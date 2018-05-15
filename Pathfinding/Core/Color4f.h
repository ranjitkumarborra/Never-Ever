/*
 *  Color3f.h
 *  Vektor3D
 *
 *  Created by Vivek Seetharaman on 24/03/11.
 *  Copyright 2011 Sourcebits Technologies . All rights reserved.
 *
 */

#ifndef _COLOR4F_
#define _COLOR4F_

#include "VektorDataTypes.h"

namespace vektor3d
{
	namespace core
	{
		class Color4f
		{
		public:
			f32 R;
			f32 G;
			f32 B;
			f32 A;
			
		public:
			Color4f( f32 red=1.0f, f32 green=1.0f, f32 blue=1.0f, f32 alpha = 1.0f);
			
			void Scale( float, float , float , float );
			
			
		};
	}
}

#endif