/*
 *  Vector2f.cpp
 *  SpriteEngine
 *
 *  Created by Damodar on 04/08/10.
 *  Copyright 2010 Sourcebits. All rights reserved.
 *
 */
#include "Tuple2f.h"
#include "Vector2f.h"
#include "math.h"


Vector2f::Vector2f (const Tuple2f &inT1) : Tuple2f( inT1 )
{
}

void Vector2f::cross()
{
	// Cross product only for Vector3f
}

void Vector2f::normalize()
{
	int xsquared = powf(x, 2);
	int ysquared = powf(y, 2);
	
	float denominator = sqrtf( xsquared + ysquared );
	
	if ( denominator > 0.00000001f )
	{
		x /=  denominator;
		y /=  denominator;
	}
	
}

float Vector2f::getMagnitude()
{
	int xsquared = powf(x, 2);
	int ysquared = powf(y, 2);
	
	float result = sqrtf( xsquared + ysquared );
	
	return result;
}

float Vector2f::dot(const Vector2f &inVector)
{
	float dotProduct = ( x*inVector.x + y*inVector.y );
	return dotProduct;
}

float Vector2f::angle(const Vector2f &inVector)
{
	// Get dot product of the two vectors
	
	//float dotProduct = this->dot(inVector);
//	
//	// Normalize both vectors
//	
//	Vector2f vec1 (x, y);
//	Vector2f vec2 (inVector);
//	vec1.normalize();
//	vec2.normalize();
//	
//	float denominator = vec1.dot((const Vector2f)vec2);
//	
//	// Get the angle /***** cos^-1(a.b/|a||b|) *****/
//	
//	float angleInRads = atan2f(dotProduct/denominator);
	
	////////////////////
	
	float dy = inVector.y - y;
	float dx = inVector.x - x;
	
	float angleInRads = atan2f(dy, dx) + M_PI;

	
	return angleInRads * 180.0 / M_PI; ;
}
