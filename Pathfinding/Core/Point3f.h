/*
 *  Point2f.h
 *  vektorCocosTry
 *
 *  Created by Vivek Seetharaman on 13/07/10.
 *  Copyright 2010 Sourcebits Technologies . All rights reserved.
 *
 */

#ifndef _POINT3F_
#define _POINT3F_

#include "VektorDataTypes.h"
#include "Point3f.h"

namespace vektor3d
{
	namespace core
	{
		class Point3f
		{
		public:
			f32 x,y,z;			// Position
			
			Point3f();
			Point3f( f32 x, f32 y, f32 z);
			
			Point3f& add( float );
			float distanceTo( const Point3f&);
			
			Point3f& operator=(const Point3f& );
			
			Point3f& operator+(const Point3f&);
			
			Point3f& operator-(const Point3f&);
			
		};
	}
}

#endif;