//
//  UnitManager.h
//  PathFinder
//
//  Created by Rajavanya on 12/04/13.
//
//

#ifndef __PathFinder__UnitManager__
#define __PathFinder__UnitManager__

#include <iostream>
#include "Point2f.h"
#include <vector>
#include "Unit.h"
#include "PathFinder.h"
#include "TileMap.h"

using namespace std;

class UnitManager {
    vector<Unit*> m_vecUnits;
    
public:
    UnitManager();
   
    ~UnitManager();
    
    void Render();
    
    void Update(float dt);
    
    void CreateUnitAt   ( Point2f P );
    
    void MoveUnitsTo    ( Point2f P );

    bool SelectUnits( Point2f selectionStart, Point2f selectionEnd  );
    
    void ClearSelectedUnitsList();
    
    // Variables
    PathFinder *m_PathFinder;
    
    TileMap *m_TileMap;
    
    Point2f m_SelectionBoxTopLeft;
    
    Point2f m_SelectionBoxBottomRight;
    
    vector<Unit*> m_vecSelectedUnits;
    
private:
    void SetSelectionArea( Point2f selectionStart, Point2f selectionEnd );
    
    
};

#endif /* defined(__PathFinder__UnitManager__) */
