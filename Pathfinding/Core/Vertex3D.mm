/*
 *  Vertex3D.mm
 *  VecktorSpace
 *
 *  Created by Vivek Seetharaman on 26/08/10.
 *  Copyright 2010 Sourcebits Technologies . All rights reserved.
 *
 */

#include "Vertex3D.h"

namespace vektor3d
{
	namespace core
	{
		Vertex3D::Vertex3D()
		{
			x=0.0f; 
			y=0.0f; 
			z=0.0f;
			
			nx = 0.0f; 
			ny = 1.0f;
			nz = 1.0f;
			
			s = 0.0f; 
			t = 0.0f;
			
			color = Color4f( 0.5f, 0.6f, 1.0f, 1.0f);
			
			AOCoefficient = 0.0f;
			
			m_HemiSphericalDiffuseComponent = 0.0f;		
			
		}
		Vertex3D::Vertex3D( float xx, float yy, float zz, float nxx , float nyy, float nzz, float ss, float tt )
		{
			x=xx; 
			y=yy; 
			z=zz;
			
			nx = nxx; 
			ny = nyy;
			nz = nzz;
			
			s = ss; 
			t = tt;
		}
		
		bool Vertex3D:: HasNeighbor( Vertex3D *v )
		{
			bool bHasNeighbor = false;
			
			for( int n=0; n<m_vecNeighbors.size(); n++ )
			{
				if( m_vecNeighbors[n] == v )
				{
					bHasNeighbor = true;
					break;
				}
			}
			
			return bHasNeighbor;
		}
		
		bool Vertex3D:: AddNeighbor( Vertex3D *n)
		{
			bool bNeighborExists = HasNeighbor( n );
			
			if( bNeighborExists )
				return false;
			
			m_vecNeighbors.push_back( n );
			return true;
		}
		
		//Vertex3D& Vertex3D:: operator=(const Vertex3D& other)
//		{
//			x = other.x;
//			y = other.y;
//			z = other.z;
//			
//			nx = other.nx; 
//			ny = other.ny; 
//			nz = other.nz; 
//			
//			s = other.s;
//			t = other.t;
//			return *this;
//		}
		
	}
}