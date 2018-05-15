/*
 *  Vector3f.mm
 *  basicTranslate
 *
 *  Created by Vivek Seetharaman on 19/07/10.
 *  Copyright 2010 Sourcebits Technologies . All rights reserved.
 *
 */

#include "Vector3f.h"
#include <math.h>
#include "Vertex3D.h"

namespace vektor3d
{
	namespace core
	{
		Vector3f::Vector3f( )
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}
		
		Vector3f::Vector3f( float xx, float yy, float zz)
		{
			x= xx; y= yy; z= zz;
		}
		
		Vector3f::Vector3f( const Vector3f& v )
		{
			x = v.x;
			y = v.y;
			z = v.z;
		}
		
		// P2-P1
		Vector3f::Vector3f( Point3f& p1, Point3f& p2)
		{
			x = p2.x - p1.x;
			y = p2.y - p1.y;
			z = p2.z - p1.z;
		}
		
		Vector3f::Vector3f( Vertex3D& p1, Vertex3D& p2)
		{
			x = p2.x - p1.x;
			y = p2.y - p1.y;
			z = p2.z - p1.z;
			
		}
		
		Vector3f Vector3f::normalize()
		{
			float mag = sqrt( x*x + y*y + z*z );
			
			x = x/mag;
			y = y/mag;
			z = z/mag;
			
			return *this;
		}
		
		void Vector3f::abs()
		{
			x = x < 0.0 ? x : x;
			y = y < 0.0 ? y : y;
			z = z < 0.0 ? z : z;
			
		}
		float Vector3f::dot( Vector3f& v)							    // Returns scalar dot products of the two vectors: this (dot) v
		{
			return x*v.x + y*v.y + z*v.z;
		}
		
		void Vector3f::cross( Vector3f& v )								// Calculates the vector cross product of this vector and the specified vector and stores result in this vector.
		{
			x =    y*v.z - z*v.y   ;
			y = -( x*v.z - z*v.x ) ;
			z =    x*v.y - y*v.x   ;
		}
		
		void Vector3f::cross( Vector3f& v1, Vector3f& v2 )				// Calculates the vector cross product of the two specified vectors and stores result in this vector.
		{
			x =    v1.y*v2.z - v1.z*v2.y   ;
			y = -( v1.x*v2.z - v1.z*v2.x ) ;
			z =    v1.x*v2.y - v1.y*v2.x   ;
		}
		
		void Vector3f::add( Vector3f& v1)
		{
			x += v1.x;
			y += v1.y;
			z += v1.z;
		}
		
		void Vector3f:: add( Vector3f& v1, Vector3f& v2, Vector3f& v3)
		{
			x = v1.x + v2.x + v3.x;
			y = v1.y + v2.y + v3.y;
			z = v1.z + v2.z + v3.z;
		}

		void Vector3f::scale( float scaleFactor)
		{
			x *= scaleFactor;
			y *= scaleFactor;
			z *= scaleFactor;
		}
		void Vector3f::negate( )
		{
			x = -x;
			y = -y;
			z = -z;
		}
		
		float Vector3f::length()
		{
			float length = pow(  x*x+y*y+z*z , 0.5 );
			return length;
		}
		
		Vector3f& Vector3f::operator=(  const Vector3f& other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
			return *this;
		}
		
		Vector3f Vector3f:: operator+( const Vector3f& other)
		{
			Vector3f sum;
			sum.x = x + other.x;
			sum.y = y + other.y;
			sum.z = z + other.z;
			
			return sum; 
		}

		
	}
}

