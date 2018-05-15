//
//  PathFinder.cpp
//  testGlut
//
//  Created by Vivek Seetharaman on 4/3/13.
//  Copyright 2013 Sourcebits Technologies. All rights reserved.
//

#include <iostream>
#include "PathFinder.h"
#include "Point2f.h"

PathFinder:: PathFinder( CollisionGraph *pGraph , TileMap *pTileMap)
{
    m_pGraph = pGraph;
    
    m_pTileMap = pTileMap;
    
    m_pParentIDs = new int[ pGraph->GetNodeCount() ];
    
    Initialize();
}

void PathFinder:: Initialize()
{
    
    for( int i=0; i<m_pGraph->GetNodeCount(); i++ )
    {
        m_pParentIDs[i] = -1;
    }
}

Path PathFinder:: TracePathToTarget()
{
    Path path;
    
    path.vecNodeID.push_back(m_TargetID);
    
    int ID = m_TargetID;
    
    while(  ID != m_SourceID )
    {
        ID = m_pParentIDs[ ID ];
        
        path.vecNodeID.push_back( ID );
    }
    
    return path;
}

