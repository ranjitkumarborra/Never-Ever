/*
 *  Matrix4f.h
 *  basicTranslate
 *
 *  Created by Vivek Seetharaman on 02/07/10.
 *  Copyright 2010 Sourcebits Technologies . All rights reserved.
 *
 */

#ifndef _MATRIX4F_
#define _MATRIX4F_

//#include "Vector3f.h"
#include "Point3f.h"
#include "Point4f.h"

namespace vektor3d
{
	namespace core
	{
		class Vector3f;
		
		class Matrix4f
		{
		public:
			static const float PI = 3.14159;
			
		public:
			/*  Members */
			// Individual elements 
			float m00, m01, m02, m03;
			float m10, m11, m12, m13;
			float m20, m21, m22, m23;
			float m30, m31, m32, m33;
			
			void swap( float& a, float& b ); // Swaps two floats. Useful in transpose method.
		public:
			/* Constructors */
			Matrix4f();
			//Matrix4f( float *pElements );
			Matrix4f( float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33 );
			//Matrix4f( Matrix4f *pMatrix);
			
			/* Methods */
			// Matrix ops
			void add( Matrix4f mat);							// Adds a matrix and stores the sum
			
			void mul( Matrix4f& mat);							// Multiplies another 4x4 matrix and accumulates result
			
			void mul( Matrix4f& mat1, Matrix4f& mat2 );			// Multiplies two 4x4 matrices and accumulates result
			
			void transpose();									// Transposes Matrix inplace
			
			void mul( float );									// Multiplies by a scalar
			
			void setElements( float e00, float e01, float e02, float e03, float e10, float e11, float e12, float e13, float e20, float e21, float e22, float e23, float e30, float e31, float e32, float e33 );
			
			void setElements( float* );
			
			void setElements(Matrix4f& srcMatrix);
			
			void setIdentity();
			
			void setRotX( float xAngle );
			
			void setRotY( float xAngle );
			
			void setRotZ( float xAngle );
			
			
			void setTranslation( float x, float y, float z);
			
			void setScale( float scaleX, float scaleY, float scaleZ );
			
			// Cumuluative Transforms Similar to glRotate, glTranslate, glScale
			void translate( float x, float y, float z );
			//void scale( float x, float y, float z );
			
			void rotateX( float angle );
			
			void rotateY( float angle );
			
			void rotateZ( float angle );
			
			// Transforms
			void transform( const Point4f&  inPoint , Point4f&  result );

			void transform( const Point3f&  inPoint , Point3f&  result );
			
			void transform( const Vector3f& inVector, Vector3f& result );
			
			void getElements( float *inFloatContainer);
			
			// Projection Matrix Construction
			void setFrustrumProjection( float left, float right, float top, float bottom, float near, float far );
			
			void setPerspectiveProjection( float fov, float aspectRatio, float near, float far );
			
			void setOrthoProjection( float minX, float maxX, float minY, float maxY, float min, float maxZ );
			
			void setBasisVectors( Vector3f& u, Vector3f& v, Vector3f& n );
			
			Vector3f getBasisVectorX();
			
			Vector3f getBasisVectorY();
			
			Vector3f getBasisVectorZ();
			
			
			// View Matrix Setup
			void lookAt( float eyeX, float eyeY, float eyeZ, float targetX, float targetY, float targetZ, float upX, float upY, float upZ );
			
			void invert();
			
			Matrix4f& operator =(  const Matrix4f& in );
			
			//private:
			void DEBUG_PRINT_MATRIX();
			
		};
		
	}
}
#endif