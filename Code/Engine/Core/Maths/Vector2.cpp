// Header Files
//=============

#include "Vector2.h"

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
Engine::Math::Vector2 Engine::Math::Vector2::operator +(const Vector2& i_rhs) const
{
	return Vector2(x + i_rhs.x, y + i_rhs.y);
}
Engine::Math::Vector2& Engine::Math::Vector2::operator +=(const Vector2& i_rhs)
{
	x += i_rhs.x;
	y += i_rhs.y;	
	return *this;
}

// Subtraction / Negation
Engine::Math::Vector2 Engine::Math::Vector2::operator -(const Vector2& i_rhs) const
{
	return Vector2(x - i_rhs.x, y - i_rhs.y);
}
Engine::Math::Vector2& Engine::Math::Vector2::operator -=(const Vector2& i_rhs)
{
	x -= i_rhs.x;
	y -= i_rhs.y;	
	return *this;
}
Engine::Math::Vector2 Engine::Math::Vector2::operator -() const
{
	return Vector2(-x, -y);
}

// Multiplication
Engine::Math::Vector2 Engine::Math::Vector2::operator *(const float i_rhs) const
{
	return Vector2(x * i_rhs, y * i_rhs);
}
Engine::Math::Vector2& Engine::Math::Vector2::operator *=(const float i_rhs)
{
	x *= i_rhs;
	y *= i_rhs;	
	return *this;
}
Engine::Math::Vector2 operator *(const float i_lhs, const Engine::Math::Vector2& i_rhs)
{
	return i_rhs * i_lhs;
}

// Division
Engine::Math::Vector2 Engine::Math::Vector2::operator /(const float i_rhs) const
{
	assert(std::abs(i_rhs) > s_epsilon);
	const float rhs_reciprocal = 1.0f / i_rhs;
	return Vector2(x * rhs_reciprocal, y * rhs_reciprocal);
}

Engine::Math::Vector2& Engine::Math::Vector2::operator /=(const float i_rhs)
{
	assert(std::abs(i_rhs) > s_epsilon);
	const float rhs_reciprocal = 1.0f / i_rhs;
	x *= rhs_reciprocal;
	y *= rhs_reciprocal;	
	return *this;
}

// Length / Normalization
float Engine::Math::Vector2::GetLength() const
{
	return std::sqrt((x * x) + (y * y));
}

float Engine::Math::Vector2::Normalize()
{
	const float length = GetLength();
	assert(length > s_epsilon);
	operator /=(length);
	return length;
}
Engine::Math::Vector2 Engine::Math::Vector2::CreateNormalized() const
{
	const float length = GetLength();
	assert(length > s_epsilon);
	const float length_reciprocal = 1.0f / length;
	return Vector2(x * length_reciprocal, y * length_reciprocal);
}

// Products
float Engine::Math::Dot(const Vector2& i_lhs, const Vector2& i_rhs)
{
	return (i_lhs.x * i_rhs.x) + (i_lhs.y * i_rhs.y);
}

/*

r = ai + bj + ck
s = di + ej + fk
r cross(s) = (bf-ce)i + (cd-af)j + (ae-bd)k
or in determinant form
r cross(s) = b	c  i   + a	c  j  + a	b k
			 e	f		 d	f       d	e

*/

Engine::Math::Vector2 Engine::Math::Cross(const Vector2& i_lhs, const Vector2& i_rhs)
{
	return Vector2(
		(i_lhs.y * 0.0f) - (0.0f * i_rhs.y), //as k would be zero
		(0.0f * i_rhs.x) - (i_lhs.x * 0.0f),
		(i_lhs.x * i_rhs.y) - (i_lhs.y * i_rhs.x));
}

// Comparison
bool Engine::Math::Vector2::operator ==(const Vector2& i_rhs) const
{
	// Use & rather than && to prevent branches (all three comparisons will be evaluated)
	return (x == i_rhs.x) & (y == i_rhs.y);
}
bool Engine::Math::Vector2::operator !=(const Vector2& i_rhs) const
{
	// Use | rather than || to prevent branches (all three comparisons will be evaluated)
	return (x != i_rhs.x) | (y != i_rhs.y);
}

// Initialization / Shut Down
//---------------------------

Engine::Math::Vector2::Vector2(const float i_x, const float i_y, const float i_z)
	:
	x(i_x), y(i_y)
{

}
