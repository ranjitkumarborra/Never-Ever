/*
 *  Line2f.h
 *  Sprite Engine Prototype
 *
 *  Created by Vivek Seetharaman on 10/09/10.
 *  Copyright 2010 Sourcebits Technologies . All rights reserved.
 *
 */
#import "Point2f.h"
#import "Vector2f.h"

#define ZERO    0.00000001f
#define ONE     0.99999999f

class LineSegment2f
{
	
public:
	Point2f start;
	Point2f end;
	Vector2f normalDirection;
	float slope , invslope , constant;
	float length, invLength; 
	
	LineSegment2f():start(0.0f,0.0f),end(0.0f,0.0f),slope(0.0f),constant(0.0f)
	{
		length = 0.0f;
		invLength = 0.0f;
	}
	
	LineSegment2f( Point2f& start , Point2f& end ):start(start),end(end)
	{
		float deltaX = end.x- start.x;
		float deltaY = end.y- start.y;
		
		length = start.distance(end);
		invLength = 0.0f;
	    if( length > 0.0000001f )
			invLength = 1.0f/length;
		
		slope    = deltaY / deltaX ;
		constant = end.y - slope * end.x;
	}
	
	LineSegment2f( float x_s , float y_s , float x_e , float y_e):start(x_s,y_s),end(x_e,y_e)
	{
		float deltaX = end.x- start.x;
		float deltaY = end.y- start.y;
		
		length = start.distance(end);
		invLength = 0.0f;
	    if( length > 0.0000001f )
			invLength = 1.0f/length;
		
		slope    = deltaY / deltaX ;
		constant = end.y - slope * end.x;    // c = y - mx
	}
	
	//class destructor
	~LineSegment2f()
	{
		
	}
	inline float solveForY (  float x )
	{
		return slope * x + constant;
	}
	
	inline float solveForX (  float y )
	{
		return ( y - constant ) * invslope ;
	}
	
	inline bool intersect(LineSegment2f* other, Point2f& intersectionPoint)
	{
		float a = other->end.x - other->start.x;
		float b = other->end.y - other->start.y;
		float c = end.x - start.x;
		float d = end.y - start.y;
				
		float Denominator = b*c - a*d;
		
		if ( Denominator < 0.00000001f )
			return false;
		
		float e = start.x - other->start.x;
		float f = start.y - other->start.y;
		
		float Numerator1 = a*f - b*e;
		float Numerator2 = c*f - d*e;
		
		if ( Numerator1 < 0.00000001f && Numerator2 < 0.00000001f )
			return false;
		
		float t1 = Numerator1/Denominator;
		float t2 = Numerator2/Denominator;
		
		if( 0.00000001f < t1 && t1 < 0.9999999f && 0.00000001f < t2 && t2 < 0.9999999f )
		{
			intersectionPoint.x = start.x + t1*c;
			intersectionPoint.y = start.y + t1*d;
			return true;
		}
		else 
			return false;
	}

	inline bool intersect( Point2f& point, Point2f& pointOnLine , float offset)
	{
		if( length < 0.000001f )
			return false;
		
		float a = point.x - start.x;
		float b = point.y - start.y;
		float c = end.x   - start.x;
		float d = end.y   - start.y;
		
		float t = ( a*c + b*d ) * invLength * invLength;
		
		if ( t < ZERO - offset || t > ONE + offset )
			return false;
		
		pointOnLine.x = start.x + t*c;
		pointOnLine.y = start.y + t*d;
		
		return true;
	}
};