//
//  PathPlanner.h
//  PathFinder
//
//  Created by Vivek Seetharaman on 4/12/13.
//  Copyright 2013 Sourcebits Technologies. All rights reserved.
//

#ifndef PathFinder_PathPlanner_h
#define PathFinder_PathPlanner_h

#include "PathFinder.h"

class INavigatable;

class PathFinder;

/*
 This class is responsible for
 */

class PathPlanner
{
private:
	INavigatable* m_pOwner;  // Owner of this path planner

	PathFinder* m_pPathFinder; // Search Algorithm
	
    Point2f mTargetPosition;
    
public:
    PathPlanner(INavigatable *pOwner);
    
	/*
     requests a path to a given target Position. this method creates an instance of search algorithm, and register this Path Planner with the path manager.
	 */
	void RequestPath( const Point2f& targetPosition );
	
	/*
     returns a path which has been already created by the search algorithm. this should be called once this path planner has been notified via  a path complete message.
	 */
	Path GetPath();
	
	/*
	 This will be called by the PathManager with which this path planner is registered. this method should be called repeatedly to find the path.
	 TimeSliced Path Manager uses this method repeatedly to find the Path in multiple cycles.
	 */
	bool CycleOnce();
	
	/*
     This will be called by the PathManager with which this path planner is registered. this method finds the full path in one go.
     
	 */
	void SearchFullPath();
};

#endif