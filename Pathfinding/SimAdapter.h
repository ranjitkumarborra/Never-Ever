//
//  SimAdapter.h
//  PathFinder
//
//  Created by Joe Engalan on 4/9/13.
//
//

#ifndef __PathFinder__SimAdapter__
#define __PathFinder__SimAdapter__

#include <iostream>
#include <list>

namespace Simulation
{
    class UnitDefinition;
    class Manager;
    class Commander;
    class Unit;
    class UnitDefinition;
    
    typedef struct _UnitData
    {
        float x, y; // Position
        float dx, dy; // Direction
        float radius;
        float color[3];
    } UnitData;
    typedef std::list<UnitData> UnitDataList;
    
    class SimulationAdapter
    {
    public:
        SimulationAdapter();
        ~SimulationAdapter();
        
        void Init();
        void Update();
        
        bool HandleLeftButtonDown(int x, int y);
        bool HandleMouseDrag(int x, int y);
        bool HandleLeftButtonUp(int x, int y);
        bool HandleKeyPress(unsigned char key, bool isShiftDown);
        
        void GetUnits(std::list<UnitData>& units) const;
        
        void SetTileScale(float tileScale);
        
    private:
        Manager *m_pManager;
        Commander *m_pPlayer;
        Commander *m_pEnemy;
        
        enum InputState
        {
            None = 0,
            PlaceUnit
        };
        InputState m_CurrentInputState;
        UnitDefinition *m_pCurrentUnitDef;
        Commander *m_pCurrentCommander;
        
        // The size of a tile in virtual units 
        float m_TileScale;
        
        bool m_IsRunning;
        
        bool m_IsDeploying;
        float m_CurrentDeployTime;
        float m_DeployX, m_DeployY;
    };
}

#endif /* defined(__PathFinder__SimAdapter__) */
