/*
 *  Point2f.h
 *  SpriteEngine
 *
 *  Created by Damodar on 04/08/10.
 *  Copyright 2010 Sourcebits. All rights reserved.
 *
 */

#ifndef _POINT_2F_H
#define _POINT_2F_H

#import "Tuple2f.h"

class Point2f : public Tuple2f
{
public:
	Point2f () : Tuple2f(0.0f, 0.0f)
	{
	}

	Point2f (float inX, float inY) : Tuple2f(inX, inY)
	{
	}

	Point2f (const Point2f &inPt) : Tuple2f(inPt.x,inPt.y)
	{
	}
	
	Point2f (const Tuple2f &inT);
	
	Point2f operator-(Point2f other );
	Point2f operator+(Point2f other );
	
	Point2f operator+=(const Point2f other );
	
	float distance (const Point2f &inPt1);
	
};

#endif