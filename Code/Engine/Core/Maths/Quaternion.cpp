#include "Quaternion.h"
#include <cassert>
#include <cmath>
#include "Vector3.h"
#include <iostream>

namespace
{
	const float s_epsilon = 1.0e-9f;
}

Engine::Math::Quaternion::Quaternion()
	:
	mW(1.0f), mX(0.0f), mY(0.0f), mZ(0.0f)
{
	scalar = 1.0f;
	vector = Vector3(0.0f, 0.0f, 0.0f);
}

Engine::Math::Quaternion Engine::Math::Quaternion::getIdentityQuartenion()
{
	return Quaternion();
}

void Engine::Math::Quaternion::operator=(const Quaternion i_rhs)
{
	mW = i_rhs.mW;
	mX = i_rhs.mX;
	mY = i_rhs.mY;
	mZ = i_rhs.mZ;
	scalar = i_rhs.scalar;
	vector = i_rhs.vector;
}



Engine::Math::Quaternion Engine::Math::Quaternion::slerp(Quaternion fromQuaternion, 
	Quaternion toQuartenion, 
	float interpolationFactor)
{
	/*
	Slerp formulae
	omega  - angular diplacement between two quaternions
	slerp(q1,q2,t) = ((sin(1-t)omega)/sin(omega))* q1 + 
						(sin(t*omega)/sin(omega)) *q2
	*/

	Quaternion slerpedQuaternion;

	//Omega angular diplacement between two quaternions
	float cosOmega = fromQuaternion.dot(toQuartenion);

	// If negative dot, negate one of the input
	// quaternions to take the shorter 4D "arc"
	if(cosOmega < 0.0f)
	{
		fromQuaternion = -fromQuaternion;
		cosOmega = -cosOmega;
	}

	// Checking if they are very close together to protect
	// against divide-by-zero
	float k0, k1;
	if (cosOmega > 0.9999f) 
	{
		// Very close - just use linear interpolation
		k0 = 1.0f - interpolationFactor;
		k1 = interpolationFactor;
	}
	else
	{
		float sinOmega = sqrt(1.0f - cosOmega*cosOmega);

		// Computing the angle from its sin and cosine
		float omega = atan2(sinOmega, cosOmega);

		// Compute inverse of denominator, so we only have
		// to divide once
		float oneOverSinOmega = 1.0f / sinOmega;
		
		// Compute interpolation parameters
		k0 = sin((1.0f - interpolationFactor) * omega) * oneOverSinOmega;
		k1 = sin(interpolationFactor * omega) * oneOverSinOmega;
	}

	// Interpolate
	slerpedQuaternion.mW = fromQuaternion.mW*k0 + toQuartenion.mW*k1;
	slerpedQuaternion.mX = fromQuaternion.mX*k0 + toQuartenion.mX*k1;
	slerpedQuaternion.mY = fromQuaternion.mY*k0 + toQuartenion.mY*k1;
	slerpedQuaternion.mZ = fromQuaternion.mZ*k0 + toQuartenion.mZ*k1;
	slerpedQuaternion.splitToScalarVector();
	return slerpedQuaternion;
}


//Getters
float Engine::Math::Quaternion::w() const
{
	return mW;
}

float Engine::Math::Quaternion::x() const
{
	return mX;
}

float Engine::Math::Quaternion::y() const
{
	return mY;
}

float Engine::Math::Quaternion::z() const
{
	return mZ;
}


//Cross Product
Engine::Math::Quaternion Engine::Math::Quaternion::operator *( const Quaternion& i_rhs ) const
{
	/*
	q1 = [s1, v1]
	q2 = [s2, v2]
	q1*q2 = [s1S2 - v1.v2, s1v2+s2v1+ v1.Cross(v2)]
	*/
	return Quaternion(
		( mW * i_rhs.mW ) - ( ( mX * i_rhs.mX ) + ( mY * i_rhs.mY ) + ( mZ * i_rhs.mZ ) ),
		( mW * i_rhs.mX ) + ( mX * i_rhs.mW ) + ( ( mY * i_rhs.mZ ) - ( mZ * i_rhs.mY ) ),
		( mW * i_rhs.mY ) + ( mY * i_rhs.mW ) + ( ( mZ * i_rhs.mX ) - ( mX * i_rhs.mZ ) ),
		( mW * i_rhs.mZ ) + ( mZ * i_rhs.mW ) + ( ( mX * i_rhs.mY ) - ( mY * i_rhs.mX ) ) );
}

//Cross Product
Engine::Math::Quaternion Engine::Math::Quaternion::cross(const Quaternion& i_rhs) const
{
	/*
	q1 = [s1, v1]
	q2 = [s2, v2]
	q1*q2 = [s1S2 - v1.v2, s1v2+s2v1+ v1.Cross(v2)]
	*/
	Quaternion tempQuaternion;
	tempQuaternion.scalar = scalar*i_rhs.scalar + vector.dot(i_rhs.vector);
	tempQuaternion.vector = vector*i_rhs.scalar + i_rhs.vector*scalar + vector.Cross(i_rhs.vector);
	tempQuaternion.splitFromScalarVector();
	return tempQuaternion;
}


// Inverse
void Engine::Math::Quaternion::inverse()
{
	mX = -mX;
	mY = -mY;
	mZ = -mZ;
}

//Create Inverse
Engine::Math::Quaternion Engine::Math::Quaternion::CreateInverse() const
{
	Quaternion tempQuartenion = Quaternion(mW, -mX, -mY, -mZ);
	tempQuartenion.splitToScalarVector();
	return tempQuartenion;
}


Engine::Math::Quaternion Engine::Math::Quaternion::operator-() const
{
	Quaternion negatedQuartenion;
	negatedQuartenion.mW = -mW;
	negatedQuartenion.mX = -mX;
	negatedQuartenion.mY = -mY;
	negatedQuartenion.mZ = -mZ;
	negatedQuartenion.splitToScalarVector();
	return negatedQuartenion;
}


void Engine::Math::Quaternion::conjugate()
{
	mX = -mX;
	mY = -mY;
	mZ = -mZ;
	splitToScalarVector();
}


float Engine::Math::Quaternion::magnitude() const
{
	return sqrt(mW*mW + mX*mX + mY*mY + mZ*mZ);
}


// NormalimZation
void Engine::Math::Quaternion::Normalize()
{
	const float length = magnitude();
	assert( length > s_epsilon );
	const float length_reciprocal = 1.0f / length;
	mW *= length_reciprocal;
	mX *= length_reciprocal;
	mY *= length_reciprocal;
	mZ *= length_reciprocal;
	splitToScalarVector();
}


Engine::Math::Quaternion Engine::Math::Quaternion::CreateNormalized() const
{
	const float length = magnitude();
	assert( length > s_epsilon );
	const float length_reciprocal = 1.0f / length;
	Quaternion tempQuaternion = Quaternion(mW * length_reciprocal, mX * length_reciprocal, mY * length_reciprocal, mZ * length_reciprocal);
	tempQuaternion.splitToScalarVector();
	return tempQuaternion;
}


//angular Displacement
Engine::Math::Quaternion Engine::Math::Quaternion::angularDisplacement(Quaternion i_other)const
{
	//Angular Displacement
	/*
	Given orientations a and b, we can compute the angular displacement
	d which rotates from a to b i.e.
	ad = b => d - difference = inverse(a)b
	*/
	Quaternion difference;
	difference = this->CreateInverse() * i_other;
	difference.splitToScalarVector(); 
	return difference;
}


Engine::Math::Quaternion Engine::Math::Quaternion::operator-(const Quaternion& iRhs) const
{
	//Angular Displacement
	/*
	Given orientations a and b, we can compute the angular displacement
	d which rotates from a to b i.e.
	ad = b => d - difference = inverse(a)b
	*/
	Quaternion difference;
	difference = this->CreateInverse() * iRhs;
	difference.splitToScalarVector();
	return difference;
}

Engine::Math::Quaternion& Engine::Math::Quaternion::operator-=(const Quaternion& iRhs)
{
	Quaternion difference;
	difference = this->CreateInverse() * iRhs;
	difference.splitToScalarVector();
	mW = difference.mW;
	mX = difference.mX;
	mY = difference.mY;
	mZ = difference.mZ;
	this->splitToScalarVector();
	return *this;
}


// Dot Product
float Engine::Math::Quaternion::dot(const Quaternion& i_rhs) const
{
	return (mW * i_rhs.mW) + (mX * i_rhs.mX) + (mY * i_rhs.mY) + (mZ * i_rhs.mZ);
}

//Exponent
Engine::Math::Quaternion Engine::Math::Quaternion::operator^(const float exponent) const
{	
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

	// Quaternion (input and output)
	Quaternion exponentResult;
	
	// Check for the case of an identity quaternion.
	// This will protect against divide by zero
	if (fabs(mW) < .9999f)
	{
		// Extracting the half angle alpha (alpha = theta/2)
		float alpha = acos(mW);
		// Compute new alpha value
		float newAlpha = alpha * exponent;
		// Compute new w value
		exponentResult.mW = cos(newAlpha);
		// Compute new xyz values
		float mult = sin(newAlpha) / sin(alpha);
		exponentResult.mX = mult;
		exponentResult.mY = mult;
		exponentResult.mZ = mult;
	}
	return exponentResult;
}

Engine::Math::Quaternion::Quaternion( const float i_angleInRadians, const Vector3& i_axisOfRotation )
{
	/*
	q = [cos(θ /2)+sin(θ /2) ˆu].
	mWhere u is the normalimZed arbitrary axis vector
	*/
	if (i_axisOfRotation.GetLength() > 0)
	{
		Vector3 axisOfRotation_normalized = i_axisOfRotation.CreateNormalized();

		const float theta_half = i_angleInRadians * 0.5f;
		mW = std::cos(theta_half);
		const float sin_theta_half = std::sin(theta_half);
		mX = axisOfRotation_normalized.x * sin_theta_half;
		mY = axisOfRotation_normalized.y * sin_theta_half;
		mZ = axisOfRotation_normalized.z * sin_theta_half;
		splitToScalarVector();
	}
	else
	{
		mW = 1.0f;
		mX = mY = mZ = 0.0f;
		scalar = 1.0f;
		vector = Vector3(0.0f, 0.0f, 0.0f);
	}

}


//About rightVector(x-axis)
Engine::Math::Quaternion Engine::Math::Quaternion::getPitch(const float angleInRadians)
{
	return Quaternion(angleInRadians, Vector3(1.0f, 0.0f, 0.0f));
}


//About forwardAxis (z-axis)
Engine::Math::Quaternion Engine::Math::Quaternion::getRoll(const float angleInRadians)
{
	return Quaternion(angleInRadians, Vector3(0.0f, 0.0f, 1.0f));
}

//About upVector (y-axis)
Engine::Math::Quaternion Engine::Math::Quaternion::getYaw(const float angleInRadians)
{
	return Quaternion(angleInRadians, Vector3(0.0f, 1.0f, 0.0f));
}


Engine::Math::Quaternion Engine::Math::Quaternion::getYawPitchRoll(
	float yaw, 
	float pitch, 
	float roll)
{
	/*
	q = q(yaw)q(pitch)q(roll) = [s+xi+yj+zk]
	s = cos(yaw/2)cos(pitch/2)cos(roll/2) + sin(yaw/2) sin(pitch/2) sin(roll/2)
	x = cos(yaw/2) sin(pitch/2)cos(roll/2) + sin(yaw/2)cos(pitch/2) sin(roll/2)
	y = sin(yaw/2)cos(pitch/2)cos(roll/2) − cos(yaw/2) sin(pitch/2) sin(roll/2)
	z = cos(yaw/2)cos(pitch/2) sin(roll/2) − sin(yaw/2) sin(pitch/2)cos(roll/2)
	*/
	Quaternion yawPitchRoll;
	yawPitchRoll.mW = cos(yaw / 2)*cos(pitch / 2)*cos(roll / 2) + sin(yaw / 2) * sin(pitch / 2)* sin(roll / 2);
	yawPitchRoll.mX = cos(yaw / 2)*sin(pitch / 2)*cos(roll / 2) + sin(yaw / 2) * cos(pitch / 2) *sin(roll / 2);
	yawPitchRoll.mY = sin(yaw / 2)*cos(pitch / 2)*cos(roll / 2) - cos(yaw / 2) * sin(pitch / 2) *sin(roll / 2);
	yawPitchRoll.mZ = cos(yaw / 2)*cos(pitch / 2)* sin(roll / 2) - sin(yaw / 2)* sin(pitch / 2)*cos(roll / 2);
	yawPitchRoll.splitToScalarVector();
	return yawPitchRoll;
}


Engine::Math::Quaternion::Quaternion( const float i_mW, const float i_mX, const float i_mY, const float i_mZ )
	:
	mW( i_mW ), mX( i_mX ), mY( i_mY ), mZ( i_mZ )
{
	splitToScalarVector();
}


void Engine::Math::Quaternion::splitToScalarVector()
{
	scalar = mW;
	vector.x = mX;
	vector.y = mY;
	vector.z = mZ;
}


void Engine::Math::Quaternion::splitFromScalarVector()
{
	mW = scalar;
	mX = vector.x;
	mY = vector.y;
	mZ = vector.z;
}


void Engine::Math::Quaternion::printQuaternion() const
{
	std::cout << "w = " <<scalar<<" " ;	
	vector.printVector();
	std::cout << std::endl;
}


Engine::Math::Vector3 Engine::Math::Quaternion::operator*(const Vector3 i_rhs)
{
	Quaternion tempQuaternion = Quaternion(0.0f, i_rhs.x, i_rhs.y, i_rhs.z);
	Quaternion crossQuaternion = (*(this))*tempQuaternion;
	Quaternion final_quaternion = crossQuaternion * this->CreateInverse();
	return (Vector3(final_quaternion.x(),final_quaternion.y(),final_quaternion.z()));
}



