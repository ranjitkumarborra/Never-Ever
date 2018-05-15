//
//  PathManager.h
//  PathFinder
//
//  Created by Rajavanya on 18/04/13.
//
//

#ifndef __PathFinder__PathManager__
#define __PathFinder__PathManager__

#include <iostream>
#include "Point2f.h"
#include "Unit.h"
#include "PathScheduler.h"

#include <map>

using namespace std;

class PathManager {

public:
    static PathManager* GetInstance();

    void RequestForPath(Point2f source, Point2f goal, INavigatable *owner);
    
    void Update();
    
    PathScheduler* GetScheduler();
    
    void PathServiceRequestComplete( bool status, INavigatable *owner, Path p);
    
    Path FetchPath (INavigatable *owner);
    
private:
    PathManager();
    
    static PathManager *_manager;
    
    PathScheduler *mScheduler;
    
    map<INavigatable*, Path> mResultMap;
};

#endif /* defined(__PathFinder__PathManager__) */