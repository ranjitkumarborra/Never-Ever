//
//  PathFinder.h
//  testGlut
//
//  Created by Vivek Seetharaman on 4/3/13.
//  Copyright 2013 Sourcebits Technologies. All rights reserved.
//

#ifndef testGlut_PathFinder_h
#define testGlut_PathFinder_h

#include <vector>
#include <stack>
#include <queue>

#include "CollisionGraph.h"
#include "Point2f.h"
#include "TileMap.h"

using namespace std;

struct Path
{
    vector<int> vecNodeID;
    vector<Point2f> vecNodePoints;
};

class PathFinder
{
    
public:
    PathFinder( CollisionGraph *pGraph, TileMap *pTileMap );
    
    virtual Path GetPath(  Point2f source, Point2f goal ) = 0;      // Node coordinates x,y
    
    virtual bool CycleOnce()
    {
        return true;
    }
    
protected:
    virtual Path TracePathToTarget();
 
    void Initialize();

protected:
    
    CollisionGraph *m_pGraph;
    
    int *m_pParentIDs;                  // Array that keeps track of a node's parent id. For Ex: To find the id of the parent of Node #9 == m_ParentIDs[9]
    
    int m_SourceID;                     // Source node ID
    
    int m_TargetID;                     // Targer node ID
    
    Point2f m_TargetPos;
    
    Point2f m_SourcePos;
    
    TileMap *m_pTileMap;       
};


#endif
