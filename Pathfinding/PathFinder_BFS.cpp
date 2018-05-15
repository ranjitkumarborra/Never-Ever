//
//  PathFinder_DFS.cpp
//  testGlut
//
//  Created by Vivek Seetharaman on 4/3/13.
//  Copyright 2013 Sourcebits Technologies. All rights reserved.
//

#include <iostream>
#include "PathFinder_BFS.h"
#include "Point2f.h"

PathFinder_BFS:: PathFinder_BFS( CollisionGraph* pGraph, TileMap *pTileMap) : PathFinder( pGraph , pTileMap)
{
    m_VisitedNodes = new bool[ pGraph->GetNodeCount() ];
    
    for( int i=0; i<m_pGraph->GetNodeCount(); i++ )
    {
        m_VisitedNodes[i] = false;
    }
}

Path PathFinder_BFS:: GetPath( Point2f source, Point2f target )
{
    m_SourceID = m_pGraph->GetNodeID( source.x, source.y );
    
    m_TargetID = m_pGraph->GetNodeID( target.x, target.y );
    
    Path path;
    
    // INITIALIZE ALGORITHM: 
    // Push Source node ID onto Stack
    
    Edge firstEdge( m_SourceID, m_SourceID );
    
    m_EdgeQueue.push( firstEdge );
    
    // Store Parent
    m_pParentIDs[ m_SourceID ] = m_SourceID;
    
    // LOOP
    bool bFound = false;
    while( !m_EdgeQueue.empty() )
    {
        // STEP 1: Get node from the front of the Queue
        Edge poppedEdge = m_EdgeQueue.front();
        int nodeID = poppedEdge.toID;
        
        m_EdgeQueue.pop();
        
        //printf("\n Q Size= %d", m_EdgeQueue.size() );
        // STEP 2: Record Parent
        m_pParentIDs[ nodeID ] = poppedEdge.fromID;
        
        // STEP 3: Mark visited
        m_VisitedNodes[ nodeID ] = true;
        
        
        // STEP 4: Check termination condition - Target found?
        if( nodeID == m_TargetID )
        {
            // Target found!
            bFound = true;
            break;
        }
        
        // STEP 5: Push connected edges onto stack - ONLY EDGES WITH UNVISITED "TO" NODES GO ON STACK
        PushNeighborEdges( nodeID );
        
        //DBug_PrintVisitedList();
        // For Dubug ONLY!
        m_pTileMap->SetTileState(nodeID, ECT_VISITED);
        //m_pTileMap->Render();
        
    }
    
    if( bFound )
    {
        // Backtrack in the parent list from target to source
        path = TracePathToTarget();
    }
    
    // Finally, Cleanup and be ready for next request!
    CleanUp();
    
    return path;
}



// 1. Pushes connected nodes onto stack
// 2. CHECKS: Make sure the nodes are un-visited and node is UN-OCCUPIED

void PathFinder_BFS:: PushNeighborEdges( int nodeID )
{
    Node* pNode     =   m_pGraph->GetNode(nodeID);
    
    for( int i=0 ; i < pNode->neighborIDs.size(); i++ )
    {
        int neighborID = pNode->neighborIDs[i];
        
        if( m_VisitedNodes[neighborID] )            // If neighbor has already been visited; don't add the edge!
            continue;
    
        if( m_pGraph->GetCost(neighborID) > 0 )
            continue;
        
        Edge edge( pNode->m_ID, neighborID );
        m_EdgeQueue.push( edge );
        
        m_VisitedNodes[ neighborID ] = true;
    }
    
}

// Clears all data structures used to service the last pathfinding query.
// Brings the Pathfinder Object back to a new state ready to service the newxt request
void PathFinder_BFS:: CleanUp()
{
    // 1. Clear Edge Queue
    while (!m_EdgeQueue.empty())
    {
        m_EdgeQueue.pop();
    }
    
    // 2. Clear Parent ID and VisitedNodes lists
    for( int n=0; n< m_pGraph->GetNodeCount(); n++ )
    {
        m_pParentIDs[n]   = NULL;
        
        m_VisitedNodes[n] = false;
    }
}


    


