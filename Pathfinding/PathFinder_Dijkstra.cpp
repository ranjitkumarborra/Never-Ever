//
//  PathFinder_Dijkstra.cpp
//  testGlut
//
//  Created by Vivek Seetharaman on 4/7/13.
//  Copyright 2013 Sourcebits Technologies. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <math.h>
#include "PathFinder_Dijkstra.h"
#include "Point2f.h"


bool operator> ( const OpenElement &e1, const OpenElement &e2)
{
    return !(e1.accumulatedCost >= e2.accumulatedCost);
}
bool operator< (const OpenElement &e1, const OpenElement &e2)
{
    return !(e1.accumulatedCost < e2.accumulatedCost);
}

PathFinder_Dijkstra:: PathFinder_Dijkstra( CollisionGraph* pGraph, TileMap *pTileMap) : PathFinder( pGraph , pTileMap)
{
    float veryHighNumber = 10000000;

    m_CLOSED_List        = new bool [ m_pGraph->GetNodeCount() ];
    
    m_arrAccumulatedCost = new float[ m_pGraph->GetNodeCount() ];
    
    m_arrAccumulatedCostFromSource = new float[ m_pGraph->GetNodeCount() ];
    
    for( int i=0; i<m_pGraph->GetNodeCount(); i++ )
    {
        m_CLOSED_List[i] = false;
        
        m_arrAccumulatedCost[i] = veryHighNumber;
        
        m_arrAccumulatedCostFromSource[i] = veryHighNumber;
    }
    
    // Heuristic
    m_pHeuristic = NULL;///new Heuristic_Manhattan();
}

bool  PathFinder_Dijkstra:: CycleOnce()
{
    static int iterCount = 0;
    bool bTargetFound = false;
    // printf("\n\n\n Cycle: %d", iterCount++ );
    
    // 1. Get the node ID with least cumulative cost in the Open List
    int minCostNodeID  = GetMinFromOpenList();
    Node* pMinCostNode = m_pGraph->GetNode( minCostNodeID );
    int node_X_Coord = pMinCostNode->m_Coord.x;
    int node_Y_Coord = pMinCostNode->m_Coord.y;
    
    //  Termination
    if( minCostNodeID == m_TargetID )
    {
        bTargetFound = true;
        return true;
    }
    
    
    // 2. Process all Neighbors
    Node *neighbors[8];
    
    int neighborCnt = m_pGraph->GetNeighbors( node_X_Coord, node_Y_Coord, &neighbors[0] );
    
    for( int n=0; n<neighborCnt; n++ )
    {
        // Get Neighbor
        Node* pNeighbor = neighbors[n];
        
        int neighborID  = pNeighbor->m_ID;
        
        Point2f neighborCoord = pNeighbor->m_Coord;
        
        // Ignore this neighbor if its in CLOSED list
        if( m_CLOSED_List[ neighborID ] )
            continue;
        
        // 3. Compute current total movement cost
        float costFromSource = m_arrAccumulatedCostFromSource[ minCostNodeID ] + pNeighbor->m_Cost;
        
        float costFromTarget = 0;
        
        if( m_pHeuristic )
            costFromTarget = m_pHeuristic->ComputeCostToTarget(neighborCoord, m_TargetPos);
        
        int currentAccumCost =  costFromSource + costFromTarget;
        
        // 4. If node is not in OPEN List i.e Parent is NULL, then Update Parent and costs in the tables 
        if( -1 == m_pParentIDs[ neighborID ] )
        {
            // Update Parent in the Parent list
            m_pParentIDs[ neighborID ] = minCostNodeID;
            
            // Update in the AccumulatedCostFromSource list
            m_arrAccumulatedCostFromSource[ neighborID ] = costFromSource;
            
            // Update in the AccumulatedCost list
            m_arrAccumulatedCost[ neighborID ] = currentAccumCost;
        }
        
        // If node is Already in the OPEN list, i.e Parent is Valid, i.e the node has been traversed before
        // Then check if "Edge" can be "Relaxed", i.e see if the current path is shorter than previously recorded one. If so, replace parent and cost
        else
        {
            if( m_arrAccumulatedCost[ neighborID ] > currentAccumCost )  // Previous cost is higher than current cost
            {
                //Replace parent to reflect new shortest path to this neighbor node from the source
                m_pParentIDs[ neighborID ] = minCostNodeID;
                
                // Update in the AccumulatedCostFromSource list
                m_arrAccumulatedCostFromSource[ neighborID ] = costFromSource;
                
                // Replace the old total cost with the current total cost of new shortest path
                m_arrAccumulatedCost[ neighborID ] = currentAccumCost;
            }
        }
    }// End Neighbor Loop
    
    // 5. Remove the processed node from OPEN List
    RemoveFromOpenList( minCostNodeID );
    
    // 6. Add this node to CLOSED list
    AddToClosedList( minCostNodeID );
    
    // 7. Add Neighbors to Open List ( Ignore neighbors that are in CLOSED list )
    AddNeighborsToOpenList(minCostNodeID);
    
    // 8. Progress Visualizer
    //m_pTileMap->SetTileState(minCostNodeID, ECT_VISITED);
    m_pTileMap->Render();

    return false;
}

/*
Path PathFinder_Dijkstra:: GetPath( Point2f source, Point2f target )
{
    m_SourceID = m_pGraph->GetNodeID( source.x, source.y );
    
    m_TargetID = m_pGraph->GetNodeID( target.x, target.y );
    
    m_TargetPos = target;
    
    m_SourcePos = source;
    
    Path path;
    
    // INITIALIZE ALGORITHM: 
    // Add Source node ID to OPEN List
   
        
    m_pParentIDs[ m_SourceID ] = m_SourceID;
    
    m_arrAccumulatedCost[ m_SourceID ] = 0;
    m_arrAccumulatedCostFromSource[ m_SourceID ] = 0;
    
    AddToOpenList( m_SourceID );
    
    bool bTargetFound;
    while( 0 < m_OPEN_List.size() )
    {
         
         if( bTargetFound = CycleOnce() )
             break;
    }
    
    if( bTargetFound )
    {
        // Backtrack in the parent list from target to source
        path = TracePathToTarget();
    }
    
    // Finally, Cleanup and be ready for next request!
    CleanUp();
    
    return path;
}
 
*/

Path PathFinder_Dijkstra:: GetPath( Point2f source, Point2f target )
{
    m_SourceID = m_pGraph->GetNodeID( source.x, source.y );
    
    m_TargetID = m_pGraph->GetNodeID( target.x, target.y );
    
    m_TargetPos = target;
    
    m_SourcePos = source;
    
    Path path;
    
    // INITIALIZE ALGORITHM: 
    // Add Source node ID to OPEN List
    
    
    m_pParentIDs[ m_SourceID ] = m_SourceID;
    
    m_arrAccumulatedCost[ m_SourceID ] = 0;
    m_arrAccumulatedCostFromSource[ m_SourceID ] = 0;
    
    AddToOpenList( m_SourceID );
    
    bool bTargetFound = false;
    while( 0 < m_OPEN_List.size() )
    {
        
        static int iterCount = 0;
        // printf("\n\n\n Cycle: %d", iterCount++ );
        
        // 1. Get the node ID with least cumulative cost in the Open List
        int minCostNodeID  = GetMinFromOpenList();
        Node* pMinCostNode = m_pGraph->GetNode( minCostNodeID );
        
        //  Termination
        if( minCostNodeID == m_TargetID )
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
            
            int neighborID  = pNeighbor->m_ID;
            
            if( pNeighbor->m_bIsPadNode )
                continue;
            
            Point2f neighborCoord = pNeighbor->m_Coord;
            
            // Ignore this neighbor if its in CLOSED list
            if( m_CLOSED_List[ neighborID ] )
                continue;
            
            // 3. Compute current total movement cost
            float costFromSource = m_arrAccumulatedCostFromSource[ minCostNodeID ] + pNeighbor->m_Cost;
            
            float costFromTarget = 0;
            
            if( m_pHeuristic )
                costFromTarget = m_pHeuristic->ComputeCostToTarget(neighborCoord, m_TargetPos);
            
            int currentAccumCost =  costFromSource + costFromTarget;
            
            // 4. If node is not in OPEN List i.e Parent is NULL, then Update Parent and costs in the tables 
            if( -1 == m_pParentIDs[ neighborID ] )
            {
                // Update Parent in the Parent list
                m_pParentIDs[ neighborID ] = minCostNodeID;
                
                // Update in the AccumulatedCostFromSource list
                m_arrAccumulatedCostFromSource[ neighborID ] = costFromSource;
                
                // Update in the AccumulatedCost list
                m_arrAccumulatedCost[ neighborID ] = currentAccumCost;
            }
            
            // If node is Already in the OPEN list, i.e Parent is Valid, i.e the node has been traversed before
            // Then check if "Edge" can be "Relaxed", i.e see if the current path is shorter than previously recorded one. If so, replace parent and cost
            else
            {
                if( m_arrAccumulatedCost[ neighborID ] > currentAccumCost )  // Previous cost is higher than current cost
                {
                    //Replace parent to reflect new shortest path to this neighbor node from the source
                    m_pParentIDs[ neighborID ] = minCostNodeID;
                    
                    // Update in the AccumulatedCostFromSource list
                    m_arrAccumulatedCostFromSource[ neighborID ] = costFromSource;
                    
                    // Replace the old total cost with the current total cost of new shortest path
                    m_arrAccumulatedCost[ neighborID ] = currentAccumCost;
                }
            }
        }// End Neighbor Loop
        
        // 5. Remove the processed node from OPEN List
        RemoveFromOpenList( minCostNodeID );
        
        // 6. Add this node to CLOSED list
        AddToClosedList( minCostNodeID );
        
        // 7. Add Neighbors to Open List ( Ignore neighbors that are in CLOSED list )
        AddNeighborsToOpenList(minCostNodeID);
        
        // 8. Progress Visualizer
        //m_pTileMap->SetTileState(minCostNodeID, ECT_VISITED);
        m_pTileMap->Render();

    }
    
    if( bTargetFound )
    {
        // Backtrack in the parent list from target to source
        path = TracePathToTarget();
    }
    
    // Finally, Cleanup and be ready for next request!
    CleanUp();
    
    return path;
}


   
void PathFinder_Dijkstra:: AddToOpenList( int nodeID )
{
    float accumCost = m_arrAccumulatedCost[ nodeID ];
    
    OpenElement e = OpenElement( nodeID, accumCost );
    
    m_OPEN_List.push_back(e); 
    std::push_heap (m_OPEN_List.begin(),m_OPEN_List.end());
    
    //printf("\n\n PUSH to OPEN: Node #%d", nodeID);
    //DBUG_PrintVector(m_OPEN_List);
    
    if(  m_pTileMap->GetTileState(nodeID) != ECT_SOURCE && m_pTileMap->GetTileState(nodeID) != ECT_TARGET )
        m_pTileMap->SetTileState( nodeID, ECT_OPEN);
}

// Returns the NodeID with the Minimum Accumulate Cost
int PathFinder_Dijkstra:: GetMinFromOpenList()
{
    OpenElement minCostElement = m_OPEN_List.front();
    
    //printf("\n\n MIN OPEN: \n\t\t <id=%d, cost=%f",minCostElement.nodeID, minCostElement.accumulatedCost );
    
    return minCostElement.nodeID;
}

void PathFinder_Dijkstra:: RemoveFromOpenList( int nodeID )
{
    std::pop_heap (m_OPEN_List.begin(),m_OPEN_List.end()); 
    m_OPEN_List.pop_back();
    
    //printf("\n\n POP OPEN: Node #%d", nodeID);
    //DBUG_PrintVector(m_OPEN_List);
}

void PathFinder_Dijkstra:: AddToClosedList( int nodeID )
{
    //printf("\n PUSH to CLOSED: Node #%dw");
    
    m_CLOSED_List[ nodeID ] = true;
    
    if(  m_pTileMap->GetTileState(nodeID) != ECT_SOURCE && m_pTileMap->GetTileState(nodeID) != ECT_TARGET )
         m_pTileMap->SetTileState( nodeID, ECT_CLOSED);
}



/*
 *  Adds neighbors of the specified node ID to the Open LIST
 *    - Don't add neighbors that are in CLOSED list
 *    - For Nodes that are already in OPEN list ( Edge has been relaxed ), access the OpenElement and update the new cost in the structure
         + And then call sort_heap
 */ 
void PathFinder_Dijkstra:: AddNeighborsToOpenList( int nodeID )
{
    Node* pNode = m_pGraph->GetNode( nodeID );

    Node *neighbors[8];
    
    int neighborCnt = m_pGraph->GetNeighbors( pNode->m_Coord.x , pNode->m_Coord.y , &neighbors[0] );
    
    for( int n=0; n<neighborCnt; n++ )
    {
        // Get Neighbor
        Node* pNeighbor = neighbors[n];
        
        int neighborID  = pNeighbor->m_ID;
        
        if( pNeighbor->m_bIsPadNode )
            continue;
        
        // Dont' add closed nodes
        if( m_CLOSED_List[ neighborID ] )
            continue;
        
        // Go through all Open nodes and see if neighbor is already in OPEN list
        bool bNeighborAlreadyInOPEN = false;
        for( int i=0; i< m_OPEN_List.size(); i++ )
        {
            if( m_OPEN_List[i].nodeID == neighborID )
            {
                // Neighbor found in the OPEN LIST!
                // Update new lower cost                 
                m_OPEN_List[i].accumulatedCost = m_arrAccumulatedCost[neighborID];
                
                bNeighborAlreadyInOPEN = true;
                break;
            }
        }
        
        if( bNeighborAlreadyInOPEN )
        {
            // Call sort_heap because the cost has changed
            std::sort_heap ( m_OPEN_List.end(), m_OPEN_List.begin() );
        }
        // Add neighbor to OPEN list if it was not found already in the OPEN List
        else
        {
            AddToOpenList(neighborID);
        }
    }// End Neighbor loop
        
}


// Clears all data structures used to service the last pathfinding query.
// Brings the Pathfinder Object back to a new state ready to service the newxt request
void PathFinder_Dijkstra:: CleanUp()
{
    // 1. Clear Edge Queue
    m_OPEN_List.clear();
    
    float veryHighNumber = 1000000;
    // 2. Clear Parent ID and VisitedNodes lists
    for( int n=0; n< m_pGraph->GetNodeCount(); n++ )
    {
        m_pParentIDs[n]   = NULL;
        
        m_CLOSED_List[n] = false;
        
        m_arrAccumulatedCost[n] = veryHighNumber;
        
        m_arrAccumulatedCostFromSource[n] = veryHighNumber;
        
    }
}


void PathFinder_Dijkstra:: DBUG_PrintVector( vector< OpenElement > vec)
{
    printf("\n");
    for( int i=0; i<vec.size(); i++ )
    {
        printf("\t \t <id=%d, cost=%f", vec[i].nodeID, vec[i].accumulatedCost);
    }
}


