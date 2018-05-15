/*
 *  Tuple2f.h
 *  SpriteEngine
 *
 *  Created by Damodar on 14/07/10.
 *  Copyright 2010 Sourcebits. All rights reserved.
 *
 */

#ifndef _TUPLE_2F_H
#define _TUPLE_2F_H

class Tuple2f
{
public:
	float x;
	float y;
	
	// Constructors
	
	Tuple2f():x(0.0f),y(0.0f)
	{
	}
	
	Tuple2f(float inX, float inY):x(inX),y(inY)
	{
	}
	
	Tuple2f(const Tuple2f& inOther):x(inOther.x),y(inOther.y)
	{
	}
	
	// Operations on a Tuple object
	
	void absolute();
	void absolute(Tuple2f& outT);
	
	void add(Tuple2f& inT1);
	void add(Tuple2f& inT1, Tuple2f& inT2);
	
	void clamp(float inMin, float inMax);
	void clamp(float inMin, float inMax, Tuple2f& outT);
	
	void clampMax(float inMax);
	void clampMax(float inMax, Tuple2f& outT);

	void clampMin(float inMin);
	void clampMin(float inMin, Tuple2f& outT);
	
	bool equals(Tuple2f& inT);
	
	void negate();
	void negate(Tuple2f& inT1);
	
	void scale(float inScaleFactor);
	void scale(float inScaleFactor, Tuple2f& inT1);
	
	void sub(Tuple2f& inT1);
	void sub(Tuple2f& inT1, Tuple2f& inT2);
	
	// Inline functions
	
	inline void interpolate(Tuple2f& inT1, float inAlpha)
	{
		// this = (1-alpha)*this + alpha*t1
		x = ( (1-inAlpha) * x ) + ( inAlpha * inT1.x );
		y = ( (1-inAlpha) * y ) + ( inAlpha * inT1.y );
	}
	
	inline void interpolate(Tuple2f& inT1, Tuple2f& inT2, float inAlpha)
	{
		// this = (1-alpha)*t1 + alpha*t2
		x = ( (1-inAlpha) * inT1.x ) + ( inAlpha * inT2.x );
		y = ( (1-inAlpha) * inT1.y ) + ( inAlpha * inT2.y );
	}
	
};

#endif
