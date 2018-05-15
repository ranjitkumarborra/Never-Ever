/*
 *  Point2f.cpp
 *  SpriteEngine
 *
 *  Created by Damodar on 04/08/10.
 *  Copyright 2010 Sourcebits. All rights reserved.
 *
 */
#include "Tuple2f.h"
#include "Point2f.h"
#include "math.h"


Point2f::Point2f (const Tuple2f &inT) : Tuple2f( inT.x, inT.y)
{
}

Point2f Point2f:: operator-(Point2f other )
{
	Point2f diff;
	diff.x = x - other.x;
	diff.y = y - other.y;
	
	return diff;
}

Point2f Point2f:: operator+(Point2f other )
{
	Point2f sum;
	sum.x = x + other.x;
	sum.y = y + other.y;
	
	return sum;
}

Point2f Point2f:: operator+=(const Point2f other )
{
	
	x = x + other.x;
	y = y + other.y;
	
	return *this;
}


float Point2f::distance (const Point2f &inPt1)
{
	float xsquared = powf((x - inPt1.x), 2);
	float ysquared = powf((y - inPt1.y), 2);
	
	float distance = sqrtf( (xsquared + ysquared) );
	
	return distance;
}