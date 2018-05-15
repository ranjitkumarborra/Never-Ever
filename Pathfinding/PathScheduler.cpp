//
//  PathScheduler.cpp
//  PathFinder
//
//  Created by Rajavanya on 19/04/13.
//
//

#include "PathScheduler.h"
#include "PathPlanner.h"

void PathScheduler::RegisterPathPlanner( PathPlanner* pPathPlanner )
{
    m_qPathPlanners.push(pPathPlanner);
}

void PathScheduler::UnRegisterPathPlanner( PathPlanner* pPathPlanner )
{
    
}

SerialPathScheduler::SerialPathScheduler(int maxRequests)
{
    this->mMaxRequests = maxRequests;
}

void SerialPathScheduler::Update()
{    
    for (int i = 0; i < this->mMaxRequests; i++)
    {
        //pop from queue and process, one whole request
        PathPlanner *tPathPlanner = m_qPathPlanners.front();
        
        if (m_qPathPlanners.size() == 0) break;
        
        //now ask the path planner to get the path
        tPathPlanner->GetPath();
        
        m_qPathPlanners.pop();
        
        delete tPathPlanner;
    }
    
    return;
}