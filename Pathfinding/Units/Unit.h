//
//  Unit.h
//  PathFinder
//
//  Created by Rajavanya on 12/04/13.
//
//

#ifndef __PathFinder__Unit__
#define __PathFinder__Unit__

#include <iostream>
#include "PathPlanner.h"
#include "Point2f.h"
#include "PathFinder.h"
#include "INavigatable.h"

enum E_UNIT_STATE
{
    EUS_IDLE = 0,
    EUS_MOVING_TO_TARGET
};

class Unit : public INavigatable
{
    Point2f m_Velocity;
    
    float m_Speed;
    float m_Variance;
    
    float m_Radius;
    
    bool b_IsMoving;    
    E_UNIT_STATE m_eUnitState;
    
public:
    void Render();
    void Update(float dt);
    
    void setPosition(float x, float y);
    Point2f getPosition();
    
    Unit();
    Unit( Point2f P );
    ~Unit();
    
    Path m_Path;
    int m_NextWayPointIndex;
    Point2f m_Position;
    bool m_bIsSelected;

    virtual Point2f GetPositionForNavigation();
    virtual void PathResultNotify();
};

#endif /* defined(__PathFinder__Unit__) */