/*
This class represents a position or direction
*/

#ifndef _MATH_VECTOR2_H
#define _MATH_VECTOR2_H

// Class Declaration
//==================

namespace Engine
{
	namespace Math
	{
		class Vector2
		{
			// Interface
			//==========

		public:

			// Addition
			Vector2 operator +(const Vector2& i_rhs) const;
			Vector2& operator +=(const Vector2& i_rhs);

			// Subtraction / Negation
			Vector2 operator -(const Vector2& i_rhs) const;
			Vector2& operator -=(const Vector2& i_rhs);
			Vector2 operator -() const;

			// Multiplication
			Vector2 operator *(const float i_rhs) const;
			Vector2& operator *=(const float i_rhs);
			friend Vector2 operator *(const float i_lhs, const Vector2& i_rhs);

			// Division
			Vector2 operator /(const float i_rhs) const;
			Vector2& operator /=(const float i_rhs);

			// Length / Normalization
			float GetLength() const;
			float Normalize();
			Vector2 CreateNormalized() const;

			// Products
			friend float Dot(const Vector2& i_lhs, const Vector2& i_rhs);
			friend Vector2 Cross(const Vector2& i_lhs, const Vector2& i_rhs);

			// Comparison
			bool operator ==(const Vector2& i_rhs) const;
			bool operator !=(const Vector2& i_rhs) const;

			// Initialization / Shut Down
			//---------------------------

			Vector2(const float i_x = 0.0f, const float i_y = 0.0f, const float i_z = 0.0f);

			// Data
			//=====

			// A vector class is one of the very few examples where I make data public
		public:

			float x, y;

			// Friend Classes
			//===============

			friend class Matrix4x4;
			friend class Quaternion;
		};

		// Friend Function Declarations
		//=============================

		Vector2 operator*(const float i_lhs, const Vector2& i_rhs);
		float Dot(const Vector2& i_lhs, const Vector2& i_rhs);
		Vector2 Cross(const Vector2& i_lhs, const Vector2& i_rhs);
	}
}

#endif	// _MATH_CVECTOR_H
