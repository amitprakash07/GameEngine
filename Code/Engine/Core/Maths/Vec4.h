/*
This class represents a position or direction
*/

#ifndef _MATH_CVECTOR_4_H
#define _MATH_CVECTOR_4_H
#include <string>

// Class Declaration
//==================

namespace Engine
{
	namespace Math
	{
		class Vector4
		{
			// Interface
			//==========

		public:

			// Addition
			Vector4 operator +(const Vector4& i_rhs) const;
			Vector4& operator +=(const Vector4& i_rhs);

			// Subtraction / Negation
			Vector4 operator -(const Vector4& i_rhs) const;
			Vector4& operator -=(const Vector4& i_rhs);
			Vector4 operator -() const;

			// Scalar Multiplication
			Vector4 operator *(const float i_rhs) const;
			Vector4& operator *=(const float i_rhs);

			// Division
			Vector4 operator /(const float i_rhs) const;
			Vector4& operator /=(const float i_rhs);

			// Length / Normalization
			float GetLength() const;
			float Normalize();
			Vector4 CreateNormalized() const;

			// Dot Product
			float dot(const Vector4& i_rhs)const;
			

			// Comparison
			bool operator ==(const Vector4& i_rhs) const;
			bool operator !=(const Vector4& i_rhs) const;

			void printVector() const;

			float* toFloatArray() const;

			Vector4(const float i_x = 0.0f, const float i_y = 0.0f, const float i_z = 0.0f, const float i_w = 0.0f);

			std::string toString() const;

			// Data
			//=====

			// A vector class is one of the very few examples where I make data public
		public:

			float x, y, z, w;
		};
	}
}

#endif	// _MATH_CVECTOR_H
