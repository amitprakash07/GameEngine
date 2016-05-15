// Header Files
//=============

#include "Vector3.h"

#include <cassert>
#include <cmath>
#include <iostream>

// Static Data Initialization
//===========================


// Interface
//==========

// Addition
Engine::Math::Vector3 Engine::Math::Vector3::operator +( const Vector3& i_rhs ) const
{
	return Vector3( x + i_rhs.x, y + i_rhs.y, z + i_rhs.z );
}


Engine::Math::Vector3& Engine::Math::Vector3::operator +=( const Vector3& i_rhs )
{
	x += i_rhs.x;
	y += i_rhs.y;
	z += i_rhs.z;
	return *this;
}

// Subtraction / Negation
Engine::Math::Vector3 Engine::Math::Vector3::operator -( const Vector3& i_rhs ) const
{
	return Vector3( x - i_rhs.x, y - i_rhs.y, z - i_rhs.z );
}


Engine::Math::Vector3& Engine::Math::Vector3::operator -=( const Vector3& i_rhs )
{
	x -= i_rhs.x;
	y -= i_rhs.y;
	z -= i_rhs.z;
	return *this;
}


Engine::Math::Vector3 Engine::Math::Vector3::operator -() const
{
	return Vector3( -x, -y, -z );
}

// Multiplication
Engine::Math::Vector3 Engine::Math::Vector3::operator *( const float i_rhs ) const
{
	return Vector3( x * i_rhs, y * i_rhs, z * i_rhs );
}


Engine::Math::Vector3& Engine::Math::Vector3::operator *=( const float i_rhs )
{
	x *= i_rhs;
	y *= i_rhs;
	z *= i_rhs;
	return *this;
}

Engine::Math::Vector3 Engine::Math::Vector3::operator*(const Vector3 i_rhs) const
{
	Vector3 tempVector;
	tempVector.x = x * i_rhs.x;
	tempVector.y = y * i_rhs.y;
	tempVector.z = z * i_rhs.z;
	return tempVector;
}



Engine::Math::Vector3 operator *( const float i_lhs, const Engine::Math::Vector3& i_rhs )
{
	return i_rhs * i_lhs;
}

// Division
Engine::Math::Vector3 Engine::Math::Vector3::operator /( const float i_rhs ) const
{
	assert( std::abs( i_rhs ) > Epsilon);
	const float rhs_reciprocal = 1.0f / i_rhs;
	return Vector3( x * rhs_reciprocal, y * rhs_reciprocal, z * rhs_reciprocal );
}

Engine::Math::Vector3& Engine::Math::Vector3::operator /=( const float i_rhs )
{
	assert( std::abs( i_rhs ) > Epsilon);
	const float rhs_reciprocal = 1.0f / i_rhs;
	x *= rhs_reciprocal;
	y *= rhs_reciprocal;
	z *= rhs_reciprocal;
	return *this;
}

// Length / Normalization
float Engine::Math::Vector3::GetLength() const
{
	return std::sqrt( ( x * x ) + ( y * y ) + ( z * z ) );
}

float Engine::Math::Vector3::Normalize()
{
	const float length = GetLength();
	assert( length > Epsilon);
	operator /=( length );
	return length;
}

Engine::Math::Vector3 Engine::Math::Vector3::CreateNormalized() const
{
	const float length = GetLength();
	assert( length > Epsilon );
	const float length_reciprocal = 1.0f / length;
	return Vector3( x * length_reciprocal, y * length_reciprocal, z * length_reciprocal );
}

// Products
float Engine::Math::Vector3::dot(const Vector3& i_rhs) const
{
	return (x*i_rhs.x + y* i_rhs.y + z* i_rhs.z);
}


Engine::Math::Vector3 Engine::Math::Vector3::Cross(const Vector3& i_rhs) const
{
	/*

	r = ai + bj + ck
	s = di + ej + fk
	r cross(s) = (bf-ce)i + (cd-af)j + (ae-bd)k
	or in determinant form
	r cross(s) = b	c  i   + a	c  j  + a	b k
	e	f		 d	f       d	e

	*/
	return Vector3(
		(y * i_rhs.z) - (z * i_rhs.y),
		(z * i_rhs.x) - (x * i_rhs.z),
		(x * i_rhs.y) - (y * i_rhs.x));
}


// Comparison
bool Engine::Math::Vector3::operator ==( const Vector3& i_rhs ) const
{
	// Use & rather than && to prevent branches (all three comparisons will be evaluated)
	return ( x == i_rhs.x ) & ( y == i_rhs.y ) & ( z == i_rhs.z );
}

bool Engine::Math::Vector3::operator !=( const Vector3& i_rhs ) const
{
	// Use | rather than || to prevent branches (all three comparisons will be evaluated)
	return ( x != i_rhs.x ) | ( y != i_rhs.y ) | ( z != i_rhs.z );
}

// Initialization / Shut Down
//---------------------------

Engine::Math::Vector3::Vector3( const float i_x, const float i_y, const float i_z )
	:
	x( i_x ), y( i_y ), z( i_z )
{

}


std::string Engine::Math::Vector3::toString() const
{
	std::string returnString;
	returnString = std::to_string(x) + std::to_string(y) + std::to_string(z);
	return returnString;
}



float* Engine::Math::Vector3::toFloatArray() const
{
	float floatArray[3];
	floatArray[0] = x;
	floatArray[1] = y;
	floatArray[2] = z;
	return floatArray;
}



void Engine::Math::Vector3::printVector() const
{
	std::cout << "x = " << x << ", y = " << y << ", z= " << z;
	std::cout << std::endl;
}

float& Engine::Math::Vector3::operator[](int iIndex)
{
	if(iIndex < 3 && iIndex >=0)
	{
		switch(iIndex)
		{
		case 0:
			return x;			
		case 1:
			return y;			
		case 2:
			return z;			
		}
	}
	float * garbage = new float;
	*garbage = -1.0f;
	return *garbage;
}


float Engine::Math::Vector3::ScalarTripleProduct(Vector3 iA, Vector3 iB) const
{
	Vector3 temp = Vector3(x, y, z);
	Vector3 m = temp.Cross(iA);
	return iB.dot(m);
}



/*
int TestTriangleAABB(Point v0, Point v1, Point v2, AABB b)
{
float p0, p1, p2, r;
// Compute box center and extents (if not already given in that format)
Vector c = (b.min + b.max) * 0.5f;
float e0 = (b.max.x - b.min.x) * 0.5f;
float e1 = (b.max.y - b.min.y) * 0.5f;
float e2 = (b.max.z - b.min.z) * 0.5f;
// Translate triangle as conceptually moving AABB to origin
v0 = v0 - c;
v1 = v1 - c;
v2 = v2 - c;
// Compute edge vectors for triangle
Vector f0 = v1 - v0, f1 = v2 - v1, f2 = v0 - v2;
// Test axes a00..a22 (category 3)
// Test axis a00
p0 = v0.z*v1.y - v0.y*v1.z;
p2 = v2.z*(v1.y - v0.y) - v2.z*(v1.z - v0.z);
r = e1 * Abs(f0.z) + e2 * Abs(f0.y);
if (Max(-Max(p0, p2), Min(p0, p2)) > r) return 0; // Axis is a separating axis
// Repeat similar tests for remaining axes a01..a22
...
// Test the three axes corresponding to the face normals of AABB b (category 1).
// Exit if...
// ... [-e0, e0] and [min(v0.x,v1.x,v2.x), max(v0.x,v1.x,v2.x)] do not overlap
if (Max(v0.x, v1.x, v2.x) < -e0 || Min(v0.x, v1.x, v2.x) > e0) return 0;
// ... [-e1, e1] and [min(v0.y,v1.y,v2.y), max(v0.y,v1.y,v2.y)] do not overlap
if (Max(v0.y, v1.y, v2.y) < -e1 || Min(v0.y, v1.y, v2.y) > e1) return 0;
// ... [-e2, e2] and [min(v0.z,v1.z,v2.z), max(v0.z,v1.z,v2.z)] do not overlap
if (Max(v0.z, v1.z, v2.z) < -e2 || Min(v0.z, v1.z, v2.z) > e2) return 0;
// Test separating axis corresponding to triangle face normal (category 2)
Plane p;
p.n = Cross(f0, f1);
p.d = Dot(p.n, v0);
return TestAABBPlane(b, p);
}
*/

