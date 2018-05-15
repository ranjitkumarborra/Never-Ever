

#ifndef PathFinder_PathFinder_A_STAR_h
#define PathFinder_PathFinder_A_STAR_h


#include "PathFinder.h"
#include "Heuristic.h"

/*
 *  This is the structure that will be pushed into the OPEN List
 *  push_heap, sort_heap will be used on this and sorted according to "cost" of the node
 *
 */

#define VERY_HIGH_NUMBER 10000

enum E_NODE_STATE
{
    ENS_UNEXPLORED = VERY_HIGH_NUMBER,
    ENS_OPEN ,
    ENS_CLOSED
};

struct NodeProxy
{
    float f,g;
    
    E_NODE_STATE eNodeState;
    
    int ID;
    
    int parentID;
};

struct ComparatorFunction
{
    bool operator() ( NodeProxy const* n1, NodeProxy const* n2) const
    {
        return n1->f > n2->f;
    }
};


class PathFinder_A_STAR : public PathFinder
{
public:
    
    PathFinder_A_STAR( CollisionGraph *pGraph, TileMap *pTileMap);
    
    Path GetPath( Point2f start, Point2f goal );
    
    bool CycelOnce();
    
    //void CleanUp();                   // Clears ParentIDs, Stacks, Queues etc.. all datastructures and brings it back to a new state ready for a enw request
    
private:
    
    void AddToOpenList( NodeProxy*, int nodeID);
    
    void RemoveFromOpenList();
    
    void AddToClosedList( NodeProxy* );
    
    NodeProxy*  GetMinFromOpenList();
    
    void AddNeighborsToOpenList( int nodeID );
    
    Path TracePathToTarget();
    
    //void DBUG_PrintVector( vector< OpenElement > );
    
    
private:  
    
    NodeProxy* m_pNodeProxies;
    
    vector< NodeProxy* > m_OPEN_List;      // Vector that contain a list of Open Elements on the search frontier, OPEN list
    
    Heuristic *m_pHeuristic;
    
};


#endif




