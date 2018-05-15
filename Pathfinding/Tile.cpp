//
//  Tile.cpp
//  testGlut
//
//  Created by Vivek Seetharaman on 4/1/13.
//  Copyright 2013 Sourcebits Technologies. All rights reserved.
//

#include <OpenGL/gl.h>     // The GL Header File
#include <OpenGL/glext.h>
#include <GLUT/GLUT.h>  
#include <iostream>
#include "Tile.h"



Tile:: Tile( Point2f pos, Point2f size)
{
    m_Pos  = pos;
    
    m_eCellState = ECT_EMPTY;
    
    m_Color = Color4f( 0.8f, 0.8f, 9.0f, 0.4f);
    
    m_bIsOccupied= false;
    
    m_bIsPaddingTile = false;

}

Tile:: Tile( Point2f pos, int w, int h)
{
    m_Pos  = pos;
    
    m_eCellState = ECT_EMPTY;
    
    m_Color = Color4f( 0.8f, 0.8f, 1.0f, 1.0f);
    
    m_bIsOccupied= false;
    
    m_bIsPaddingTile = false;

}

Tile:: Tile( int w, int h)
{
    m_eCellState = ECT_EMPTY;
    
    m_Color = Color4f( 0.8f, 0.8f, 1.0f, 1.0f);
    
    m_bIsOccupied= false;
    
    m_bIsPaddingTile = false;

}

Tile:: Tile()
{
    m_eCellState = ECT_EMPTY;
    
    m_Color = Color4f( 0.8f, 0.8f, 1.0f, 0.4f);
    
    m_bIsOccupied= false;
    
    m_bIsPaddingTile = false;
}
/*
Color4f Tile:: GetColor()
{
    Color4f cellColor;
    
    if( m_eCellState == ECT_EMPTY )
    {
        cellColor = CELL_COLOR_EMPTY;
    }
    
    else if( m_eCellState == ECT_SOURCE)
    {
        cellColor = CELL_COLOR_SOURCE;
    }
    
    else if( m_eCellState == ECT_TARGET)
    {
        cellColor = CELL_COLOR_TARGET;
    }
    
    else if( m_eCellState == ECT_OCCUPIED)
    {
        cellColor = CELL_COLOR_OCCUPIED;
    }
    
    else if( m_eCellState == ECT_PATH)
    {
        cellColor = CELL_COLOR_PATH;
    }
    else if( m_eCellState == ECT_VISITED)
    {
        cellColor = CELL_COLOR_VISITED;
    }
    else if( m_eCellState == ECT_OPEN)
    {
        cellColor = CELL_COLOR_OPEN;
    }
    else if( m_eCellState == ECT_CLOSED)
    {
        cellColor = CELL_COLOR_CLOSED;
    }
    
    return cellColor;
}
 */

void Tile:: Occupy( bool bOccupy )
{
    m_bIsOccupied = bOccupy;
    
    if( m_bIsOccupied )
        m_eCellState = ECT_OCCUPIED;
    
    else
        m_eCellState = ECT_EMPTY;
}

bool Tile:: IsOccupied()
{
    return m_bIsOccupied;
}

