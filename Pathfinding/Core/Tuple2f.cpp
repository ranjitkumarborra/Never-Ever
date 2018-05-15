/*
 *  Tuple2f.cpp
 *  SpriteEngine
 *
 *  Created by Damodar on 14/07/10.
 *  Copyright 2010 Sourcebits. All rights reserved.
 *
 */

#include "Tuple2f.h"
#include "math.h"


// Public Functions

void Tuple2f::absolute()
{
	x = fabsf(x);
	y = fabsf(y);
}

void Tuple2f::absolute(Tuple2f& outT)
{
	x = fabsf(outT.x);
	y = fabsf(outT.y);
}

void Tuple2f::add(Tuple2f& inT1)
{
	x = x + inT1.x;
	y = y + inT1.y;
}

void Tuple2f::add(Tuple2f& inT1, Tuple2f& inT2)
{
	x = inT1.x + inT2.x;
	y = inT1.y + inT2.y;
}

void Tuple2f::clamp(float inMin, float inMax)
{
	x = (x < inMin) ? inMin : ( (x > inMax) ? inMax : x);
	y = (y < inMin) ? inMin : ( (y > inMax) ? inMax : y );
}

void Tuple2f::clamp(float inMin, float inMax, Tuple2f& outT)
{
	outT.x = (x < inMin) ? inMin : ( (x > inMax) ? inMax : x );
	outT.y = (y < inMin) ? inMin : ( (y > inMax) ? inMax : y );
}

void Tuple2f::clampMax(float inMax)
{
	x = (x > inMax) ? inMax : x;
	y = (y > inMax) ? inMax : y;
}

void Tuple2f::clampMax(float inMax, Tuple2f& outT)
{
	outT.x = (x > inMax) ? inMax : x;
	outT.y = (y > inMax) ? inMax : y;
}

void Tuple2f::clampMin(float inMin)
{
	x = (x < inMin) ? inMin : x;
	y = (y < inMin) ? inMin : y;
}

void Tuple2f::clampMin(float inMin, Tuple2f& outT)
{
	outT.x = (x < inMin) ? inMin : x;
	outT.y = (y < inMin) ? inMin : y;
}

bool Tuple2f::equals(Tuple2f& inT)
{
	bool returnValue = false;
	
	if( fabsf(inT.x - x) < 0.0001 )
		if( fabsf(inT.y - y) < 0.0001 )
			returnValue = true;
	
//	if( (x <= inT.x) && ( (inT.x - x) < 0.0001 ) )
//		if( (y <= inT.y) && ( (inT.y - y) < 0.0001 ) )		
//			returnValue = true;
	
//	if( (x >= inT.x) && ( (x - inT.x) < 0.0001 ) )
//		if( (y >= inT.y) && ( (y - inT.y) < 0.0001 ) )
//			returnValue = true;
	
	return returnValue;
}

void Tuple2f::negate()
{
	x = -(x);
	y = -(y);
}

void Tuple2f::negate(Tuple2f& inT1)
{
	x = -(inT1.x);
	y = -(inT1.y);
}

void Tuple2f::scale(float inScaleFactor)
{
	x = x*inScaleFactor;
	y = y*inScaleFactor;
}

void Tuple2f::scale(float inScaleFactor, Tuple2f& inT1)
{
	x = inT1.x*inScaleFactor;
	y = inT1.y*inScaleFactor;
}

void Tuple2f::sub(Tuple2f& inT1)
{
	x = x - inT1.x;
	y = y - inT1.y;
}

void Tuple2f::sub(Tuple2f& inT1, Tuple2f& inT2)
{
	x = inT1.x - inT2.x;
	y = inT1.y - inT2.y;
}

