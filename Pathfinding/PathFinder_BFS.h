//
//  PathFinder_BFS.h
//  testGlut
//
//  Created by Vivek Seetharaman on 4/3/13.
//  Copyright 2013 Sourcebits Technologies. All rights reserved.
//

#ifndef testGlut_PathFinder_BFS_h
#define testGlut_PathFinder_BFS_h

#include "PathFinder.h"


class PathFinder_BFS : public PathFinder
{
public:
    PathFinder_BFS( CollisionGraph *pGraph, TileMap *pTileMap);
    
    Path GetPath( Point2f start, Point2f goal );
    
    void CleanUp();                   // Clears ParentIDs, Stacks, Queues etc.. all datastructures and brings it back to a new state ready for a enw request
    
private:
    void PushNeighborEdges( int nodeID );

    queue< Edge > m_EdgeQueue;          // Queues the edges
    
    bool *m_VisitedNodes;             // Keeps track of whether the node has been visited or not
    
};


#endif
