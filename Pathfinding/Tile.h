//
//  Tile.h
//  testGlut
//
//  Created by Vivek Seetharaman on 4/1/13.
//  Copyright 2013 Sourcebits Technologies. All rights reserved.
//

#ifndef testGlut_Tile_h
#define testGlut_Tile_h

#include "Point2f.h"
#include "Color4f.h"
#include <vector>

using namespace std;
using namespace vektor3d::core;


enum E_CELL_STATE
{
    ECT_EMPTY = 0,
    ECT_OCCUPIED ,
    ECT_VISITED,
    ECT_PATH,
    ECT_OPEN,
    ECT_CLOSED,
    ECT_SOURCE,
    ECT_TARGET,
    ECT_PADDING
};

class Tile
{
public:
    
    Tile( Point2f pos, Point2f size);
    
    Tile( Point2f pos, int w, int h);
    
    Tile( int w, int h);
    
    Tile();
    
    Color4f GetColor();
    
    Color4f GetPosition();
    
    void Occupy( bool );
    
    bool IsOccupied();
    
public:
    
    enum E_CELL_STATE m_eCellState;
    
    Point2f m_Pos;                  // Physical x,y, position
    
    Point2f m_Coord;                 // Grid coordinates of this tile
     
    // Collision Cell Properties
    int m_ID;
    
    float m_Cost;
    
    bool m_bIsPaddingTile;
private:
    
    Color4f m_Color;
    
    bool m_bIsOccupied; // If Cost > 0, then Occupied is true
    

    
};


                            
#endif
