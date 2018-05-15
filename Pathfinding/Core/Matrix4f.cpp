/*
 *  Matrix4f.mm
 *  basicTranslate
 *
 *  Created by Vivek Seetharaman on 02/07/10.
 *  Copyright 2010 Sourcebits Technologies . All rights reserved.
 *
 */

#include "Matrix4f.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "Vector3f.h"

namespace vektor3d
{
	namespace core
	{
		// Default Constructor: Identity
		Matrix4f::Matrix4f()
		{
			setIdentity();
		}
		
		Matrix4f::Matrix4f( float e00, float e01, float e02, float e03,
						   float e10, float e11, float e12, float e13,
						   float e20, float e21, float e22, float e23,
						   float e30, float e31, float e32, float e33 )
		{
			m00 = e00 ; m01 = e01 ; m02 = e02 ; m03 = e03 ;
			m10 = e10 ; m11 = e11 ; m12 = e12 ; m13 = e13 ;
			m20 = e20 ; m21 = e21 ; m22 = e22 ; m23 = e23 ;
			m30 = e30 ; m31 = e31 ; m32 = e32 ; m33 = e33 ;	
		}
		
		
		void Matrix4f::setElements( float e00, float e01, float e02, float e03,
								   float e10, float e11, float e12, float e13,
								   float e20, float e21, float e22, float e23,
								   float e30, float e31, float e32, float e33 )
		{
			m00 = e00 ; m01 = e01 ; m02 = e02 ; m03 = e03 ;
			m10 = e10 ; m11 = e11 ; m12 = e12 ; m13 = e13 ;
			m20 = e20 ; m21 = e21 ; m22 = e22 ; m23 = e23 ;
			m30 = e30 ; m31 = e31 ; m32 = e32 ; m33 = e33 ;	
		}
		
		void Matrix4f::setElements( Matrix4f& srcMatrix )
		{
			m00 = srcMatrix.m00 ; m01 = srcMatrix.m01 ; m02 = srcMatrix.m02 ; m03 = srcMatrix.m03 ;
			m10 = srcMatrix.m10 ; m11 = srcMatrix.m11 ; m12 = srcMatrix.m12 ; m13 = srcMatrix.m13 ;
			m20 = srcMatrix.m20 ; m21 = srcMatrix.m21 ; m22 = srcMatrix.m22 ; m23 = srcMatrix.m23 ;
			m30 = srcMatrix.m30 ; m31 = srcMatrix.m31 ; m32 = srcMatrix.m32 ; m33 = srcMatrix.m33 ;	
		}
		
		
		
		void Matrix4f::setIdentity()
		{
			m00 = 1.0f; m01 = 0.0f; m02 = 0.0f; m03 = 0.0f;
			m10 = 0.0f; m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
			m20 = 0.0f; m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
			m30 = 0.0f; m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
		}
		
		void Matrix4f::setTranslation( float x, float y, float z )
		{
			m03 = x;  
			m13 = y;
			m23 = z;
		}
		
		void Matrix4f::setScale( float x, float y, float z )
		{
			m00 = x;  
			m11 = y;
			m22 = z;
		}
		
		void Matrix4f::setRotX( float angle )
		{
			float xRadian = (PI/180.0) * angle;							// Convert angle to radian
			
			m11 =  cos( xRadian );										// Set Matrix Values
			m12 = -sin( xRadian );
			m21 =  sin( xRadian );
			m22 =  cos( xRadian );
		}
		
		void Matrix4f::setRotY( float angle )
		{
			float xRadian = (PI/180.0) * angle;							// Convert angle to radian
			
			m00 =   cos( xRadian );										// Set Matrix Values
			m02 =   -sin( xRadian );
			m20 =   
			sin( xRadian );
			m22 =   cos( xRadian );
		}
		
		void Matrix4f::setRotZ( float angle )
		{
			float xRadian = (PI/180.0) * angle;							// Convert angle to radian
			
			m00 =   cos( xRadian );										// Set Matrix Values
			m01 =  -sin( xRadian );
			m10 =   sin( xRadian );
			m11 =   cos( xRadian );
		}
		
		
		void Matrix4f::add( Matrix4f mat )
		{
			m00 += mat.m00; m01 += mat.m01; m02 += mat.m02; m03 += mat.m03;
			m01 += mat.m01; m11 += mat.m11; m12 += mat.m12; m13 += mat.m13;
			m02 += mat.m02; m21 += mat.m21; m22 += mat.m22; m23 += mat.m23;
			m03 += mat.m03; m31 += mat.m31; m32 += mat.m32; m33 += mat.m33;	
		}
		
		void Matrix4f::mul( Matrix4f& mat )
		{
			float row0[4], row1[4], row2[4], row3[4];
			row0[0] = (m00*mat.m00 + m01*mat.m10 + m02*mat.m20 + m03*mat.m30); row0[1] = (m00*mat.m01 + m01*mat.m11 + m02*mat.m21 + m03*mat.m31);  row0[2] = (m00*mat.m02 + m01*mat.m12 + m02*mat.m22 + m03*mat.m32);  row0[3] = m00*mat.m03 + m01*mat.m13 + m02*mat.m23 + m03*mat.m33;
			row1[0] = (m10*mat.m00 + m11*mat.m10 + m12*mat.m20 + m13*mat.m30); row1[1] = (m10*mat.m01 + m11*mat.m11 + m12*mat.m21 + m13*mat.m31);  row1[2] = (m10*mat.m02 + m11*mat.m12 + m12*mat.m22 + m13*mat.m32);  row1[3] = m10*mat.m03 + m11*mat.m13 + m12*mat.m23 + m13*mat.m33;
			row2[0] = (m20*mat.m00 + m21*mat.m10 + m22*mat.m20 + m23*mat.m30); row2[1] = (m20*mat.m01 + m21*mat.m11 + m22*mat.m21 + m23*mat.m31);  row2[2] = (m20*mat.m02 + m21*mat.m12 + m22*mat.m22 + m23*mat.m32);  row2[3] = m20*mat.m03 + m21*mat.m13 + m22*mat.m23 + m23*mat.m33;
			row3[0] = (m30*mat.m00 + m31*mat.m10 + m32*mat.m20 + m33*mat.m30); row3[1] = (m30*mat.m01 + m31*mat.m11 + m32*mat.m21 + m33*mat.m31);  row3[2] = (m30*mat.m02 + m31*mat.m12 + m32*mat.m22 + m33*mat.m32);  row3[3] = m30*mat.m03 + m31*mat.m13 + m32*mat.m23 + m33*mat.m33;
			
			// Put result back into matrix
			m00 = row0[0] ; m01 = row0[1] ; m02 = row0[2] ; m03 = row0[3] ;
			m10 = row1[0] ; m11 = row1[1] ; m12 = row1[2] ; m13 = row1[3] ;
			m20 = row2[0] ; m21 = row2[1] ; m22 = row2[2] ; m23 = row2[3] ;
			m30 = row3[0] ; m31 = row3[1] ; m32 = row3[2] ; m33 = row3[3] ;
			
		}
		
		void Matrix4f::mul( Matrix4f& mat, Matrix4f& mat2 )
		{
			float row0[4], row1[4], row2[4], row3[4];
			row0[0] = (mat.m00*mat2.m00 + mat.m01*mat2.m10 + mat.m02*mat2.m20 + mat.m03*mat2.m30); row0[1] = (mat.m00*mat2.m01 + mat.m01*mat2.m11 + mat.m02*mat2.m21 + mat.m03*mat2.m31);  row0[2] = (mat.m00*mat2.m02 + mat.m01*mat2.m12 + mat.m02*mat2.m22 + mat.m03*mat2.m32);  row0[3] = mat.m00*mat2.m03 + mat.m01*mat2.m13 + mat.m02*mat2.m23 + mat.m03*mat2.m33;
			row1[0] = (mat.m10*mat2.m00 + mat.m11*mat2.m10 + mat.m12*mat2.m20 + mat.m13*mat2.m30); row1[1] = (mat.m10*mat2.m01 + mat.m11*mat2.m11 + mat.m12*mat2.m21 + mat.m13*mat2.m31);  row1[2] = (mat.m10*mat2.m02 + mat.m11*mat2.m12 + mat.m12*mat2.m22 + mat.m13*mat2.m32);  row1[3] = mat.m10*mat2.m03 + mat.m11*mat2.m13 + mat.m12*mat2.m23 + mat.m13*mat2.m33;
			row2[0] = (mat.m20*mat2.m00 + mat.m21*mat2.m10 + mat.m22*mat2.m20 + mat.m23*mat2.m30); row2[1] = (mat.m20*mat2.m01 + mat.m21*mat2.m11 + mat.m22*mat2.m21 + mat.m23*mat2.m31);  row2[2] = (mat.m20*mat2.m02 + mat.m21*mat2.m12 + mat.m22*mat2.m22 + mat.m23*mat2.m32);  row2[3] = mat.m20*mat2.m03 + mat.m21*mat2.m13 + mat.m22*mat2.m23 + mat.m23*mat2.m33;
			row3[0] = (mat.m30*mat2.m00 + mat.m31*mat2.m10 + mat.m32*mat2.m20 + mat.m33*mat2.m30); row3[1] = (mat.m30*mat2.m01 + mat.m31*mat2.m11 + mat.m32*mat2.m21 + mat.m33*mat2.m31);  row3[2] = (mat.m30*mat2.m02 + mat.m31*mat2.m12 + mat.m32*mat2.m22 + mat.m33*mat2.m32);  row3[3] = mat.m30*mat2.m03 + mat.m31*mat2.m13 + mat.m32*mat2.m23 + mat.m33*mat2.m33;
			
			// Put result back into matrix
			m00 = row0[0] ; m01 = row0[1] ; m02 = row0[2] ; m03 = row0[3] ;
			m10 = row1[0] ; m11 = row1[1] ; m12 = row1[2] ; m13 = row1[3] ;
			m20 = row2[0] ; m21 = row2[1] ; m22 = row2[2] ; m23 = row2[3] ;
			m30 = row3[0] ; m31 = row3[1] ; m32 = row3[2] ; m33 = row3[3] ;
			
		}
		
		void Matrix4f::swap( float& a, float& b )
		{
			float temp = 0.0f;
			temp = a;
			a=b;
			b=temp;
		}
		
		void Matrix4f::transpose()
		{
			swap( m01, m10 );
			swap( m02, m20 );
			swap( m03, m30 );
			swap( m12, m21 );
			swap( m12, m21 );
			swap( m13, m31 );
			swap( m23, m32 );
		}
		
		
		//void scale( float x, float y, float z )
		//{
		//	
		//}
		
		void Matrix4f::translate( float x, float y, float z )
		{
			Matrix4f matTranslation;									// Make desired Translation matrix
			matTranslation.setTranslation(x, y, z);
			
			this->mul( matTranslation );								// Post multiply with current matrix
		}
		
		void Matrix4f::rotateX( float xAngle )
		{
			Matrix4f matX;												// Construct Rot X matrix
			matX.setRotX( xAngle );
			
			this->mul(matX);											// Multiply with Current Matrix
		}
		
		void Matrix4f::rotateY( float yAngle )
		{
			Matrix4f matY;												// Construct Rot X matrix
			matY.setRotY( yAngle );
			
			this->mul(matY);											// Multiply with Current Matrix
		}
		
		void Matrix4f::rotateZ( float zAngle )
		{
			Matrix4f matZ;												// Construct Rot X matrix
			matZ.setRotZ( zAngle );
			
			this->mul(matZ);											// Multiply with Current Matrix
		}
		
		// PROJECTION MATRIX CONSTRUCTION
		// Helper function that creates Frustrum matrix using FOV,aspect, near , far
		void Matrix4f::setPerspectiveProjection( float fov, float aspectRatio, float near, float far )
		{
			float t = near * tan( fov * 3.1416 / 360.0f );
			float b = -t;
			// Calculate xmin, xmax from aspectRatio
			float r = t * aspectRatio;
			float l = b * aspectRatio;
			// Call Frustrum creator
			//printf("\n\n xmin = %f, xMax=%f, ymin = %f, ymanx=%f", l,r,b,t);
			this->setFrustrumProjection( l, r, t, b, near, far );
			
		}
		
		void Matrix4f::setOrthoProjection( float minX, float maxX, float minY, float maxY, float min, float maxZ )
		{
			
		}
		
		void Matrix4f::setFrustrumProjection( float l, float r, float t, float b, float n, float f )
		{
			// Create the Perpspective projection matrix
			m00 = (2.0f*n)/(r-l)  ; m01 =      0         ; m02 = (r+l)/(r-l)   ; m03 =         0         ;
			m10 =      0          ; m11 = (2.0f*n)/(t-b) ; m12 = (t+b)/(t-b)   ; m13 =         0         ;
			m20 =      0          ; m21 =      0         ; m22 = (-f-n)/(f-n)  ; m23 = (-2.0f*f*n)/(f-n) ;
			m30 =      0          ; m31 =      0         ; m32 =       -1      ; m33 =         0         ;
		}
		
		void Matrix4f::lookAt( float eyeX, float eyeY, float eyeZ, float targetX, float targetY, float targetZ, float upX, float upY, float upZ )
		{
			Vector3f forward( targetX-eyeX, targetY-eyeY, targetZ-eyeZ );
			forward.negate();
			forward.normalize();
			
			Vector3f up( upX, upY, upZ );	
			up.normalize();
			
			Vector3f side(0,0,0);
			
			side.cross( forward, up);
			side.normalize();
			
			// Re-compute upvector
			up.cross(side,forward);
			up.normalize();
			
			// Construct LookAt matrix:
			//    side.x     side.y     side.z       0
			//    up.x       up.y       up.z         0
			//    forward.x  forward.y  forward.z    0
			//    0           0          0           1
			
			m00 = side.x    ;   m01 = up.x   ;   m02 = forward.x  ;   m03 = 0.0f;
			m10 = side.y    ;   m11 = up.y   ;   m12 = forward.y  ;   m13 = 0.0f;
			m20 = side.z    ;   m21 = up.z   ;   m22 = forward.z  ;   m23 = 0.0f;
			m30 = 0.0f       ;   m31 = 0.0f   ;   m32 = 0.0f       ;   m33 = 1.0f;

			//CamMatrix = T * R
			Matrix4f T;
			T.translate( eyeX, eyeY, eyeZ );
			T.mul(*this);
			
			// View matrix is inverse of this.
			
			//V = (T*R)inverse  = inv(R) * inv(T)
		    T.invert();
			
			*this = T;
		}
		
		
		
		
		void Matrix4f::getElements( float *inFloatContainer)
		{
			if( inFloatContainer == NULL ){
				printf("\n ERROR ! Null pointer");		
			}
			
			inFloatContainer[0]  = m00;
			inFloatContainer[1]  = m10;
			inFloatContainer[2]  = m20;
			inFloatContainer[3]  = m30;
			
			inFloatContainer[4]  = m01;
			inFloatContainer[5]  = m11;
			inFloatContainer[6]  = m21;
			inFloatContainer[7]  = m31;
			
			inFloatContainer[8]  = m02;
			inFloatContainer[9]  = m12;
			inFloatContainer[10] = m22;
			
			inFloatContainer[11] = m32;
			
			inFloatContainer[12] = m03;
			inFloatContainer[13] = m13;
			inFloatContainer[14] = m23;
			inFloatContainer[15] = m33;
			
		}
		
		void Matrix4f::transform( const Point4f& p, Point4f& result )             
		{
			result.x = m00*p.x + m01*p.y + m02*p.z + m03*p.w ;
			result.y = m10*p.x + m11*p.y + m12*p.z + m13*p.w ;
			result.z = m20*p.x + m21*p.y + m22*p.z + m23*p.w ;
			result.w = m30*p.x + m31*p.y + m32*p.z + m33*p.w ;
		}
		
		void Matrix4f::transform( const Point3f& p, Point3f& result )             // Assume 'w' is 1.0f
		{
			result.x = m00*p.x + m01*p.y + m02*p.z + m03*1.0 ;
			result.y = m10*p.x + m11*p.y + m12*p.z + m13*1.0 ;
			result.z = m20*p.x + m21*p.y + m22*p.z + m23*1.0 ;
		}
		
		void Matrix4f::transform( const Vector3f& p, Vector3f& result )             // Assume 'w' is 0.0f For transforming a Vector because translating a vector has no meaning
		{
			result.x = m00*p.x + m01*p.y + m02*p.z + m03*0.0 ;
			result.y = m10*p.x + m11*p.y + m12*p.z + m13*0.0 ;
			result.z = m20*p.x + m21*p.y + m22*p.z + m23*0.0 ;
		}
		
		
		void Matrix4f::DEBUG_PRINT_MATRIX()
		{
			printf(" \n\n %f \t %f \t %f \t %f", m00, m01, m02, m03 );
			printf(" \n\n %f \t %f \t %f \t %f", m10, m11, m12, m13 );
			printf(" \n\n %f \t %f \t %f \t %f", m20, m21, m22, m23 );
			printf(" \n\n %f \t %f \t %f \t %f", m30, m31, m32, m33 );
		}
		
		void Matrix4f:: invert()
		{
			float det =   m00*m11*m22*m33 + m00*m12*m23*m31 + m00*m13*m21*m32
			            + m01*m10*m23*m32 + m01*m12*m20*m33 + m01*m13*m22*m30
			            + m02*m10*m21*m33 + m02*m11*m23*m30 + m02*m13*m20*m31
					    + m03*m10*m22*m31 + m03*m11*m20*m32 + m03*m12*m21*m30
			            - m00*m11*m23*m32 - m00*m12*m21*m33 - m00*m13*m22*m31
			            - m01*m10*m22*m33 - m01*m12*m23*m30 - m01*m13*m20*m32
			            - m02*m10*m23*m31 - m02*m11*m20*m33 - m02*m13*m21*m30
						- m03*m10*m21*m32 - m03*m11*m22*m30 - m03*m12*m20*m31 ;
			
			if( det == 0 )
			{
				printf("\n Matrix cannot be inverted: Determinant is ZERO !");
				return;
			}
			
			float b11 = m11*m22*m33 + m12*m23*m31 + m13*m21*m32 - m11*m23*m32 - m12*m21*m33 - m13*m22*m31;
			float b12 = m01*m23*m32 + m02*m21*m33 + m03*m22*m31 - m01*m22*m33 - m02*m23*m31 - m03*m21*m32;
			float b13 = m01*m12*m33 + m02*m13*m31 + m03*m11*m32 - m01*m13*m32 - m02*m11*m33 - m03*m12*m31;
			float b14 = m01*m13*m22 + m02*m11*m23 + m03*m12*m21 - m01*m12*m23 - m02*m13*m21 - m03*m11*m22;
			float b21 = m10*m23*m32 + m12*m20*m33 + m13*m22*m30 - m10*m22*m33 - m12*m23*m30 - m13*m20*m32;
			float b22 = m00*m22*m33 + m02*m23*m30 + m03*m20*m32 - m00*m23*m32 - m02*m20*m33 - m03*m22*m30;
			float b23 = m00*m13*m32 + m02*m10*m33 + m03*m12*m30 - m00*m12*m33 - m02*m13*m30 - m03*m10*m32;
			float b24 = m00*m12*m23 + m02*m13*m20 + m03*m10*m22 - m00*m13*m22 - m02*m10*m23 - m03*m12*m20;
			float b31 = m10*m21*m33 + m11*m23*m30 + m13*m20*m31 - m10*m23*m31 - m11*m20*m33 - m13*m21*m30;
			float b32 = m00*m23*m31 + m01*m20*m33 + m03*m21*m30 - m00*m21*m33 - m01*m23*m30 - m03*m20*m31;
			float b33 = m00*m11*m33 + m01*m13*m30 + m03*m10*m31 - m00*m13*m31 - m01*m10*m33 - m03*m11*m30;
			float b34 = m00*m13*m21 + m01*m10*m23 + m03*m11*m20 - m00*m11*m23 - m01*m13*m20 - m03*m10*m21;
			float b41 = m10*m22*m31 + m11*m20*m32 + m12*m21*m30 - m10*m21*m32 - m11*m22*m30 - m12*m20*m31;
			float b42 = m00*m21*m32 + m01*m22*m30 + m02*m20*m31 - m00*m22*m31 - m01*m20*m32 - m02*m21*m30;
			float b43 = m00*m12*m31 + m01*m10*m32 + m02*m11*m30 - m00*m11*m32 - m01*m12*m30 - m02*m10*m31;
			float b44 = m00*m11*m22 + m01*m12*m20 + m02*m10*m21 - m00*m12*m21 - m01*m10*m22 - m02*m11*m20;
			
			Matrix4f inv;
			inv.setElements(b11,b12,b13,b14, b21,b22,b23,b24, b31,b32,b33,b34, b41,b42,b43,b44);
			inv.mul( 1.0f/det);
			
			this->setElements(inv);
			
		}
		void Matrix4f:: mul( float x)
		{
			m00 *= x; m01*=x; m02*=x; m03*=x;
			m10 *= x; m11*=x; m12*=x; m13*=x;
			m20 *= x; m21*=x; m22*=x; m23*=x;
			m30 *= x; m31*=x; m32*=x; m33*=x;
		}
		
		//Matrix4f& Matrix4f::operator =(  const Matrix4f& in )
//		{
//			float * elements = new float[16];
//			
//			in.getElements( elements);
//			
//			setElements(elements);
//		}
		
		Matrix4f& Matrix4f::operator =(  const Matrix4f& in )
		{
			m00 = in.m00;
			m01 = in.m01;
			m02 = in.m02;
			m03 = in.m03;
			
			m10 = in.m10;
			m11 = in.m11;
			m12 = in.m12;
			m13 = in.m13;
			
			m20 = in.m20;
			m21 = in.m21;
			m22 = in.m22;
			m23 = in.m23;
			
			m30 = in.m30;
			m31 = in.m31;
			m32 = in.m32; 
			m33 = in.m33;
		}
		
	
		void Matrix4f::setElements( float* inFloatContainer)
		{
			m00 = inFloatContainer[0]  ;
			m10 = inFloatContainer[1]  ;
			m20 = inFloatContainer[2]  ;
			m30 = inFloatContainer[3]  ;
			
			m01 = inFloatContainer[4]  ;
			m11 = inFloatContainer[5]  ;
			m21 = inFloatContainer[6]  ;
			m31 = inFloatContainer[7]  ;
			
			m02 = inFloatContainer[8]  ;
			m12 = inFloatContainer[9]  ;
			m22 = inFloatContainer[10] ;
			m32 = inFloatContainer[11] ;
			
			m03 = inFloatContainer[12] ;
			m13 = inFloatContainer[13] ;
			m23 = inFloatContainer[14] ;
			m33 = inFloatContainer[15] ;
		}
		
		void Matrix4f:: setBasisVectors( Vector3f& u, Vector3f& v, Vector3f& n )
		{
			m00 = u.x;	m10 = u.y;	m20 = u.z;
			
			m01 = v.x;	m11 = v.y;	m21 = v.z;
			
			m02 = n.x;	m12 = n.y;	m22 = n.z;
		}
		
		Vector3f Matrix4f:: getBasisVectorX()
		{
			Vector3f x(m00, m10, m20 );
			return x;
		}
		
		
		Vector3f Matrix4f:: getBasisVectorY()
		{
			Vector3f y(m01, m11, m21 );
			return y;
		}
		
		Vector3f Matrix4f:: getBasisVectorZ()
		{
			Vector3f z(m02, m12, m22 );
			return z;
		}
		
		
	}
}







