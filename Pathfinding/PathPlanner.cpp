//
//  PathPlanner.cpp
//  PathFinder
//
//  Created by Rajavanya on 19/04/13.
//
//

#include "PathPlanner.h"
#include "PathManager.h"
#include "PathFinder_A_STAR.h"
#include "INavigatable.h"

extern TileMap     *tileMap;

PathPlanner::PathPlanner(INavigatable *pOwner)
{
    this->m_pOwner = pOwner;
    this->m_pPathFinder = new PathFinder_A_STAR( tileMap->GetCollisionGraph(), tileMap );
}

void PathPlanner::RequestPath( const Point2f& targetPosition )
{
    this->mTargetPosition = targetPosition;
    
    //get the scheduler from Path Manager singleton and add itself via register
    PathManager::GetInstance()->GetScheduler()->RegisterPathPlanner(this);
}

Path PathPlanner::GetPath()
{
    Path p = m_pPathFinder->GetPath(this->m_pOwner->GetPositionForNavigation(), this->mTargetPosition);
    
    PathManager::GetInstance()->PathServiceRequestComplete( true, this->m_pOwner, p);
    
    return p;
}

bool PathPlanner::CycleOnce()
{
    return true;
}

void PathPlanner::SearchFullPath()
{
}