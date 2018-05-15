/*
 *  Color3f.cpp
 *  Vektor3D
 *
 *  Created by Vivek Seetharaman on 24/03/11.
 *  Copyright 2011 Sourcebits Technologies . All rights reserved.
 *
 */

#include "Color4f.h"

namespace vektor3d
{
	namespace core
	{
		Color4f:: Color4f( f32 red, f32 green, f32 blue, f32 alpha )
		{
			R = red;
			G = green;
			B = blue;
			A = alpha;
		}
		
		void Color4f:: Scale( float sR, float sG, float sB, float sA)
		{
			R *= sR;
			G *= sG;
			B *= sB;
			A *= sA;
			
		}
	}
}

