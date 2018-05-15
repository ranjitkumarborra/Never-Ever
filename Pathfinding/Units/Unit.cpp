//
//  Unit.cpp
//  PathFinder
//
//  Created by Rajavanya on 12/04/13.
//
//

#include "Unit.h"
#include <OpenGL/gl.h>     // The GL Header File
#include <OpenGL/glext.h>
#include "Color4f.h"
#include "PathManager.h"

extern TileMap     *tileMap;

using namespace vektor3d::core;

Color4f UNIT_COLOR_IDLE                 = Color4f( 0.5f, 0.5f, 0.5f, 1.0);
Color4f UNIT_COLOR_MOVING_TO_TARGET     = Color4f( 1.0f, 0.8f, 0.0f, 1.0f);
Color4f UNIT_COLOR_SELECTED             = Color4f( 0.0f, 0.7f, 0.0f, 1.0f);

Point2f Unit::GetPositionForNavigation()
{
    Point2f tGridCoords = this->m_Position;
    tGridCoords.x /= tileMap->m_TileSize;
    tGridCoords.y /= tileMap->m_TileSize;

    return tGridCoords;
}

void Unit::PathResultNotify()
{
    Path p =PathManager::GetInstance()->FetchPath(this);
    this->m_Path = p;
    this->m_NextWayPointIndex = this->m_Path.vecNodePoints.size()-1;
    
    for (int j = 0; j < this->m_Path.vecNodePoints.size(); j++)
    {
        float random = (-tileMap->m_TileSize/12) +  ((float)rand()/RAND_MAX) * (tileMap->m_TileSize/6);
        
        this->m_Path.vecNodePoints[j].x = (this->m_Path.vecNodePoints[j].x+ 0.5)*tileMap->m_TileSize;
        this->m_Path.vecNodePoints[j].y = (this->m_Path.vecNodePoints[j].y+ 0.5)*tileMap->m_TileSize;
        
        this->m_Path.vecNodePoints[j].x += random;
        this->m_Path.vecNodePoints[j].y += random;
    }

    float random = (-tileMap->m_TileSize/2) +  ((float)rand()/RAND_MAX) * tileMap->m_TileSize;
    this->m_Path.vecNodePoints[0].x += random;
    this->m_Path.vecNodePoints[0].y += random;
}

Unit::Unit( Point2f P )
{    
    setPosition(P.x, P.y);
    
    m_Speed = ((float)rand())/RAND_MAX * 0.2f + 3.91f;   //speed always has to be lesser or equal to radius
    
    m_Radius =  5.0f;// ((float)rand())/RAND_MAX * 30.0f + 10.0;
    
    m_NextWayPointIndex = -1;
    
    m_eUnitState = EUS_IDLE;
    
    m_bIsSelected = false;
    
    m_Variance = 1.0f;
}

Unit::Unit()
{
    
}

Unit::~Unit()
{
    
}

void Unit::Render()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    
    glPointSize(10.0f);
    
    Color4f unitColor;
    switch( m_eUnitState )
    {
        case EUS_IDLE:
            unitColor = UNIT_COLOR_IDLE;
            break;
        
        case EUS_MOVING_TO_TARGET:
            unitColor = UNIT_COLOR_MOVING_TO_TARGET;
            break;
    }
    if( m_bIsSelected )
        unitColor = UNIT_COLOR_SELECTED;
    
    glColor4f( unitColor.R, unitColor.G, unitColor.B, unitColor.A);
    
    glBegin(GL_POINTS);
        glVertex2f(m_Position.x, m_Position.y);
    glEnd();
    
    glPopMatrix();
}

void Unit::setPosition(float x, float y)
{
    this->m_Position.x = x;
    this->m_Position.y = y;
}

Point2f Unit::getPosition()
{
    return m_Position;
}

void Unit::Update(float dt)
{
    if (m_NextWayPointIndex > -1)
    {
        //check the first point and travel towards it
        //on reaching the first point, erase it from the vector and repeat
        
        float t_DistToNextPoint = this->m_Position.distance(m_Path.vecNodePoints[m_NextWayPointIndex]);
       

        Point2f t_NormalizedDirectionVector = m_Path.vecNodePoints[m_NextWayPointIndex] - this->m_Position;
        
        if( t_DistToNextPoint * t_DistToNextPoint > 1e-10 )
        {
            t_NormalizedDirectionVector.x /= t_DistToNextPoint;
            t_NormalizedDirectionVector.y /= t_DistToNextPoint;
        }
                
        if (t_DistToNextPoint < 5 && m_Variance < 1.0)
            m_Variance += 0.02;
        else if ( t_DistToNextPoint > 5 && m_Variance > 0.5)
            m_Variance -= 0.02;
        
        m_Position.x += t_NormalizedDirectionVector.x * m_Speed * m_Variance;
        m_Position.y += t_NormalizedDirectionVector.y * m_Speed * m_Variance;
        
        
        if (t_DistToNextPoint < m_Radius)
        {
            m_NextWayPointIndex--;
            //printf("Index = %d\n", m_NextWayPointIndex);
        }
    }
}