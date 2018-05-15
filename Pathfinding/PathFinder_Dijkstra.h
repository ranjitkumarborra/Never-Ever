//
//  PathFinder_Dijkstra.h
//  testGlut
//
//  Created by Vivek Seetharaman on 4/7/13.
//  Copyright 2013 Sourcebits Technologies. All rights reserved.
//

#ifndef testGlut_PathFinder_Dijkstra_h
#define testGlut_PathFinder_Dijkstra_h


#include "PathFinder.h"
#include "Heuristic.h"

/*
 *  This is the structure that will be pushed into the OPEN List
 *  push_heap, sort_heap will be used on this and sorted according to "cost" of the node
 *
 */
 
struct OpenElement
{
    int     nodeID;    // Node ID
    float   accumulatedCost;  // Node Cost
    
    OpenElement( int ID, float cost )
    {
        nodeID          = ID;
        accumulatedCost = cost;
    }
    
    friend bool operator> (const OpenElement &e1, const OpenElement &e2); 
    friend bool operator< (const OpenElement &e1, const OpenElement &e2); 
    
};



class PathFinder_Dijkstra : public PathFinder
{
public:
    
    PathFinder_Dijkstra( CollisionGraph *pGraph, TileMap *pTileMap);
    
    Path GetPath( Point2f start, Point2f goal );
    
    bool CycleOnce();
    
    void CleanUp();                   // Clears ParentIDs, Stacks, Queues etc.. all datastructures and brings it back to a new state ready for a enw request
    
private:
    
    void AddToOpenList( int nodeID );
    
    void RemoveFromOpenList( int nodeID );
    
    void AddToClosedList( int nodeID );
    
    int  GetMinFromOpenList();
    
    void AddNeighborsToOpenList( int nodeID );
    
    void DBUG_PrintVector( vector< OpenElement > );
    
    
private:  
    
    float *m_arrAccumulatedCostFromSource;  // Stores on the accumulated cost from a node back to the source: i.e g - the Cost from source
    
    float *m_arrAccumulatedCost;            // Array of accumulated cost - indexed by Node ID, This represents total cost to move to any node from SOURCE AND TARGET
                                            // Array has as many elements as there are nodes: f = g + h
    
    
    vector< OpenElement > m_OPEN_List;      // Vector that contain a list of Open Elements on the search frontier, OPEN list
    
    
    
    bool *m_CLOSED_List;                    // This is an array of bools that tells whether a Node ID is closed or not.
                                            // Array has as many elements as there are nodes
                                            // This is Spatially inefficient as N -> Large numbers, but runs in Constant time, later change this to hash map

    Heuristic *m_pHeuristic;
    
};


#endif

