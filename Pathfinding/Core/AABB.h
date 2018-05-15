/*
 *  AABB.h
 *  Sprite Engine Prototype
 *
 *  Created by Vivek Seetharaman on 31/08/10.
 *  Copyright 2010 Sourcebits Technologies . All rights reserved.
 *
 */
#import "Point2f.h"

class AABB
{
	
// Members
public:
	Point2f m_BoundsMin;
	Point2f m_BoundsMax;
	
public:
	AABB();
	AABB(Point2f& minPoint ,Point2f& maxPoint );
	void addPoint( Point2f& newPoint );

};