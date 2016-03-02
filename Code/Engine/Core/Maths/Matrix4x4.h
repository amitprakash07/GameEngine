/*
	This class represents a full Transform
	(i.e. a 4x4 matrix composed of a 3x3 rotation matrix and a 3 element translation vector)

	Matrix Facts:
		* The float elements are stored as columns
			* In other words, the second float stored is the first element in the second row
			* This is so that all 16 floats can be copied directly to Direct3D or OpenGL
				(Both HLSL and GLSL interpret a matrix's registers to be columns)
		* The vectors are the rows
			* In other words, the first three rows are the rotation and the last row is the translation
			* This is an arbitrary choice, but it is arguably the most common one in computer graphics
				(every other field outside of computer graphics that I know of uses column vectors, though)
			* This matches standard Direct3D but is backwards from standard OpenGL
		* The vectors are right-handed
			* In other words, the first vector is right, the second vector is up, and the third vector is back
			* This is an arbitrary choice; it matches Maya and standard OpenGL, and is backwards from standard Direct3D
*/

#ifndef __MATH_CMATRIX_Transform_H
#define __MATH_CMATRIX_Transform_H

// Forward Declarations
//=====================

namespace Engine
{
	namespace Math
	{
		class Vector3;
		class Quaternion;
	}
}

// Class Declaration
//==================

namespace Engine
{
	namespace Math
	{
		class Matrix4x4
		{			
		public:

			static Matrix4x4 CreateWorldToViewTransform(
				const Quaternion& i_cameraOrientation, const Vector3& i_cameraPosition );
			static Matrix4x4 CreateViewToScreenTransform(
				const float i_fieldOfView_y, const float i_aspectRatio,
				const float i_z_nearPlane = 0.1, const float i_z_farPlane = 100);
			static Matrix4x4 getIdentityMatrix();
			Matrix4x4 operator*(double scalar)const;
			Matrix4x4 operator*(Matrix4x4 i_rhs)const;
			Vector3 mul(Vector3 vector, bool isVector = false)const;
			void operator *=(Matrix4x4 i_rhs);
			Matrix4x4 getTranspose()const;
			void transpose();
			Matrix4x4 getInverse()const;
			void inverse();
			double determinant()const;
			Matrix4x4();
			Matrix4x4( const Quaternion& i_rotation, const Vector3& i_translation );			
		private:
			// Storage is column-major; see notes at the top of the file
			float 
				m_00, m_10, m_20, m_30,
				m_01, m_11, m_21, m_31,
				m_02, m_12, m_22, m_32,
				m_03, m_13, m_23, m_33;	
			Matrix4x4(
				const float i_00, const float i_10, const float i_20, const float i_30,
				const float i_01, const float i_11, const float i_21, const float i_31,
				const float i_02, const float i_12, const float i_22, const float i_32,
				const float i_03, const float i_13, const float i_23, const float i_33 );			
		};
	}
}

#endif	// __MATH_CMATRIX_Transform_H
