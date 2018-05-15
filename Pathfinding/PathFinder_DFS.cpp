//
//  PathFinder_DFS.cpp
//  testGlut
//
//  Created by Vivek Seetharaman on 4/3/13.
//  Copyright 2013 Sourcebits Technologies. All rights reserved.
//

#include <iostream>
#include "PathFinder_DFS.h"
#include "Point2f.h"

PathFinder_DFS:: PathFinder_DFS( CollisionGraph* pGraph, TileMap *pTileMap) : PathFinder( pGraph , pTileMap)
{
    m_VisitedNodes = new bool[ pGraph->GetNodeCount() ];
    
    for( int i=0; i<m_pGraph->GetNodeCount(); i++ )
    {
        m_VisitedNodes[i] = false;
    }
}

Path PathFinder_DFS:: GetPath( Point2f source, Point2f target )
{
    m_SourceID = m_pGraph->GetNodeID( source.x, source.y );
    
    m_TargetID = m_pGraph->GetNodeID( target.x, target.y );
    
    Path path;
    
    
    // INITIALIZE ALGORITHM: 
    // Push Source node ID onto Stack
      
    Edge firstEdge( m_SourceID, m_SourceID );
    
    m_EdgeStack.push( firstEdge );
    
    // Store Parent
    m_pParentIDs[ m_SourceID ] = m_SourceID;
    
    // LOOP
    bool bFound = false;
    while( !m_EdgeStack.empty() )
    {
        // STEP 1: Pop Top node off stack
        Edge poppedEdge = m_EdgeStack.top();
        int nodeID = poppedEdge.toID;
        
        m_EdgeStack.pop();
        
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
        
        
        // For Dubug ONLY!
        m_pTileMap->SetTileState(nodeID, ECT_VISITED);
       // m_pTileMap->Render();
        
    }
    
    if( bFound )
    {
        // Backtrack in the parent list from target to source
        path = TracePathToTarget();
    }
    
    return path;
}


// 1. Pushes connected nodes onto stack
// 2. CHECKS: Make sure the nodes are un-visited and node is un occupied

void PathFinder_DFS:: PushNeighborEdges( int nodeID )
{
    // 4-Way Search
    
    Node* pNode     =   m_pGraph->GetNode(nodeID);
    
    Point2f coord   =   pNode->m_Coord;
    
    int xMax = m_pGraph->GetNodeCountX();
    int yMax = m_pGraph->GetNodeCountY();
    
    if( coord.x < 0 || coord.x > xMax || coord.y<0 || coord.y > yMax )
    {   
        printf("\n ERROR: PAthFinder:: PushNeighborEdges() - INVALID NODE! ");
    }
    
    Point2f L_Coord = Point2f( coord.x-1, coord.y   );
    Point2f R_Coord = Point2f( coord.x+1, coord.y   );
    Point2f T_Coord = Point2f( coord.x  , coord.y+1 );
    Point2f B_Coord = Point2f( coord.x  , coord.y-1 );
    
    vector< Point2f > vecNeighborNodeCoords;
    vecNeighborNodeCoords.push_back(L_Coord);
    vecNeighborNodeCoords.push_back(T_Coord);
    vecNeighborNodeCoords.push_back(R_Coord);
    vecNeighborNodeCoords.push_back(B_Coord);
    
    for( int i=0; i<vecNeighborNodeCoords.size(); i++ )
    {
        Point2f nodeCoord = vecNeighborNodeCoords[i];
        
        if( nodeCoord.x<0 || nodeCoord.x >= xMax || nodeCoord.y<0 || nodeCoord.y>=yMax )
        {
            // Dont add the edge, because it is invalid and out of bounds
        }
        else // This is a valid edge - but Make Sure that the destination node has not been visited! Only then push to stack 
        {
            int toID = nodeCoord.y * xMax + nodeCoord.x;
            
            // If node already visited - Dont push on Stack
            if( false == m_VisitedNodes[toID] )
            {
                // Lastly check if node is occupied
                if( 0 == m_pGraph->GetCost( toID ) )
                {
                    Edge edge( nodeID, toID );
                    
                    m_EdgeStack.push(edge);
                }
            }
        }
    }
}

void PathFinder_DFS:: CleanUp()
{
    // 1. Clear Edge Stack
    while (!m_EdgeStack.empty())
    {
        m_EdgeStack.pop();
    }
    
    // 2. Clear Parent ID and VisitedNodes lists
    for( int n=0; n< m_pGraph->GetNodeCount(); n++ )
    {
        m_pParentIDs[n]   = NULL;
        
        m_VisitedNodes[n] = false;
    }

}
