/*
 *  Vertex3D.h
 *  VecktorSpace
 *
 *  Created by Vivek Seetharaman on 26/08/10.
 *  Copyright 2010 Sourcebits Technologies . All rights reserved.
 *
 */

#ifndef _VERTEX3D_
#define _VERTEX3D_

#include "Color4f.h"
#include "Matrix4f.h"
#include "Vector3f.h"
#include <vector>

using namespace std;
namespace vektor3d
{
	namespace core
	{
		enum E_VERTEX_TYPE
		{
			EVT_STANDARD = 0,   // Vertex, Color, Normal
		};
		
		class Vertex3D
		{
			
		public:
			
			// Vertex Info
			float x,y,z;
			
			float nx,ny,nz;
			
			float s,t;
			
			Color4f color;
			
			// Tangent Space
			Matrix4f m_TBN_Matrix;
			
			// Ambient Occlusion
			float AOCoefficient;
			
			Vector3f m_BentNormal;						// General Direction of Uncoccluded Light
			
			float m_HemiSphericalDiffuseComponent;		
			
			// Connectivity Information
			vector< Vertex3D* > m_vecNeighbors;

		public:	
			// Mesthods
			Vertex3D();
			
			Vertex3D( float x, float y, float z,  float nx=0.0f, float ny=1.0f, float nz=0.0f, float s=0.0f, float t=0.0f );
			
			bool AddNeighbor( Vertex3D* v);
			
			bool HasNeighbor( Vertex3D* v);
			
			//Vertex3D& operator=(const Vertex3D& );

		};
	}
}

#endif