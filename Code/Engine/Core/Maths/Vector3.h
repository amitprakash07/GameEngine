/*
	This class represents a position or direction
*/

#ifndef _MATH_CVECTOR_H
#define _MATH_CVECTOR_H
#include <string>

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

			// Scalar Multiplication
			Vector3 operator *( const float i_rhs ) const;
			Vector3& operator *=( const float i_rhs );			

			// Division
			Vector3 operator /( const float i_rhs ) const;
			Vector3& operator /=( const float i_rhs );

			// Length / Normalization
			float GetLength() const;
			float Normalize();
			Vector3 CreateNormalized() const;

			// Dot Product
			float dot( const Vector3& i_rhs )const;
			//Cross Product
			Vector3 Cross(const Vector3& i_rhs )const;

			// Comparison
			bool operator ==( const Vector3& i_rhs ) const;
			bool operator !=( const Vector3& i_rhs ) const;

			void printVector() const;

			float* toFloatArray() const;

			Vector3( const float i_x = 0.0f, const float i_y = 0.0f, const float i_z = 0.0f );			

			std::string toString() const;

			// Data
			//=====

		// A vector class is one of the very few examples where I make data public
		public:

			float x, y, z;			
		};		
	}
}

#endif	// _MATH_CVECTOR_H
