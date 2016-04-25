// Header Files
//=============

#include "Vector3.h"

#include <cassert>
#include <cmath>
#include <iostream>

// Static Data Initialization
//===========================

namespace
{
	const float s_epsilon = 1.0e-9f;
}

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


Engine::Math::Vector3 operator *( const float i_lhs, const Engine::Math::Vector3& i_rhs )
{
	return i_rhs * i_lhs;
}

// Division
Engine::Math::Vector3 Engine::Math::Vector3::operator /( const float i_rhs ) const
{
	assert( std::abs( i_rhs ) > s_epsilon );
	const float rhs_reciprocal = 1.0f / i_rhs;
	return Vector3( x * rhs_reciprocal, y * rhs_reciprocal, z * rhs_reciprocal );
}

Engine::Math::Vector3& Engine::Math::Vector3::operator /=( const float i_rhs )
{
	assert( std::abs( i_rhs ) > s_epsilon );
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
	assert( length > s_epsilon );
	operator /=( length );
	return length;
}

Engine::Math::Vector3 Engine::Math::Vector3::CreateNormalized() const
{
	const float length = GetLength();
	assert( length > s_epsilon );
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

