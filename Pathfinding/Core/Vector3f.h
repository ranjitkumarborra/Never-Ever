/*
 *  Vector3f.h
 *  basicTranslate
 *
 *  Created by Vivek Seetharaman on 19/07/10.
 *  Copyright 2010 Sourcebits Technologies . All rights reserved.
 *
 */

#ifndef _VECTOR3F_
#define _VECTOR3F_

#include "Point3f.h"



namespace vektor3d
{
	namespace core
	{
		
		class Vertex3D;
		
		class Vector3f
		{
		public:
			// Members
			float x;
			float y;
			float z;
			
			// Methods
			Vector3f();
			
			Vector3f( float x, float y, float z);
			
			Vector3f( const Vector3f& v );
			
			Vector3f( Point3f& p1, Point3f& p2);
			
			Vector3f( Vertex3D& v1, Vertex3D& v2);
			
			Vector3f normalize();
			
			float dot( Vector3f& v);
			
			void cross( Vector3f& v);
			
			void cross( Vector3f& v1, Vector3f& v2);
			
			void add( Vector3f& v1);
			
			void negate();
			
			void abs();
			
			void add( Vector3f& v1, Vector3f& v2, Vector3f& v3);
			
			void scale( float);
			
			float length();
			
			Vector3f operator+( const Vector3f& other);
			
			Vector3f& operator=(  const Vector3f& other);
			
		};
	}
}

#endif