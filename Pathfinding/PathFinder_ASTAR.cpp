//
//  PathFinder_ASTAR.cpp
//  PathFinder
//
//  Created by Vivek Seetharaman on 4/12/13.
//  Copyright 2013 Sourcebits Technologies. All rights reserved.
//

#include <iostream>


#include <iostream>
#include <algorithm>
#include <math.h>
#include "PathFinder_A_STAR.h"
#include "Point2f.h"
#include "DTimer.h"

#define INDEX(i,j) ((j)*m_X_Nodes+(i))
#define ROOT2 1


DTimer timer1;

//#define VISUALIZE

PathFinder_A_STAR:: PathFinder_A_STAR( CollisionGraph* pGraph, TileMap *pTileMap) : PathFinder( pGraph , pTileMap)
{
    m_pNodeProxies = new NodeProxy[ m_pGraph->GetNodeCount() ];

    // Heuristic
    m_pHeuristic = new Heuristic_Manhattan();
    
}


Path PathFinder_A_STAR:: GetPath( Point2f source, Point2f target )
{
    m_SourceID = m_pGraph->GetNodeID( source.x, source.y );
    
    m_TargetID = m_pGraph->GetNodeID( target.x, target.y );
    
    m_TargetPos = target;
    
    m_SourcePos = source;
    
    Path path;
    
    NodeProxy *pTargetNodeProxy = &m_pNodeProxies[m_TargetID];
    
    // INITIALIZE ALGORITHM: 
    // 1. Initialize Data structures
    
    m_OPEN_List.clear();
    
    //double t1 = timer1.getCurrentTime();
    memset( m_pNodeProxies, VERY_HIGH_NUMBER, sizeof( NodeProxy) * m_pGraph->GetNodeCount() );
    //double t2 = timer1.getCurrentTime();
    //printf("\n Memset Takes: %f ms", t2-t1);
    
    m_pNodeProxies[ m_SourceID ].parentID = m_SourceID;
    m_pNodeProxies[ m_SourceID ].f        = 0;
    m_pNodeProxies[ m_SourceID ].g        = 0;
    
    
    for( int n=0; n<m_pGraph->GetNodeCount(); n++ )
    {
        m_pNodeProxies[n].ID = n;
        m_pNodeProxies[n].g = 10000000.0f;
    }
    
    
    // Add Source node ID to OPEN List
    AddToOpenList( m_pNodeProxies + m_SourceID, m_SourceID );
    
    bool bTargetFound = false;
    while( 0 < m_OPEN_List.size() )
    {
            
        // 1. Get the node proxy with least cumulative cost in the Open List
        NodeProxy* pMinCostNodeProxy = GetMinFromOpenList();
        
        // Get corresponding node also
        Node* pMinCostNode = m_pGraph->GetNode( pMinCostNodeProxy->ID );
        
        // 2. Remove the processed node from OPEN List
        RemoveFromOpenList();
        
        // 6. Add this node to CLOSED list
        AddToClosedList( pMinCostNodeProxy );
        
        //  Termination
        if( pMinCostNodeProxy->ID == pTargetNodeProxy->ID )
        {
            bTargetFound = true;
            break;
        }
        
        // 2. Process all Neighbors
        Node *neighbors[8];
        
        int neighborCnt = m_pGraph->GetNeighbors( pMinCostNode->m_Coord.x , pMinCostNode->m_Coord.y , &neighbors[0] );
        
        for( int n=0; n < neighborCnt; n++ )
        {
            // Get Neighbor
            Node* pNeighbor = neighbors[n];
            
            NodeProxy *pNeighborProxy = &m_pNodeProxies[ pNeighbor->m_ID ];
            
            int neighborID  = pNeighbor->m_ID;
            
            if( pNeighbor->m_bIsPadNode )
                continue;
            
            Point2f neighborCoord = pNeighbor->m_Coord;
            
            // Ignore this neighbor if its in CLOSED list
            if( pNeighborProxy->eNodeState == ENS_CLOSED )
                continue;
            
            // 3. Compute current total movement cost 'f'
            float neighborCost = (pMinCostNode->m_Coord.x == pNeighbor->m_Coord.x || pMinCostNode->m_Coord.y == pNeighbor->m_Coord.y ) ? pNeighbor->m_Cost : ROOT2*pNeighbor->m_Cost;
            float costFromSource = pMinCostNodeProxy->g + neighborCost;
            
            float costFromTarget = 0;
            
            
            
            // 4. If node is not in OPEN List i.e Parent is NULL, then Update Parent and costs in the tables 
            if( pNeighborProxy->eNodeState != ENS_OPEN  ||  pNeighborProxy->g > costFromSource )
            {
                // Update Parent in the Parent list
                pNeighborProxy->parentID = pMinCostNode->m_ID;
                
                // Update in the AccumulatedCostFromSource list
                pNeighborProxy->g = costFromSource;
                
                // Compute h: Cost from target
                if( m_pHeuristic )
                    costFromTarget = m_pHeuristic->ComputeCostToTarget(neighborCoord, m_TargetPos);
                
                // Compute f = g+h
                int currentAccumCost =  costFromSource + costFromTarget;
                // Update in the AccumulatedCost list
                pNeighborProxy->f = currentAccumCost;
                
                // If node not in OPEN, add to OPEN list
                if( pNeighborProxy->eNodeState != ENS_OPEN )
                {
                    AddToOpenList(pNeighborProxy, pNeighborProxy->ID);
                }
                
                // If node is Already in the OPEN list, i.e Parent is Valid, i.e the node has been traversed before
                // Call sort_heap because the cost has changed
                else
                {
                    std::sort_heap ( m_OPEN_List.end(), m_OPEN_List.begin(), ComparatorFunction());
                }  
            }// End IF node not in open list
            
        }// End Neighbor Loop
    
        // 8. Progress Visualizer
#ifdef VISUALIZE
        m_pTileMap->Render();
        
#endif       
        
    }
    
    if( bTargetFound )
    {
        //printf("\n Target Found");
        // Backtrack in the parent list from target to sourced
        path = TracePathToTarget();
    }
    
    return path;
}



void PathFinder_A_STAR:: AddToOpenList( NodeProxy* pProxy, int nodeID )
{
    pProxy->eNodeState = ENS_OPEN;
    
    m_OPEN_List.push_back( pProxy ); 
    std::push_heap (m_OPEN_List.begin(),m_OPEN_List.end(), ComparatorFunction() );
    
    //printf("\n\n PUSH to OPEN: Node #%d", nodeID);
    //DBUG_PrintVector(m_OPEN_List);
    
#ifdef VISUALIZE
    if(  m_pTileMap->GetTileState(nodeID) != ECT_SOURCE && m_pTileMap->GetTileState(nodeID) != ECT_TARGET )
        m_pTileMap->SetTileState( nodeID, ECT_OPEN);
#endif
    
}

// Returns the NodeID with the Minimum Accumulate Cost
NodeProxy* PathFinder_A_STAR:: GetMinFromOpenList()
{
    NodeProxy *pNodeProxy = m_OPEN_List.front();
    
    //printf("\n\n MIN OPEN: \n\t\t <id=%d, cost=%f",minCostElement.nodeID, minCostElement.accumulatedCost );
    
    return pNodeProxy;
}

void PathFinder_A_STAR:: RemoveFromOpenList()
{
    std::pop_heap (m_OPEN_List.begin(),m_OPEN_List.end(), ComparatorFunction() ); 
    m_OPEN_List.pop_back();
    
    //printf("\n\n POP OPEN: Node #%d", nodeID);
    //DBUG_PrintVector(m_OPEN_List);
}

void PathFinder_A_STAR:: AddToClosedList( NodeProxy* pProxy )
{
    //printf("\n PUSH to CLOSED: Node #%dw");
    
    pProxy->eNodeState = ENS_CLOSED;
    
    int nodeID = pProxy->ID;
   
#ifdef VISUALIZE
    if(  m_pTileMap->GetTileState(nodeID) != ECT_SOURCE && m_pTileMap->GetTileState(nodeID) != ECT_TARGET )
        m_pTileMap->SetTileState( nodeID, ECT_CLOSED);
#endif
}

bool CycleOnce()
{
    return  true;
}

Path PathFinder_A_STAR::TracePathToTarget()
{
    Path path;
    
    path.vecNodeID.push_back(m_TargetID);
    
    Point2f nodePoint = m_pGraph->GetNode(m_TargetID)->m_Coord;
    path.vecNodePoints.push_back( nodePoint  );
    
    
    int ID = m_TargetID;
    
    while(  ID != m_SourceID )
    {
        ID = m_pNodeProxies[ID].parentID;
        
        path.vecNodeID.push_back( ID );
        Point2f nodePoint = m_pGraph->GetNode(ID)->m_Coord;
        path.vecNodePoints.push_back( nodePoint  );
        
        //printf(" Path Node : %f,   %f\n",nodePoint.x,nodePoint.y );
        
    }
    
    return path;

}


//void PathFinder_A_STAR:: DBUG_PrintVector( vector< OpenElement > vec)
//{
//    printf("\n");
//    for( int i=0; i<vec.size(); i++ )
//    {
//        printf("\t \t <id=%d, cost=%f", vec[i].nodeID, vec[i].accumulatedCost);
//    }
//}

