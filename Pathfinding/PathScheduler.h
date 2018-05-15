//
//  PathScheduler.h
//  PathFinder
//
//  Created by Rajavanya on 19/04/13.
//
//

#ifndef __PathFinder__PathScheduler__
#define __PathFinder__PathScheduler__

#include <queue>

using namespace std;

class PathPlanner;

class PathScheduler
{
public:
	virtual void Update() = 0;
	
	void RegisterPathPlanner( PathPlanner* pPathPlanner );
    
	void UnRegisterPathPlanner( PathPlanner* pPathPlanner );
    
protected:
    queue<PathPlanner*> m_qPathPlanners;
};

class TimeSlicedPathScheduler : public PathScheduler
{
public:
	TimeSlicedPathScheduler(int numCycles);
	
	virtual void Update();
};

class SerialPathScheduler : public PathScheduler
{
    int mMaxRequests;
    
public:
	SerialPathScheduler(int maxRequests);
	
	virtual void Update();
};

#endif /* defined(__PathFinder__PathScheduler__) */