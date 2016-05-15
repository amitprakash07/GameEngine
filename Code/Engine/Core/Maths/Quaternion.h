/*
	This class represents a rotation
*/

#ifndef _MATH_CQUATERNION_H
#define _MATH_CQUATERNION_H

#include "Vector3.h"

namespace Engine
{
	namespace Math
	{
		class Quaternion
		{
		public:
			Quaternion();
			static Quaternion getIdentityQuartenion();	
			static Quaternion slerp(Quaternion fromQuaternion,
				Quaternion toQuartenion, float interpolationFactor);

			float w()const;
			float x()const;
			float y()const;
			float z()const;

			void w(float iW) { mW = iW; }
			void x(float iX) { mX = iX; }
			void y(float iY) { mY = iY; }
			void z(float iZ) { mZ = iZ; }

			//Assignment
			void operator = (const Quaternion i_rhs);

			//Cross Product
			Quaternion operator *( const Quaternion& i_rhs ) const;
			Quaternion cross(const Quaternion& i_rhs) const;

			Vector3 operator*(const Vector3 i_rhs);

			//Inverse
			void inverse();
			Quaternion CreateInverse() const;

			//Equality 
			bool operator ==(Quaternion irhs) const;
			bool operator != (Quaternion i_rhs) const;

			//Negate
			Quaternion operator -()const;
			void conjugate();

			//Magnitude
			float magnitude()const;

			
			//Normalization
			/*
			q = [s,v] = [s,x,y,z]
			magnitude = length = sqrt(s*s + x*x + y*y + z*z)
			normalize = magnitude * q
			*/
			void Normalize();
			Quaternion CreateNormalized() const;

			//Angular Displacement
			/*
			Given orientations a and b, we can compute the angular displacement
			d which rotates from a to b i.e.				
			ad = b => d(difference) = inverse(a)b
			*/
			Quaternion angularDisplacement(Quaternion i_other)const; 
			Quaternion operator -(const Quaternion &iRhs)const;
			Quaternion& operator -=(const Quaternion &iRhs);


			//Dot Product
			/*
			The geometric interpretation of the quaternion dot product is similar to 
			the interpretation of the vector dot product; 
			The larger the absolute value of the quaternion dot product ab, the more
			“similar” the angular displacements represented by a and b.
			*/
			float dot(const Quaternion& i_rhs )const;

			//Exponent
			/*
			Quaternion exponentiation is useful because it allows us to 
			extract a “fraction” of an angular displacement. 
			For example, to compute a quaternion that represents one-third
			of the angular displacement represented by the quaternion q, 
			we would compute q1/3.

			The caveat we here is this: a quaternion represents angular displacements
			using the shortest arc. “Multiple spins” cannot be represented. 
			For our example from above, q4 is not a 240º clockwise rotation about the x-axis as expected; 
			it is an 80º counterclockwise rotation.
			*/
			Quaternion operator^(const float power)const;


			//Rotation Quartenion
			Quaternion( const float i_angleInRadians, const Vector3& i_axisOfRotation );
			static Quaternion getYaw(const float angleInRadians);//About y-axis
			static Quaternion getPitch(const float angleInRadians);//About x-axis
			static Quaternion getRoll(const float angleInRadians);//About z-axis
			static Quaternion getYawPitchRoll(const float angleInRadiansForPitch,
				const float angleInRadiansForYaw,
				const float angleInRadiansForRoll);


			void printQuaternion() const;

			std::string toString() const;


		private:
			float mW, mX, mY, mZ;
			float scalar;
			Vector3 vector;
			Quaternion( const float i_w, 
				const float i_x, 
				const float i_y, 
				const float i_z );
			void splitToScalarVector();
			void splitFromScalarVector();
		};
	}
}

#endif	// _MATH_CQUATERNION_H
