/*
	This class represents a rotation
*/

#ifndef _MATH_CQUATERNION_H
#define _MATH_CQUATERNION_H

// Forward Declarations
//=====================

namespace Engine
{
	namespace Math
	{
		class Vector3;
	}
}

// Class Declaration
//==================

namespace Engine
{
	namespace Math
	{
		class Quaternion
		{
			// Interface
			//==========

		public:

			static Quaternion getIdentityQuartenion();
			// Concatenation
			Quaternion operator *( const Quaternion& i_rhs ) const;

			// Inversion
			void Invert();
			Quaternion CreateInverse() const;

			// Normalization
			void Normalize();
			Quaternion CreateNormalized() const;

			// Products
			friend float Dot( const Quaternion& i_lhs, const Quaternion& i_rhs );

			// Initialization / Shut Down
			//---------------------------

			Quaternion();	// Identity
			Quaternion( const float i_angleInRadians, const Vector3& i_axisOfRotation_normalized );

			// Data
			//=====

		private:

			float m_w, m_x, m_y, m_z;

			// Implementation
			//===============

		private:

			// Initialization / Shut Down
			//---------------------------

			Quaternion( const float i_w, const float i_x, const float i_y, const float i_z );

			// Friend Classes
			//===============

			friend class Matrix4x4;
		};
	}
}

#endif	// _MATH_CQUATERNION_H
