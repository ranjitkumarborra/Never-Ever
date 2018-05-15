/*
 *  Point2f.mm
 *  vektorCocosTry
 *
 *  Created by Vivek Seetharaman on 13/07/10.
 *  Copyright 2010 Sourcebits Technologies . All rights reserved.
 *
 */

#include "Point3f.h"
#include <math.h>

namespace vektor3d
{
	namespace core
	{
		Point3f::Point3f()
		{
			x=0;
			y=0;
			z=0;
		}
		Point3f::Point3f( float xx, float yy, float zz) : x(xx), y(yy), z(zz)
		{
			
		}
		
		float Point3f::distanceTo( const Point3f& p)
		{
			return sqrt( (p.x - x)*(p.x - x) + (p.y - y)*(p.y - y) + (p.z - z)*(p.z - z ) );
		}
		
		Point3f& Point3f:: add( float f)
		{
			x+=f;
			y+=f;
			z+=f;
			
			return *this;
		}
		
		Point3f& Point3f:: operator=(const Point3f& other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
			
			return *this;
		}
		
		Point3f& Point3f::operator+(const Point3f& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			
			return *this;
		}
		
		Point3f& Point3f::operator-(const Point3f& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			
			return *this;
		}

	}
}
