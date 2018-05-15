//
//  SimAdapter.cpp
//  PathFinder
//
//  Created by Joe Engalan on 4/9/13.
//
//

#include "SimAdapter.h"
#include "../Simulation/Behavior/Manager.h"
#include "../Simulation/vector.h"
#include "../Simulation/Definitions/Militia.h"

using namespace Simulation;
using namespace vector;
using namespace Definitions;

// TIMER
static const float frameTime60FPS = 1.0f / 60.0f;
static clock_t lastTimeStamp = 0;
static clock_t currentTimeStamp = 0;
static float deltaTime = 0.0f;
static const float deployDelay = 0.2f;

float UpdateDeltaTime()
{
    // Get the tick rate.
    currentTimeStamp = clock();
    if(lastTimeStamp == 0)
        lastTimeStamp = currentTimeStamp;
    
    float deltaTime = float(currentTimeStamp - lastTimeStamp) / CLOCKS_PER_SEC;
    lastTimeStamp = currentTimeStamp;
    
    return deltaTime;
}
// TIMER

SimulationAdapter::SimulationAdapter() :
m_TileScale(1.0f),
m_IsRunning(false)
{
}

SimulationAdapter::~SimulationAdapter()
{
    
}

void SimulationAdapter::Init()
{
    m_pManager = new Manager();
    m_pPlayer = m_pManager->AddCommander();
    m_pEnemy = m_pManager->AddCommander();
    m_TileScale = 1.0f;
}

void SimulationAdapter::Update()
{
    float frameTime = UpdateDeltaTime();
    if(m_IsRunning)
    {
        deltaTime += frameTime;
        if(deltaTime >= frameTime60FPS)
        {
            deltaTime -= frameTime60FPS;
            m_pManager->Update(frameTime60FPS);
            
        }

    }
    
    if(m_IsDeploying)
    {
        m_CurrentDeployTime -= frameTime;
        if(m_CurrentDeployTime <= 0.0f)
        {
            Unit *unit = m_pCurrentCommander->AddUnit(*m_pCurrentUnitDef);
            unit->SetPosition(Vector2(m_DeployX / m_TileScale, m_DeployY / m_TileScale));
            unit->SetDirection(Vector2(1.0f, 0.0f));
            m_CurrentDeployTime += deployDelay;
        }
    }
}

bool SimulationAdapter::HandleKeyPress(unsigned char key, bool isShiftDown)
{
    if(key == 'm' || key == 'M')
    {
        m_pCurrentUnitDef = &MilitiaDef;
        m_CurrentInputState = PlaceUnit;
        m_pCurrentCommander = key == 'm' ? m_pPlayer : m_pEnemy;
        return true;
    }
    else if(key == ' ')
    {
        m_IsRunning = !m_IsRunning;
        return true;
    }
    
    return false;
}

bool SimulationAdapter::HandleLeftButtonDown(int x, int y)
{
    if(m_CurrentInputState == PlaceUnit)
    {
        m_IsDeploying = true;
        m_CurrentDeployTime = 0.0f;
        m_DeployX = x;
        m_DeployY = y;
        return true;
    }
    return false;
}

bool SimulationAdapter::HandleMouseDrag(int x, int y)
{
    if(m_CurrentInputState == PlaceUnit)
    {
        m_DeployX = x;
        m_DeployY = y;
        return true;
    }
    
    return false;
}


bool SimulationAdapter::HandleLeftButtonUp(int x, int y)
{
    if(m_CurrentInputState == PlaceUnit)
    {
        m_IsDeploying = false;
        m_CurrentInputState = None;
        
        return true;
    }
    
    return false;
}

void SimulationAdapter::GetUnits(std::list<UnitData>& unitData) const
{
    UnitList units;
    m_pManager->GetAllUnits(units);
    
    for(UnitList::iterator it = units.begin(); units.end() != it; ++it)
    {
        Unit *unit = *it;
        Vector2 position = unit->Position();
        Vector2 direction = unit->Direction();
        
        UnitData data;
        data.x = position.X * m_TileScale;
        data.y = position.Y * m_TileScale;
        data.dx = direction.X;
        data.dy = direction.Y;
        data.radius = unit->Properties().Radius() * m_TileScale;
        
        if(unit->Owner() == m_pPlayer)
        {
            data.color[0] = data.color[1] = data.color[2] = 1.0f;
        }
        else if(unit->Owner() == m_pEnemy)
        {
            data.color[0] = data.color[1] = data.color[2] = 0.5f;
        }
        
        unitData.push_back(data);
    }
}

void SimulationAdapter::SetTileScale(float tileScale)
{
    m_TileScale = tileScale;
}
