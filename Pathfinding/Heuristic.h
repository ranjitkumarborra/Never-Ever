//
//  Heuristic.h
//  testGlut
//
//  Created by Vivek Seetharaman on 4/8/13.
//  Copyright 2013 Sourcebits Technologies. All rights reserved.
//

#ifndef testGlut_Heuristic_h
#define testGlut_Heuristic_h

#include <iostream>
#include <algorithm>
#include <math.h>
#include <math.h>

class Heuristic
{
public:
    virtual float ComputeCostToTarget( Point2f currentPosition, Point2f targetPosition ) = 0;
};


class Heuristic_Manhattan : public Heuristic
{
    float ComputeCostToTarget( Point2f currentPosition, Point2f targetPosition )
    {
        return ( fabs( currentPosition.x - targetPosition.x ) + fabs( currentPosition.y - targetPosition.y ) );
    }
};

class Heuristic_Euclidean : public Heuristic
{
    float ComputeCostToTarget( Point2f currentPosition, Point2f targetPosition  )
    {
        return(sqrtf(  ( currentPosition.x - targetPosition.x )*( currentPosition.x - targetPosition.x ) + ( currentPosition.y - targetPosition.y )*( currentPosition.y - targetPosition.y ) ) );
    }
};

#endif
