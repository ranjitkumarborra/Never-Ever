/*
 *  Point4f.cpp
 *  SDLZombie
 *
 *  Created by Vivek Seetharaman on 28/09/11.
 *  Copyright 2011 Sourcebits Technologies . All rights reserved.
 *
 */

#include "Point4f.h"
#include <math.h>

namespace vektor3d
{
	namespace core
	{
		Point4f::Point4f()
		{
			x=0;
			y=0;
			z=0;
			w=1.0f;
		}
		Point4f::Point4f( float xx, float yy, float zz, float ww) : x(xx), y(yy), z(zz), w(ww)
		{
			
		}
		
		float Point4f::distanceTo( const Point3f& p)
		{
			return sqrt( (p.x - x)*(p.x - x) + (p.y - y)*(p.y - y) + (p.z - z)*(p.z - z ) );
		}
		
		Point4f& Point4f:: add( float f)
		{
			x+=f;
			y+=f;
			z+=f;
			w+=f;
			return *this;
		}
		
		Point4f& Point4f:: operator=(const Point4f& other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
			w = other.w;
			return *this;
		}
		
		Point4f& Point4f::operator+(const Point4f& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
			
			return *this;
		}
		
		Point4f& Point4f::operator-(const Point4f& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;
			
			return *this;
		}
		
	}
}
