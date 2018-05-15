/*
 *  Matrix3f.mm
 *  vektorCocosTry
 *
 *  Created by Vivek Seetharaman on 27/07/10.
 *  Copyright 2010 Sourcebits Technologies . All rights reserved.
 *
 */
/*
 *  Matrix4f.mm
 *  basicTranslate
 *
 *  Created by Vivek Seetharaman on 02/07/10.
 *  Copyright 2010 Sourcebits Technologies . All rights reserved.
 *
 */

#include "Matrix3f.h"

// Default Constructor: Identity
Matrix3f::Matrix3f()
{
	setIdentity();
}

void Matrix3f::setIdentity()
{
	m00 = 1.0f; m01 = 0.0f; m02 = 0.0f; 
	m10 = 0.0f; m11 = 1.0f; m12 = 0.0f; 
	m20 = 0.0f; m21 = 0.0f; m22 = 1.0f; 	
}

void Matrix3f::setTranslation( float x, float y )
{
	m02 = x;  
	m12 = y;
}

void Matrix3f::setScale( float sx, float sy)
{
	m00 = sx;  
	m11 = sy;
}

void Matrix3f::setRotation( float angle )
{
	float xRadian = (M_PI/180.0) * angle;							// Convert angle to radian
	
	m00 =  cos( xRadian );										// Set Matrix Values
	m01 =  sin( xRadian );
	m10 =  -sin( xRadian );
	m11 =  cos( xRadian );
}


void Matrix3f::mul( Matrix3f& mat )
{
	float row0[3], row1[3], row2[3];
	row0[0] = (m00*mat.m00 + m01*mat.m10 + m02*mat.m20); row0[1] = (m00*mat.m01 + m01*mat.m11 + m02*mat.m21 );  row0[2] = (m00*mat.m02 + m01*mat.m12 + m02*mat.m22 ); 	
	row1[0] = (m10*mat.m00 + m11*mat.m10 + m12*mat.m20); row1[1] = (m10*mat.m01 + m11*mat.m11 + m12*mat.m21 );  row1[2] = (m10*mat.m02 + m11*mat.m12 + m12*mat.m22 );	
	row2[0] = (m20*mat.m00 + m21*mat.m10 + m22*mat.m20); row2[1] = (m20*mat.m01 + m21*mat.m11 + m22*mat.m21 );  row2[2] = (m20*mat.m02 + m21*mat.m12 + m22*mat.m22 );  
	
	// Put result back into matrix
	m00 = row0[0] ; m01 = row0[1] ; m02 = row0[2] ; 
	m10 = row1[0] ; m11 = row1[1] ; m12 = row1[2] ; 
	m20 = row2[0] ; m21 = row2[1] ; m22 = row2[2] ;
	
}

void Matrix3f::translate( float x, float y )
{
	Matrix3f matTranslation;								// Make desired Translation matrix
	matTranslation.setTranslation(x, y);
	
	this->mul( matTranslation );								// Post multiply with current matrix
}

void Matrix3f::rotate( float xAngle )
{
	Matrix3f matX;												// Construct Rot X matrix
	matX.setRotation( xAngle );
	
	this->mul(matX);											// Multiply with Current Matrix
}

void Matrix3f::transform( Point2f& p )
{
	float x00 = p.x , x01 = p.y , x02 = 1;
	
	// matrix multiplication 3 * 3 = 3*1
	
	p.x = ( m00 * x00 + m01 * x01 + m02 * x02 );
	p.y = ( m10 * x00 + m11 * x01 + m12 * x02 );
	x02 = ( m20 * x00 + m21 * x01 + m22 * x02 );	
	
}

void Matrix3f::transform( Vector2f& p )
{
	float x00 = p.x , x01 = p.y , x02 = 1;
	
	// matrix multiplication 3 * 3 = 3*1
	
	p.x = ( m00 * x00 + m01 * x01 + m02 * x02 );
	p.y = ( m10 * x00 + m11 * x01 + m12 * x02 );
	x02 = ( m20 * x00 + m21 * x01 + m22 * x02 );		
}

void Matrix3f::DEBUG_PRINT_MATRIX()
{
//	printf(" \n\n %f \t %f \t %f ", m00, m01, m02);
//	printf(" \n\n %f \t %f \t %f ", m10, m11, m12);
//	printf(" \n\n %f \t %f \t %f ", m20, m21, m22);
}










