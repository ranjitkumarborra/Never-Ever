/*
 *  Vector2f.h
 *  SpriteEngine
 *
 *  Created by Damodar on 04/08/10.
 *  Copyright 2010 Sourcebits. All rights reserved.
 *
 */

#ifndef _VECTOR_2F_H
#define _VECTOR_2F_H
#import "Tuple2f.h"

class Vector2f : public Tuple2f
{
public:
	// Contructors
	
	Vector2f () : Tuple2f( 0.0f, 0.0f )
	{
	}
	
	Vector2f (float inX, float inY) : Tuple2f( inX, inY )
	{
	}
	
	Vector2f (const Tuple2f &inT1);
	
	void cross();
	void normalize();
	float getMagnitude();
	float dot(const Vector2f &inVector);
	float angle(const Vector2f &inVector);
	
};


#endif