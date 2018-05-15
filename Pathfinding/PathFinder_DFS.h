//
//  PathFinder_DFS.h
//  testGlut
//
//  Created by Vivek Seetharaman on 4/3/13.
//  Copyright 2013 Sourcebits Technologies. All rights reserved.
//

#ifndef testGlut_PathFinder_DFS_h
#define testGlut_PathFinder_DFS_h

#include "PathFinder.h"


class PathFinder_DFS : public PathFinder
{
public:
    PathFinder_DFS( CollisionGraph *pGraph, TileMap *pTileMap);
    
    Path GetPath( Point2f start, Point2f goal );
    
    void CleanUp();     // Clears ParentIDs, Stacks, Queues etc.. all datastructures and brings it back to a new state ready for a enw request
    
private:
    void PushNeighborEdges( int nodeID );
    
    stack< Edge > m_EdgeStack;          // Stacks the edges - used for back tracking in DFS algorithm only, wont need this one - move it to 
    
    bool *m_VisitedNodes;               // Keeps track of whether the node has been visited or not
    
    
};


#endif
