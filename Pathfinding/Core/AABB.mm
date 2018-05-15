/*
 *  AABB.mm
 *  Sprite Engine Prototype
 *
 *  Created by Vivek Seetharaman on 31/08/10.
 *  Copyright 2010 Sourcebits Technologies . All rights reserved.
 *
 */

#include "AABB.h"


AABB::AABB()
{
	m_BoundsMin.x = 0.0f;
	m_BoundsMin.y = 0.0f;
	
	m_BoundsMax.x = 1.0f;
	m_BoundsMax.y = 1.0f;
}


AABB::AABB(Point2f& minPoint ,Point2f& maxPoint ):m_BoundsMin(minPoint),m_BoundsMax(maxPoint)
{
}

void AABB::addPoint( Point2f& newPoint )
{
	
}