//
//  TileMap.h
//  testGlut
//
//  Created by Vivek Seetharaman on 4/1/13.
//  Copyright 2013 Sourcebits Technologies. All rights reserved.
//

#ifndef testGlut_TileMap_h
#define testGlut_TileMap_h


#include "Point2f.h"
#include "Color4f.h"
#include "Tile.h"
#include "CollisionGraph.h"
#include <vector>

using namespace std;

class TileMap
{
public:
    TileMap( int tileCount_X, int tileCount_Y, int tileSize );
    
    void Initialize();
    
    void PopulateCellColorList();
    
    void Render();
    
    int  Pick( int x, int y);
    
    void Occupy( bool bOccupy, int tileID, int radius = 0 );
    
    void HighlightTiles( vector<int> tileIDs );
    
    void SetTileState( int tileID, E_CELL_STATE eCellState );
    
    E_CELL_STATE GetTileState( int tileID );
    
    void OnLeftMouseClick( int x, int y);
    
    void OnRightMouseClick( int x, int y);

    // Accessor Methods
    
    int  GetBrushRadius();
    
    void SetBrushRadius( int );
    
    CollisionGraph* GetCollisionGraph();
    
    void SetCollisionGraph( CollisionGraph* );
    
    void SetSourcePosition( Point2f P );
    
    void SetTargetPosition( Point2f P );
    
    vector<int> GetSpiralTileIDs( int centerTileID, int number );
        
    Point2f GetSourcePosition();
    
    Point2f GetTargetPosition();
    
    int GetSourceNodeID();
    
    int GetTargetNodeID();
    
    void Refresh();   // Leaves the obstacles in place, clears other cell states to ECT_EMPTY
    
    void Reset();     // Resets TileMap to a brand new state.
    
    void SetOffset( int x, int y);
    
    Point2f m_Offset;

    int m_TileSize;

    int m_Tiles_X;
    
    int m_Tiles_Y;
    
    Tile* m_pTileArray;

    
private:
    
    CollisionGraph *m_pCollisionGraph;
        
    Point2f mouseClickPos;
    
    int m_BrushRadius;
    
    // Physical Position
    Point2f m_SourcePosition;   
    
    Point2f m_TargetPosition;
    
    // Node/Tile ID
    int m_SourceNodeID;
    
    int m_TargetNodeID;
    
    vector<Color4f> m_vecCellColorList;
};



#endif
