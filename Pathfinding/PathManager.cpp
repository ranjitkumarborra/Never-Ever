//
//  PathManager.cpp
//  PathFinder
//
//  Created by Rajavanya on 18/04/13.
//
//

#include "PathManager.h"
#include "PathPlanner.h"
#include "INavigatable.h"

PathManager::PathManager()
{
    this->mScheduler = new SerialPathScheduler(1);
}

PathManager* PathManager::_manager = 0;

PathManager* PathManager::GetInstance()
{
    if (!_manager)
        _manager = new PathManager();
    
    return _manager;
}

void PathManager::RequestForPath(Point2f source, Point2f goal, INavigatable *owner)
{
    PathPlanner *planner = new PathPlanner(owner);
    planner->RequestPath(goal);
}

void PathManager::Update()
{
    mScheduler->Update();
}

PathScheduler* PathManager::GetScheduler()
{
    return mScheduler;
}

void PathManager::PathServiceRequestComplete( bool status, INavigatable *owner, Path p)
{
    if (status)
    {
        this->mResultMap[owner] = p;
        
        owner->PathResultNotify();
    }
}


Path PathManager::FetchPath (INavigatable *owner)
{
    Path p = this->mResultMap[owner];
    
    return p;
}