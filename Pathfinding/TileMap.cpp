//
//  TileMap.cpp
//  testGlut
//
//  Created by Vivek Seetharaman on 4/1/13.
//  Copyright 2013 Sourcebits Technologies. All rights reserved.
//
#include <OpenGL/gl.h>     // The GL Header File
#include <OpenGL/glext.h>
#include <GLUT/GLUT.h>  
#include <iostream>
#include "TileMap.h"
#include "Tile.h"

#define INDEX(i,j) (j)*m_Tiles_X+(i)

Color4f CELL_COLOR_EMPTY       = Color4f( 0.5f, 0.5f, 0.5f, 0.2);
Color4f CELL_COLOR_OCCUPIED    = Color4f( 1.0f, 0.3f, 0.3f, 0.4f);
Color4f CELL_COLOR_VISITED     = Color4f( 0.2f, 0.2f, 0.4f, 0.6f);
Color4f CELL_COLOR_PATH        = Color4f( 0.0f, 0.6f, 0.0f, 1.0f);
Color4f CELL_COLOR_OPEN        = Color4f( 0.0f, 0.7f, 1.0f, 0.25f);
Color4f CELL_COLOR_CLOSED      = Color4f( 0.0f, 0.7f, 1.0f, 0.1f);
Color4f CELL_COLOR_SOURCE      = Color4f( 0.0f, 0.3f, 0.0f, 1.0f);
Color4f CELL_COLOR_TARGET      = Color4f( 0.6f, 0.0f, 0.0f, 1.0f);
Color4f CELL_COLOR_PADDING     = Color4f( 0.3f, 0.3f, 0.0f, 0.2f);


TileMap:: TileMap( int tileCount_X, int tileCount_Y, int tileSize )
{
    m_Tiles_X = tileCount_X+2;
    
    m_Tiles_Y = tileCount_Y+2;
    
    m_TileSize = tileSize;
    
    m_pTileArray = new Tile[ m_Tiles_X * m_Tiles_Y ];
    
    m_pCollisionGraph = new CollisionGraph( m_Tiles_X, m_Tiles_Y );
    
    m_BrushRadius = 1;
    
    m_Offset = Point2f(0,100);
    
    Initialize();
    
    m_SourceNodeID = INDEX(1,1);
    
    m_TargetNodeID = INDEX(2,2);
    
    SetSourcePosition( Point2f( 2.5*m_TileSize,2.5*m_TileSize) + m_Offset );
    
    SetTargetPosition( Point2f( 3.5*m_TileSize, 3.5*m_TileSize) + m_Offset);
    
    PopulateCellColorList();
    
}

void TileMap:: Initialize()
{
    for( int j=0; j<m_Tiles_Y; j++ )
    {
        for( int i=0; i<m_Tiles_X; i++)
        {
            
            int id = j*m_Tiles_X + i;
         
            Point2f gridCoord = Point2f( i, j );
            
            Tile* t = &m_pTileArray[ id ];
            
            t->m_ID = id;
            
            t->m_Coord = gridCoord;
            
            t->m_Cost = 0;
            
            t->m_Pos.x = i*m_TileSize;
            
            t->m_Pos.y = j*m_TileSize;
            
            if( i==0 || i==m_Tiles_X-1 || j == 0 || j == m_Tiles_Y-1 )
            {
                SetTileState( id, ECT_PADDING);
                t->m_bIsPaddingTile = true;
                Node* pNode = m_pCollisionGraph->GetNode(id);
                pNode->m_bIsPadNode = true;
            }
        }
    }
}

void TileMap:: PopulateCellColorList()
{
    m_vecCellColorList.push_back(CELL_COLOR_EMPTY);
    m_vecCellColorList.push_back(CELL_COLOR_OCCUPIED);
    m_vecCellColorList.push_back(CELL_COLOR_VISITED);
    m_vecCellColorList.push_back(CELL_COLOR_PATH);
    m_vecCellColorList.push_back(CELL_COLOR_OPEN);
    m_vecCellColorList.push_back(CELL_COLOR_CLOSED);
    m_vecCellColorList.push_back(CELL_COLOR_SOURCE);
    m_vecCellColorList.push_back(CELL_COLOR_TARGET);
    m_vecCellColorList.push_back(CELL_COLOR_PADDING);
    
}

void TileMap:: Render()
{
    //glClear(GL_COLOR_BUFFER_BIT);	// Clear Screen And Depth Buffer
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    //glLoadIdentity();
    
    
    glTranslatef(m_Offset.x, m_Offset.y, 0);
    
    // Render Tiles
    glBegin( GL_QUADS);
    for( int i=0; i<m_Tiles_X*m_Tiles_Y; i++ )
    {
        Tile* pTile = &m_pTileArray[i];
        
        if( pTile->m_bIsPaddingTile )
            continue;
        
        //Color4f tileColor = pTile->GetColor();
        Color4f tileColor = m_vecCellColorList[ pTile->m_eCellState ];
        
        Point2f pos       = pTile->m_Pos;
        
        int cellSize      = m_TileSize - 2;
        cellSize = cellSize<=0 ? m_TileSize-1 : cellSize;
        cellSize = cellSize<=0 ? 1 : cellSize;
        
        glColor4f(tileColor.R, tileColor.G, tileColor.B, tileColor.A);
        
        glVertex2f( pos.x           , pos.y             );
        glVertex2f( pos.x + cellSize, pos.y             );
        glVertex2f( pos.x + cellSize, pos.y + cellSize  );
        glVertex2f( pos.x           , pos.y + cellSize  );

    }
    glEnd();
    
    glPopMatrix();
    glFlush();    
}

// Given x,y - return the id of the picked tile. -1 if no tile was picked
int  TileMap:: Pick( int x, int y)
{
    int xTile = x/m_TileSize;
    int yTile = y/m_TileSize;
    
    int tileIndex = yTile * m_Tiles_X + xTile;
    
    // If mouse click is outside the tilemap, return -1
    if( tileIndex < 0 || tileIndex > m_Tiles_X*m_Tiles_Y )
        tileIndex = -1;
    
    // if mouse click is on the paddign tiles, return no selection
    if( tileIndex >=0 )
    {
        if( m_pTileArray[tileIndex].m_bIsPaddingTile )
            tileIndex = -1;
    }
    
    return  tileIndex;
}


// TODO: Handle edge cases - What if radius is greater than space to the boundary?
void TileMap:: Occupy( bool bOccupy, int tileID, int radius )
{
    float obstacleCost = 10000;                             // Use a high value so apthfinding does not go through walls.
    // Selected Tile
    Tile* pTile = &m_pTileArray[tileID];
    
    Point2f gridCoord = pTile->m_Coord;
    
    // Occupy a radius of tiles including and around the selected tile
    for( int y = gridCoord.y-radius; y <= gridCoord.y+radius; y++ )
    {
        for( int x = gridCoord.x-radius; x <= gridCoord.x+radius; x++ )
        {
            int tileID = y * m_Tiles_X + x;
          
            pTile = &m_pTileArray[tileID];
            
            pTile->Occupy(bOccupy);
            
            float cost = bOccupy ? obstacleCost : 0.0f;
            
            m_pCollisionGraph->SetCost( tileID, cost);
            
            //m_pCollisionGraph->PrintNodes();
            
        }
    }
}

void TileMap:: HighlightTiles( vector<int> vecTileIDs )
{
    for( int t=0; t<vecTileIDs.size(); t++ )
    {
        SetTileState(vecTileIDs[t], ECT_PATH);
    }
}

void TileMap:: SetTileState( int tileID, E_CELL_STATE eCellState )
{
    if(!( GetTileState(tileID) == ECT_OCCUPIED || GetTileState(tileID) == ECT_SOURCE || GetTileState(tileID) == ECT_TARGET))
   
        m_pTileArray[tileID].m_eCellState = eCellState;
}


// Occupy cells - Fill cells
void TileMap:: OnLeftMouseClick( int x, int y)
{ 
    mouseClickPos = Point2f(x,y);
    
    // Subrtract offset from mouse click postion
    x -= m_Offset.x;
    y -= m_Offset.y;
    
    int tileID = Pick( x, y);

    Occupy( true, tileID, m_BrushRadius );
    
}

// Erase tool - Make cells empty
void TileMap:: OnRightMouseClick( int x, int y)
{ 
    mouseClickPos = Point2f(x,y);
    
    // Subrtract offset from mouse click postion
    x -= m_Offset.x;
    y -= m_Offset.y;
    
    int tileID = Pick( x, y);
    
    Occupy( false, tileID, m_BrushRadius);
}

CollisionGraph* TileMap:: GetCollisionGraph()
{
    return m_pCollisionGraph;
}

void TileMap:: SetCollisionGraph( CollisionGraph *pGraph )
{
    m_pCollisionGraph = pGraph;
}

void TileMap:: SetBrushRadius( int radius)
{
    m_BrushRadius = radius;
}

int TileMap:: GetBrushRadius()
{
    return m_BrushRadius;
}

void TileMap:: SetSourcePosition( Point2f P )
{
    P.x -= m_Offset.x;
    P.y -= m_Offset.y;
    
    m_SourcePosition = P;
    
    int newSourceID = Pick( P.x, P.y);
    
    // Mark Old Source Node as just an empty tile
    m_pTileArray[m_SourceNodeID].m_eCellState = ECT_EMPTY;
    
    m_SourceNodeID = newSourceID;
    
    // Mark new Source Node 
    m_pTileArray[m_SourceNodeID].m_eCellState = ECT_SOURCE;
}

void TileMap:: SetTargetPosition( Point2f P )
{
    P.x -= m_Offset.x;
    P.y -= m_Offset.y;
    
    m_TargetPosition = P;
    
    int newTargetID = Pick( P.x, P.y);
    
    // Mark Old Target Node as just an empty tile
    m_pTileArray[m_TargetNodeID].m_eCellState = ECT_EMPTY;
    
    m_TargetNodeID = newTargetID;
    
    // Mark new Target Node 
    m_pTileArray[m_TargetNodeID].m_eCellState = ECT_TARGET;
}

int TileMap:: GetSourceNodeID()
{
    return m_SourceNodeID;
}


int TileMap:: GetTargetNodeID()
{
    return m_TargetNodeID;
}

Point2f TileMap:: GetSourcePosition()
{
    return m_SourcePosition;
}

Point2f TileMap:: GetTargetPosition()
{
    return m_TargetPosition;
}

void TileMap:: SetOffset( int x, int y)
{
    m_Offset = Point2f(x,y);
}

void TileMap:: Refresh()  // Leaves the obstacles in place, clears other cell states to ECT_EMPTY
{
    for( int t=0; t<m_Tiles_X*m_Tiles_Y; t++ )
    {
        Tile* pTile = &m_pTileArray[t];
        
        if( pTile->m_eCellState != ECT_OCCUPIED && pTile->m_eCellState!= ECT_SOURCE && pTile->m_eCellState!=ECT_TARGET)
            pTile->m_eCellState = ECT_EMPTY;
    }
}

void TileMap:: Reset()     // Resets TileMap to a brand new state. Clear everything
{
    for( int t=0; t<m_Tiles_X*m_Tiles_Y; t++ )
    {
        Tile* pTile = &m_pTileArray[t];
        
        pTile->m_eCellState = ECT_EMPTY;
    }
    
    m_pCollisionGraph->Reset();
}

E_CELL_STATE TileMap:: GetTileState( int tileID )
{
    return m_pTileArray[tileID].m_eCellState;
}

/*
Point2f right( 0, 1)

1 right
1 down
2 left
2 up
3 right
3 down
4 left
4 up
5 right
5 down

  04 05  05  05  05  05
  04 02  03  03  03
  04 02  00  01  03
  04 02  02  01  03
  04 04  04  04  03
*/
#define INDEX( x,y) ((y)*m_Tiles_X+(x))

vector<int> TileMap:: GetSpiralTileIDs( int centerTileID, int tilesNeeded )
{
    Point2f centerTileCoord = m_pTileArray[centerTileID].m_Coord;
    
    Point2f r(  1,  0);
    Point2f d(  0,  -1);
    Point2f l( -1,  0);
    Point2f u(  0, 1);
    
    vector<Point2f> vecDirections;
    vecDirections.push_back( r );
    vecDirections.push_back( d );
    vecDirections.push_back( l );
    vecDirections.push_back( u );
    
    int distanceToWall = 1;
    Point2f currTileCoord = centerTileCoord;
    
    vector<int> vecSpiralTileIDs;
    vecSpiralTileIDs.push_back(centerTileID);
    int count = 0;
    int dIndex=0; // direction index
    
    //printf("\n\n Spiral \n");
    while( count < tilesNeeded )
    {
        for( int s=0; s<2; s++ )
        {
            for( int c=0; c<distanceToWall; c++ )
            {
                currTileCoord.x += vecDirections[dIndex].x;
                currTileCoord.y += vecDirections[dIndex].y;
            
                vecSpiralTileIDs.push_back(INDEX( currTileCoord.x, currTileCoord.y  ));
                count++;
                
               // printf("\n\t %f, %f", currTileCoord.x, currTileCoord.y);
                
                if( count >= tilesNeeded )
                    break;
                
                
            }
            dIndex++;
            dIndex = dIndex == 4 ? 0 : dIndex;
        }
        distanceToWall++;
        
    }
    
    return vecSpiralTileIDs;
}

