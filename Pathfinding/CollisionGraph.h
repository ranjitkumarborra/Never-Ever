//
//  CollisionMap.h
//  testGlut
//
//  Created by Vivek Seetharaman on 4/2/13.
//  Copyright 2013 Sourcebits Technologies. All rights reserved.
//

#ifndef testGlut_CollisionMap_h
#define testGlut_CollisionMap_h

#include "Point2f.h"
#include <vector>
#include <list>

using namespace  std;
struct Node
{
    bool m_bIsPadNode;
    
    int m_ID;
    
    float m_Cost;
    
    Point2f m_Coord;
    
    //vector<int> neighborIDs;
};

struct Edge
{
    Edge( int from, int to)
    {
        fromID = from;
        toID = to;
    }
    int fromID;
    int toID;
};


class CollisionGraph
{
    
public:
   
    CollisionGraph( int, int );
    
    inline int GetNodeCount()   { return m_NodeCount; } 
    
    inline Point2f GetGridDimensions()  { return Point2f( m_X_Nodes, m_Y_Nodes ); }
    
    Node* GetNode( int ID );
    
    Node* GetNode( int x, int y );
    
    int GetNodeID( int x, int y);
    
    int GetCost( int x, int y);
    
    int GetCost( int ID );
    
    int GetNodeCountX();
    
    int GetNodeCountY();
    
    int  GetNeighbors( int x, int y, Node **pNeighbors );
    
    int  GetNeighbors( int nodeID,  Node **pNeighbors );
    
    void SetCost( int nodeID, float cost );
    
    void Reset(); // Clears all node costs
    
    //DEBUG
    void PrintNodes();
    
private:
    
    int m_X_Nodes;
        
    int m_Y_Nodes;
    
    int m_NodeCount;
    
    Node* m_pNodes;
    
    void InitializeNodes();
    
    //void ConstructEdges();
    
   };


#endif
