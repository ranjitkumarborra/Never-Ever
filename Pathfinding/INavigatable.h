//
//  INavigatable.h
//  PathFinder
//
//  Created by Rajavanya on 19/04/13.
//
//

#ifndef PathFinder_INavigatable_h
#define PathFinder_INavigatable_h

#include "Point2f.h"

class INavigatable
{
public:
    virtual Point2f GetPositionForNavigation() = 0;
    virtual void PathResultNotify() = 0;
};

#endif
