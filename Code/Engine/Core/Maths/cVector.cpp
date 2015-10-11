// Header Files
//=============

#include "cVector.h"

#include <cassert>
#include <cmath>

// Static Data Initialization
//===========================

namespace
{
	const float s_epsilon = 1.0e-9f;
}

// Interface
//==========

// Addition
Engine::Math::cVector Engine::Math::cVector::operator +( const cVector& i_rhs ) const
{
	return cVector( x + i_rhs.x, y + i_rhs.y, z + i_rhs.z );
}
Engine::Math::cVector& Engine::Math::cVector::operator +=( const cVector& i_rhs )
{
	x += i_rhs.x;
	y += i_rhs.y;
	z += i_rhs.z;
	return *this;
}

// Subtraction / Negation
Engine::Math::cVector Engine::Math::cVector::operator -( const cVector& i_rhs ) const
{
	return cVector( x - i_rhs.x, y - i_rhs.y, z - i_rhs.z );
}
Engine::Math::cVector& Engine::Math::cVector::operator -=( const cVector& i_rhs )
{
	x -= i_rhs.x;
	y -= i_rhs.y;
	z -= i_rhs.z;
	return *this;
}
Engine::Math::cVector Engine::Math::cVector::operator -() const
{
	return cVector( -x, -y, -z );
}

// Multiplication
Engine::Math::cVector Engine::Math::cVector::operator *( const float i_rhs ) const
{
	return cVector( x * i_rhs, y * i_rhs, z * i_rhs );
}
Engine::Math::cVector& Engine::Math::cVector::operator *=( const float i_rhs )
{
	x *= i_rhs;
	y *= i_rhs;
	z *= i_rhs;
	return *this;
}
Engine::Math::cVector operator *( const float i_lhs, const Engine::Math::cVector& i_rhs )
{
	return i_rhs * i_lhs;
}

// Division
Engine::Math::cVector Engine::Math::cVector::operator /( const float i_rhs ) const
{
	assert( std::abs( i_rhs ) > s_epsilon );
	const float rhs_reciprocal = 1.0f / i_rhs;
	return cVector( x * rhs_reciprocal, y * rhs_reciprocal, z * rhs_reciprocal );
}
Engine::Math::cVector& Engine::Math::cVector::operator /=( const float i_rhs )
{
	assert( std::abs( i_rhs ) > s_epsilon );
	const float rhs_reciprocal = 1.0f / i_rhs;
	x *= rhs_reciprocal;
	y *= rhs_reciprocal;
	z *= rhs_reciprocal;
	return *this;
}

// Length / Normalization
float Engine::Math::cVector::GetLength() const
{
	return std::sqrt( ( x * x ) + ( y * y ) + ( z * z ) );
}
float Engine::Math::cVector::Normalize()
{
	const float length = GetLength();
	assert( length > s_epsilon );
	operator /=( length );
	return length;
}
Engine::Math::cVector Engine::Math::cVector::CreateNormalized() const
{
	const float length = GetLength();
	assert( length > s_epsilon );
	const float length_reciprocal = 1.0f / length;
	return cVector( x * length_reciprocal, y * length_reciprocal, z * length_reciprocal );
}

// Products
float Engine::Math::Dot( const cVector& i_lhs, const cVector& i_rhs )
{
	return ( i_lhs.x * i_rhs.x ) + ( i_lhs.y * i_rhs.y ) + ( i_lhs.z * i_rhs.z );
}
Engine::Math::cVector Engine::Math::Cross( const cVector& i_lhs, const cVector& i_rhs )
{
	return cVector(
		( i_lhs.y * i_rhs.z ) - ( i_lhs.z * i_rhs.y ),
		( i_lhs.z * i_rhs.x ) - ( i_lhs.x * i_rhs.z ),
		( i_lhs.x * i_rhs.y ) - ( i_lhs.y * i_rhs.x ) );
}

// Comparison
bool Engine::Math::cVector::operator ==( const cVector& i_rhs ) const
{
	// Use & rather than && to prevent branches (all three comparisons will be evaluated)
	return ( x == i_rhs.x ) & ( y == i_rhs.y ) & ( z == i_rhs.z );
}
bool Engine::Math::cVector::operator !=( const cVector& i_rhs ) const
{
	// Use | rather than || to prevent branches (all three comparisons will be evaluated)
	return ( x != i_rhs.x ) | ( y != i_rhs.y ) | ( z != i_rhs.z );
}

// Initialization / Shut Down
//---------------------------

Engine::Math::cVector::cVector( const float i_x, const float i_y, const float i_z )
	:
	x( i_x ), y( i_y ), z( i_z )
{

}
