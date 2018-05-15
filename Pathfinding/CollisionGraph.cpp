//
//  CollisionMap.cpp
//  testGlut
//
//  Created by Vivek Seetharaman on 4/2/13.
//  Copyright 2013 Sourcebits Technologies. All rights reserved.
//

#include <iostream>
#include "CollisionGraph.h"

#define INDEX(i,j) ((j)*m_X_Nodes+(i))

CollisionGraph:: CollisionGraph( int x, int y)
{
    m_X_Nodes = x;
    
    m_Y_Nodes = y;
    
    m_NodeCount = x*y;
    
    m_pNodes = new Node[x*y];
    
    InitializeNodes();
}

void CollisionGraph:: InitializeNodes()
{
    for( int i=0; i<m_NodeCount; i++ )
    {
        m_pNodes[i].m_ID   = i;
        
        m_pNodes[i].m_Cost = 1;
    }
    
    for( int j=0; j<m_Y_Nodes; j++ )
    {
        for( int i=0; i<m_X_Nodes; i++)
        {
            int id = j*m_X_Nodes + i;
            
            Point2f gridCoord = Point2f( i, j );
            
            m_pNodes[id].m_ID   = id;
           
            m_pNodes[id].m_Cost = 1;
            
            m_pNodes[id].m_Coord = gridCoord;
            
            m_pNodes[id].m_bIsPadNode = false;
        }
    }
    
    //ConstructEdges();
}



/*
void CollisionGraph:: ConstructEdges()
{
    Point2f arrNeighbors[4];
    for( int j=0; j<m_Y_Nodes; j++ )
    {
        for( int i=0; i<m_X_Nodes; i++ )
        {
            // Current Node
            Node *pNode = GetNode( i, j );
            
            // Find Neighbor coordinates
            Point2f L_Coord = Point2f( i-1  , j   );
            Point2f R_Coord = Point2f( i+1, j   );
            Point2f T_Coord = Point2f( i  , j+1 );
            Point2f B_Coord = Point2f( i  , j-1 );
            
            arrNeighbors[0] = L_Coord;
            arrNeighbors[1] = T_Coord;
            arrNeighbors[2] = R_Coord;
            arrNeighbors[3] = B_Coord;
            
            // Find valid neighbors and add to neighbor list
            for( int i=0; i<4; i++ )
            {
                Point2f nodeCoord = arrNeighbors[i];
                
                if( nodeCoord.x<0 || nodeCoord.x >= m_X_Nodes || nodeCoord.y<0 || nodeCoord.y>=m_Y_Nodes )
                {
                    continue;
                }
                
                int toID = nodeCoord.y * m_X_Nodes + nodeCoord.x;
                
                pNode->neighborIDs.push_back(toID);
            }
            
        }// i loop
    }// j Loop
}*/

/*
void CollisionGraph:: ConstructEdges()
{
    for( int j=1; j<m_Y_Nodes-1; j++ )
    {
        for( int i=1; i<m_X_Nodes-1; i++ )
        {
            // Current Node
            Node *pNode = GetNode( i, j );
            
            pNode->neighborIDs.push_back( INDEX( i+1, j  ));
            pNode->neighborIDs.push_back( INDEX( i+1, j+1));
            
            pNode->neighborIDs.push_back( INDEX( i  , j+1));
            pNode->neighborIDs.push_back( INDEX( i-1, j+1));
            
            pNode->neighborIDs.push_back( INDEX( i-1, j  ));
            pNode->neighborIDs.push_back( INDEX( i-1, j-1));
            
            pNode->neighborIDs.push_back( INDEX( i  , j-1 ));
            pNode->neighborIDs.push_back( INDEX( i+1, j-1 ));
            
            
            
        }// i loop
    }// j Loop
}
 */

int  CollisionGraph:: GetNeighbors( int x, int y, Node **pNeighbors )
{
    pNeighbors[0] = &m_pNodes[ INDEX( x+1, y)   ];
    pNeighbors[1] = &m_pNodes[ INDEX( x+1, y+1) ];
    pNeighbors[2] = &m_pNodes[ INDEX( x  , y+1) ];
    pNeighbors[3] = &m_pNodes[ INDEX( x-1, y+1) ];
    pNeighbors[4] = &m_pNodes[ INDEX( x-1, y  ) ];
    pNeighbors[5] = &m_pNodes[ INDEX( x-1, y-1) ];
    pNeighbors[6] = &m_pNodes[ INDEX( x  , y-1) ];
    pNeighbors[7] = &m_pNodes[ INDEX( x+1, y-1) ];
    
    return 8;
}

int  CollisionGraph:: GetNeighbors( int nodeID,  Node **pNeighbors )
{
    int x = m_pNodes[nodeID].m_Coord.x;
    
    int y = m_pNodes[nodeID].m_Coord.y;
    
    return GetNeighbors(x, y, pNeighbors);
}




void CollisionGraph:: SetCost( int ID, float cost )
{
    m_pNodes[ ID ].m_Cost = cost;
}


Node* CollisionGraph:: GetNode( int ID)
{
    return &m_pNodes[ ID ];
}

Node* CollisionGraph:: GetNode( int x, int y )
{
    return &m_pNodes[ y*m_X_Nodes+ x ];
}

int CollisionGraph:: GetNodeID( int x, int y)
{
    Node* pNode = &m_pNodes[ y*m_X_Nodes+ x ];
    
    return pNode->m_ID;
}

int CollisionGraph:: GetCost( int x, int y)
{
    Node* pNode = &m_pNodes[ y*m_X_Nodes+ x ];
    
    return pNode->m_Cost;

}

int CollisionGraph:: GetCost( int ID )
{
    Node* pNode = &m_pNodes[ ID ];
    return pNode->m_Cost;
}

int CollisionGraph:: GetNodeCountX()
{
    return m_X_Nodes;
}

int CollisionGraph::GetNodeCountY()
{
    return m_Y_Nodes;
}

void CollisionGraph:: PrintNodes()
{
    for( int i=0; i<m_NodeCount; i++ )
    {
        printf("\n Node #%d\n", i);
       
        //for( int j=0; j<m_pNodes[i].neighborIDs.size(); j++ )
        {
          //  printf("\t %d", m_pNodes[i].neighborIDs[j] );
        }
    }
}

// Clears all node costs
void CollisionGraph:: Reset() 
{
    for( int n=0; n<m_NodeCount; n++ )
    {
        m_pNodes[n].m_Cost = 0;
    }
}