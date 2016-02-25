/*
	This class represents a position or direction
*/

#ifndef _MATH_CVECTOR_H
#define _MATH_CVECTOR_H

// Class Declaration
//==================

namespace Engine
{
	namespace Math
	{
		class Vector3
		{
			// Interface
			//==========

		public:

			// Addition
			Vector3 operator +( const Vector3& i_rhs ) const;
			Vector3& operator +=( const Vector3& i_rhs );

			// Subtraction / Negation
			Vector3 operator -( const Vector3& i_rhs ) const;
			Vector3& operator -=( const Vector3& i_rhs );
			Vector3 operator -() const;

			// Multiplication
			Vector3 operator *( const float i_rhs ) const;
			Vector3& operator *=( const float i_rhs );
			friend Vector3 operator *( const float i_lhs, const Vector3& i_rhs );

			// Division
			Vector3 operator /( const float i_rhs ) const;
			Vector3& operator /=( const float i_rhs );

			// Length / Normalization
			float GetLength() const;
			float Normalize();
			Vector3 CreateNormalized() const;

			// Products
			friend float Dot( const Vector3& i_lhs, const Vector3& i_rhs );
			friend Vector3 Cross( const Vector3& i_lhs, const Vector3& i_rhs );

			// Comparison
			bool operator ==( const Vector3& i_rhs ) const;
			bool operator !=( const Vector3& i_rhs ) const;

			// Initialization / Shut Down
			//---------------------------

			Vector3( const float i_x = 0.0f, const float i_y = 0.0f, const float i_z = 0.0f );

			// Data
			//=====

		// A vector class is one of the very few examples where I make data public
		public:

			float x, y, z;

			// Friend Classes
			//===============

			friend class Matrix4x4;
			friend class Quaternion;
		};

		// Friend Function Declarations
		//=============================

		Vector3 operator*( const float i_lhs, const Vector3& i_rhs );
		float Dot( const Vector3& i_lhs, const Vector3& i_rhs );
		Vector3 Cross( const Vector3& i_lhs, const Vector3& i_rhs );
	}
}

#endif	// _MATH_CVECTOR_H
