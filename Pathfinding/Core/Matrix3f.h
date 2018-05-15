/*
 *  Matrix3f.h
 *  vektorCocosTry
 *
 *  Created by Vivek Seetharaman on 27/07/10.
 *  Copyright 2010 Sourcebits Technologies . All rights reserved.
 *
 */

#ifndef _MATRIX4F_
#define _MATRIX4F_

#import "Vector2f.h"
#import "Point2f.h"
#import <Math.h>


class Matrix3f
{
public:
	static const float PI = 3.14159;
	
public:
	/*  Members */
	// Individual elements 
	float m00, m01, m02;
	float m10, m11, m12;
	float m20, m21, m22;
	
	public:
	/* Constructors */
	Matrix3f();
	
	/* Methods */
	void mul( Matrix3f& mat);							// Multiplies another 4x4 matrix and accumulates result
	void mul( Matrix3f& mat1, Matrix3f& mat2 );			// Multiplies two 4x4 matrices and accumulates result
														//void transpose();									// Transposes Matrix inplace
	
	void setIdentity();
	void setRotation( float xAngle );
    
	
	void setTranslation( float x, float y);
	void setScale( float scaleX, float scaleY);
	
	// Cumuluative Transforms Similar to glRotate, glTranslate, glScale
	void translate( float x, float y );
	void rotate( float angle );
	
	// transform a point
	void transform( Point2f& p );
	void transform( Vector2f& p );	
	
	//private:
	void DEBUG_PRINT_MATRIX();
	
};

#endif