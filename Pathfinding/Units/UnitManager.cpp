//
//  UnitManager.cpp
//  PathFinder
//
//  Created by Rajavanya on 12/04/13.
//
//

#include "UnitManager.h"
#include <OpenGL/gl.h>     // The GL Header File
#include <OpenGL/glext.h>
#include "Point2f.h"
#include "Math.h"
#include "PathManager.h"

void UnitManager::CreateUnitAt( Point2f P )
{
    Unit *t_NewUnit = new Unit( P );
    m_vecUnits.push_back(t_NewUnit);
}

UnitManager::UnitManager()
{
}

UnitManager::~UnitManager()
{
}

void UnitManager::MoveUnitsTo( Point2f P )
{
    srand(time(NULL));
    
    // This is the Destination chosen by the user. All units should move in and around this area
    Point2f t_DestGridCoord;
    
    
    t_DestGridCoord.x = int(P.x/m_TileMap->m_TileSize);
    t_DestGridCoord.y = int(P.y/m_TileMap->m_TileSize);
    
    int destTileID = (t_DestGridCoord.y) * m_TileMap->m_Tiles_X + t_DestGridCoord.x;
    
    
    int numSelectedUnits = m_vecSelectedUnits.size();
    
    vector<int> vecSpiralTileIDs = m_TileMap->GetSpiralTileIDs(destTileID, numSelectedUnits);
    
    printf("\nSpiral Generator\n:");
    for (int i = 0; i < m_vecSelectedUnits.size(); i++)
    {
        Point2f t_UnitPos = m_vecSelectedUnits[i]->getPosition();

        //validation of positions
        int t_SrcTileIndex = m_TileMap->Pick(t_UnitPos.x, t_UnitPos.y);
        int t_DstTileIndex = m_TileMap->Pick(P.x, P.y);
        
        if (t_SrcTileIndex == -1 || t_DstTileIndex == -1)
            break;
        
        Point2f t_UnitGridCoord;
        t_UnitGridCoord.x = int(t_UnitPos.x/m_TileMap->m_TileSize);
        t_UnitGridCoord.y = int(t_UnitPos.y/m_TileMap->m_TileSize);
        
        Point2f targetCoord = m_TileMap->m_pTileArray[vecSpiralTileIDs[i]].m_Coord;
        printf("\n [%f, %f] ", targetCoord.x, targetCoord.y  );
        
        //for each unit, call Path manager "Request" path
        
//        m_vecSelectedUnits[i]->m_Path = this->m_PathFinder->GetPath(t_UnitGridCoord, targetCoord);
//        m_vecSelectedUnits[i]->m_NextWayPointIndex = m_vecSelectedUnits[i]->m_Path.vecNodePoints.size()-1;
        

        PathManager::GetInstance()->RequestForPath(t_UnitGridCoord, targetCoord, m_vecSelectedUnits[i]);
        
//        for (int j = 0; j < m_vecSelectedUnits[i]->m_Path.vecNodePoints.size(); j++)
//        {
//            m_vecSelectedUnits[i]->m_Path.vecNodePoints[j].x = (m_vecSelectedUnits[i]->m_Path.vecNodePoints[j].x+ 0.5)*m_TileMap->m_TileSize;
//            m_vecSelectedUnits[i]->m_Path.vecNodePoints[j].y = (m_vecSelectedUnits[i]->m_Path.vecNodePoints[j].y+ 0.5)*m_TileMap->m_TileSize;
//        }
    }
    
}

void UnitManager::Update(float dt)
{
    for (int i = 0; i < m_vecUnits.size(); i++)
    {
        
        m_vecUnits[i]->Update(dt);
    }
}

void UnitManager::Render()
{
    glColor4f(0.7f, 0.5f, 1.0f, 1.0f);
    
    for (int i = 0; i < m_vecUnits.size(); i++)
    {
        m_vecUnits[i]->Render();
    }
    
    glFlush();
}

void UnitManager:: SetSelectionArea( Point2f selectionStart, Point2f selectionEnd )
{
    m_SelectionBoxTopLeft.x = selectionStart.x <= selectionEnd.x ? selectionStart.x : selectionEnd.x;   // Min X
    m_SelectionBoxTopLeft.y = selectionStart.y >= selectionEnd.y ? selectionStart.y : selectionEnd.y;   // Max Y
     
    m_SelectionBoxBottomRight.x = selectionStart.x >= selectionEnd.x ? selectionStart.x : selectionEnd.x;   // Max X
    m_SelectionBoxBottomRight.y = selectionStart.y <= selectionEnd.y ? selectionStart.y : selectionEnd.y;   // Min Y
}

bool UnitManager:: SelectUnits( Point2f start, Point2f end  )
{
    SetSelectionArea(start, end);
    
    float manhattanDistance = fabs(m_SelectionBoxTopLeft.x-m_SelectionBoxBottomRight.x) + fabs(m_SelectionBoxTopLeft.y-m_SelectionBoxBottomRight.y);
    
    // If there is a valied selection window, then select all units within the window
    if( manhattanDistance > 0 )
    {
        for( int u=0; u<m_vecUnits.size(); u++ )
        {
            // Check Unit Center is within selection box or not
            Unit* pUnit = m_vecUnits[u];
            
           if( pUnit->m_Position.x > m_SelectionBoxTopLeft.x         && 
               pUnit->m_Position.x < m_SelectionBoxBottomRight.x     &&
               pUnit->m_Position.y < m_SelectionBoxTopLeft.y         && 
               pUnit->m_Position.y > m_SelectionBoxBottomRight.y     )
           {
               // Select Units
               pUnit->m_bIsSelected = true;
               
               m_vecSelectedUnits.push_back(pUnit);
           }
           else
           {
               pUnit->m_bIsSelected = false;
           }
               
        }
        
        // Return true if any unit was selected, false otherwise
        bool bSelectionSuccessful = m_vecSelectedUnits.size() > 0 ? true : false;
        
        return bSelectionSuccessful;
    }
    
    return false;
}

void UnitManager:: ClearSelectedUnitsList()
{
    for( int u=0; u<m_vecUnits.size(); u++ )
    {
        m_vecUnits[u]->m_bIsSelected = false;
    }
    m_vecSelectedUnits.clear();
}


