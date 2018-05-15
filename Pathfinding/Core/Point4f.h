/*
 *  Point4f.h
 *  SDLZombie
 *
 *  Created by Vivek Seetharaman on 28/09/11.
 *  Copyright 2011 Sourcebits Technologies . All rights reserved.
 *
 */


#ifndef _POINT4F_
#define _POINT4F_

#include "Point3f.h"
#include "VektorDataTypes.h"

namespace vektor3d
{
	namespace core
	{
		class Point4f
		{
		public:
			f32 x,y,z,w;			// Position
			
			Point4f();
			Point4f( f32 x, f32 y, f32 z, f32 w=1.0f);
			
			Point4f& add( float );
			float distanceTo( const Point3f&);
			
			Point4f& operator=(const Point4f& );
			
			Point4f& operator+(const Point4f&);
			
			Point4f& operator-(const Point4f&);
			
		};
	}
}

#endif;