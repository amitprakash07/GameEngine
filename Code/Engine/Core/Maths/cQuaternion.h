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
		class cVector;
	}
}

// Class Declaration
//==================

namespace Engine
{
	namespace Math
	{
		class cQuaternion
		{
			// Interface
			//==========

		public:

			static cQuaternion getIdentityQuartenion();
			// Concatenation
			cQuaternion operator *( const cQuaternion& i_rhs ) const;

			// Inversion
			void Invert();
			cQuaternion CreateInverse() const;

			// Normalization
			void Normalize();
			cQuaternion CreateNormalized() const;

			// Products
			friend float Dot( const cQuaternion& i_lhs, const cQuaternion& i_rhs );

			// Initialization / Shut Down
			//---------------------------

			cQuaternion();	// Identity
			cQuaternion( const float i_angleInRadians, const cVector& i_axisOfRotation_normalized );

			// Data
			//=====

		private:

			float m_w, m_x, m_y, m_z;

			// Implementation
			//===============

		private:

			// Initialization / Shut Down
			//---------------------------

			cQuaternion( const float i_w, const float i_x, const float i_y, const float i_z );

			// Friend Classes
			//===============

			friend class cMatrix_transformation;
		};
	}
}

#endif	// _MATH_CQUATERNION_H
