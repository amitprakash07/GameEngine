

/*
Link http://www.euclideanspace.com/
*/

#include "Matrix4x4.h"

#include <cmath>
#include "Quaternion.h"
#include "Vector3.h"
#include <iostream>

// Interface
//==========

Engine::Math::Matrix4x4 Engine::Math::Matrix4x4::CreateWorldToViewTransform(
	const Quaternion& i_cameraOrientation, const Vector3& i_cameraPosition )
{
	Matrix4x4 transform_viewToWorld( i_cameraOrientation, i_cameraPosition );
	// A camera can only ever have rotation and translation
	// and so a lot of simplifying assumptions can be made in order to create the inverse
	return Matrix4x4(
		transform_viewToWorld.m_00, transform_viewToWorld.m_01, transform_viewToWorld.m_02,
			-( transform_viewToWorld.m_30 * transform_viewToWorld.m_00 ) - ( transform_viewToWorld.m_31 * transform_viewToWorld.m_01 ) - ( transform_viewToWorld.m_32 * transform_viewToWorld.m_02 ),
		transform_viewToWorld.m_10, transform_viewToWorld.m_11, transform_viewToWorld.m_12,
			-( transform_viewToWorld.m_30 * transform_viewToWorld.m_10 ) - ( transform_viewToWorld.m_31 * transform_viewToWorld.m_11 ) - ( transform_viewToWorld.m_32 * transform_viewToWorld.m_12 ),
		transform_viewToWorld.m_20, transform_viewToWorld.m_21, transform_viewToWorld.m_22,
			-( transform_viewToWorld.m_30 * transform_viewToWorld.m_20 ) - ( transform_viewToWorld.m_31 * transform_viewToWorld.m_21 ) - ( transform_viewToWorld.m_32 * transform_viewToWorld.m_22 ),
		0.0f, 0.0f, 0.0f, 1.0f );
}

Engine::Math::Matrix4x4 Engine::Math::Matrix4x4::getIdentityMatrix()
{
	return Matrix4x4();
}


Engine::Math::Matrix4x4 Engine::Math::Matrix4x4::CreateViewToScreenTransform(
	const float i_fieldOfView_y, const float i_aspectRatio,
	const float i_z_nearPlane, const float i_z_farPlane )
{
	const float yScale = 1.0f / std::tan( i_fieldOfView_y * 0.5f );
	const float xScale = yScale / i_aspectRatio;
#if defined(PLATFORM_D3D )
	const float zDistanceScale = i_z_farPlane / ( i_z_nearPlane - i_z_farPlane );
	return Matrix4x4(
		xScale, 0.0f, 0.0f, 0.0f,
		0.0f, yScale, 0.0f, 0.0f,
		0.0f, 0.0f, zDistanceScale, i_z_nearPlane * zDistanceScale,
		0.0f, 0.0f, -1.0f, 0.0f );
#elif defined(PLATFORM_OPEN_GL)
	const float zDistanceScale = 1.0f / ( i_z_nearPlane - i_z_farPlane );
	return Matrix4x4(
		xScale, 0.0f, 0.0f, 0.0f,
		0.0f, yScale, 0.0f, 0.0f,
		0.0f, 0.0f, ( i_z_nearPlane + i_z_farPlane ) * zDistanceScale, ( 2.0f * i_z_nearPlane * i_z_farPlane ) * zDistanceScale,
		0.0f, 0.0f, -1.0f, 0.0f );
#endif
}


Engine::Math::Matrix4x4::Matrix4x4()
	:
	m_00( 1.0f ), m_10( 0.0f ), m_20( 0.0f ), m_30( 0.0f ),
	m_01( 0.0f ), m_11( 1.0f ), m_21( 0.0f ), m_31( 0.0f ),
	m_02( 0.0f ), m_12( 0.0f ), m_22( 1.0f ), m_32( 0.0f ),
	m_03( 0.0f ), m_13( 0.0f ), m_23( 0.0f ), m_33( 1.0f )
{

}


/*
float  - storage column major
m_00, m_10, m_20, m_30,
m_01, m_11, m_21, m_31,
m_02, m_12, m_22, m_32,
m_03, m_13, m_23, m_33


matrix
m00 m01 m02 m03
m10 m11 m12 m13
m20 m21 m22 m23
m30 m31 m32 m33
*/


Engine::Math::Matrix4x4 Engine::Math::Matrix4x4::getInverse()const
{
	// http://www.euclideanspace.com/maths/algebra/matrix/resources/code/index.htm

	Matrix4x4 inverseMatrix;
	inverseMatrix.m_00 = m_12*m_23*m_31 - m_13*m_22*m_31 + m_13*m_21*m_32 - m_11*m_23*m_32 - m_12*m_21*m_33 + m_11*m_22*m_33;
	inverseMatrix.m_01 = m_03*m_22*m_31 - m_02*m_23*m_31 - m_03*m_21*m_32 + m_01*m_23*m_32 + m_02*m_21*m_33 - m_01*m_22*m_33;
	inverseMatrix.m_02 = m_02*m_13*m_31 - m_03*m_12*m_31 + m_03*m_11*m_32 - m_01*m_13*m_32 - m_02*m_11*m_33 + m_01*m_12*m_33;
	inverseMatrix.m_03 = m_03*m_12*m_21 - m_02*m_13*m_21 - m_03*m_11*m_22 + m_01*m_13*m_22 + m_02*m_11*m_23 - m_01*m_12*m_23;
	inverseMatrix.m_10 = m_13*m_22*m_30 - m_12*m_23*m_30 - m_13*m_20*m_32 + m_10*m_23*m_32 + m_12*m_20*m_33 - m_10*m_22*m_33;
	inverseMatrix.m_11 = m_02*m_23*m_30 - m_03*m_22*m_30 + m_03*m_20*m_32 - m_00*m_23*m_32 - m_02*m_20*m_33 + m_00*m_22*m_33;
	inverseMatrix.m_12 = m_03*m_12*m_30 - m_02*m_13*m_30 - m_03*m_10*m_32 + m_00*m_13*m_32 + m_02*m_10*m_33 - m_00*m_12*m_33;
	inverseMatrix.m_13 = m_02*m_13*m_20 - m_03*m_12*m_20 + m_03*m_10*m_22 - m_00*m_13*m_22 - m_02*m_10*m_23 + m_00*m_12*m_23;
	inverseMatrix.m_20 = m_11*m_23*m_30 - m_13*m_21*m_30 + m_13*m_20*m_31 - m_10*m_23*m_31 - m_11*m_20*m_33 + m_10*m_21*m_33;
	inverseMatrix.m_21 = m_03*m_21*m_30 - m_01*m_23*m_30 - m_03*m_20*m_31 + m_00*m_23*m_31 + m_01*m_20*m_33 - m_00*m_21*m_33;
	inverseMatrix.m_22 = m_01*m_13*m_30 - m_03*m_11*m_30 + m_03*m_10*m_31 - m_00*m_13*m_31 - m_01*m_10*m_33 + m_00*m_11*m_33;
	inverseMatrix.m_23 = m_03*m_11*m_20 - m_01*m_13*m_20 - m_03*m_10*m_21 + m_00*m_13*m_21 + m_01*m_10*m_23 - m_00*m_11*m_23;
	inverseMatrix.m_30 = m_12*m_21*m_30 - m_11*m_22*m_30 - m_12*m_20*m_31 + m_10*m_22*m_31 + m_11*m_20*m_32 - m_10*m_21*m_32;
	inverseMatrix.m_31 = m_01*m_22*m_30 - m_02*m_21*m_30 + m_02*m_20*m_31 - m_00*m_22*m_31 - m_01*m_20*m_32 + m_00*m_21*m_32;
	inverseMatrix.m_32 = m_02*m_11*m_30 - m_01*m_12*m_30 - m_02*m_10*m_31 + m_00*m_12*m_31 + m_01*m_10*m_32 - m_00*m_11*m_32;
	inverseMatrix.m_33 = m_01*m_12*m_20 - m_02*m_11*m_20 + m_02*m_10*m_21 - m_00*m_12*m_21 - m_01*m_10*m_22 + m_00*m_11*m_22;
	inverseMatrix = inverseMatrix * this->determinant();
	//scale(1 / m_1.determinant());
	return inverseMatrix;
}

Engine::Math::Matrix4x4 Engine::Math::Matrix4x4::operator*(double scalar)const
{
	/*
	http://www.euclideanspace.com/maths/algebra/matrix/resources/code/sftranslation_cpp.htm
	*/

	Matrix4x4 tempMatrix = Matrix4x4();
	tempMatrix.m_00 = m_00* scalar;
	tempMatrix.m_01 = m_01* scalar;
	tempMatrix.m_02 = m_02* scalar;
	tempMatrix.m_03 = m_03* scalar;
	tempMatrix.m_10 = m_10* scalar;
	tempMatrix.m_11 = m_11* scalar;
	tempMatrix.m_12 = m_12* scalar;
	tempMatrix.m_13 = m_13* scalar;
	tempMatrix.m_20 = m_20* scalar;
	tempMatrix.m_21 = m_21* scalar;
	tempMatrix.m_22 = m_22* scalar;
	tempMatrix.m_23 = m_23* scalar;
	tempMatrix.m_30 = m_30* scalar;
	tempMatrix.m_31 = m_31* scalar;
	tempMatrix.m_32 = m_32* scalar;
	tempMatrix.m_33 = m_33* scalar;
	return tempMatrix;
}


Engine::Math::Matrix4x4 Engine::Math::Matrix4x4::operator*(Matrix4x4 m_2)const
{
	/*
	http://www.euclideanspace.com/maths/algebra/matrix/resources/code/index.htm#cpp
	*/
	Matrix4x4 produxtMatrix;
	produxtMatrix.m_00 = m_00*m_2.m_00 + m_01*m_2.m_10 + m_02*m_2.m_20 + m_03*m_2.m_30;
	produxtMatrix.m_01 = m_00*m_2.m_01 + m_01*m_2.m_11 + m_02*m_2.m_21 + m_03*m_2.m_31;
	produxtMatrix.m_02 = m_00*m_2.m_02 + m_01*m_2.m_12 + m_02*m_2.m_22 + m_03*m_2.m_32;
	produxtMatrix.m_03 = m_00*m_2.m_03 + m_01*m_2.m_13 + m_02*m_2.m_23 + m_03*m_2.m_33;

	produxtMatrix.m_10 = m_10*m_2.m_00 + m_11*m_2.m_10 + m_12*m_2.m_20 + m_13*m_2.m_30;
	produxtMatrix.m_11 = m_10*m_2.m_01 + m_11*m_2.m_11 + m_12*m_2.m_21 + m_13*m_2.m_31;
	produxtMatrix.m_12 = m_10*m_2.m_02 + m_11*m_2.m_12 + m_12*m_2.m_22 + m_13*m_2.m_32;
	produxtMatrix.m_13 = m_10*m_2.m_03 + m_11*m_2.m_13 + m_12*m_2.m_23 + m_13*m_2.m_33;

	produxtMatrix.m_20 = m_20*m_2.m_00 + m_21*m_2.m_10 + m_22*m_2.m_20 + m_23*m_2.m_30;
	produxtMatrix.m_21 = m_20*m_2.m_01 + m_21*m_2.m_11 + m_22*m_2.m_21 + m_23*m_2.m_31;
	produxtMatrix.m_22 = m_20*m_2.m_02 + m_21*m_2.m_12 + m_22*m_2.m_22 + m_23*m_2.m_32;
	produxtMatrix.m_23 = m_20*m_2.m_03 + m_21*m_2.m_13 + m_22*m_2.m_23 + m_23*m_2.m_33;

	produxtMatrix.m_30 = m_30*m_2.m_00 + m_31*m_2.m_10 + m_32*m_2.m_20 + m_33*m_2.m_30;
	produxtMatrix.m_31 = m_30*m_2.m_01 + m_31*m_2.m_11 + m_32*m_2.m_21 + m_33*m_2.m_31;
	produxtMatrix.m_32 = m_30*m_2.m_02 + m_31*m_2.m_12 + m_32*m_2.m_22 + m_33*m_2.m_32;
	produxtMatrix.m_33 = m_30*m_2.m_03 + m_31*m_2.m_13 + m_32*m_2.m_23 + m_33*m_2.m_33;
	return produxtMatrix;
}


Engine::Math::Vector3 Engine::Math::Matrix4x4::mul(Vector3 vector, bool isVector)const
{
	Vector3 translateVector;
	switch(isVector)
	{
	case false:
		translateVector.x = vector.x*m_00 + vector.y*m_10 + vector.z*m_20 + m_30;
		translateVector.y = vector.x*m_01 + vector.y*m_11 + vector.z*m_21 + m_31;
		translateVector.z = vector.x*m_02 + vector.y*m_12 + vector.z*m_22 + m_32;
		break;
	case true:
		translateVector.x = vector.x*m_00 + vector.y*m_10 + vector.z*m_20;
		translateVector.y = vector.x*m_01 + vector.y*m_11 + vector.z*m_21;
		translateVector.z = vector.x*m_02 + vector.y*m_12 + vector.z*m_22;
		break;
	}
	return translateVector;
}


void Engine::Math::Matrix4x4::operator*=(Matrix4x4 m_2)
{
	*this = (*(this))*m_2;
}


void Engine::Math::Matrix4x4::inverse()
{
	*this = this->getInverse();
}

double Engine::Math::Matrix4x4::determinant()const
{
	double value;
	value =
		m_03*m_12*m_21*m_30 - m_02*m_13*m_21*m_30 - m_03*m_11*m_22*m_30 + m_01*m_13*m_22*m_30 +
		m_02*m_11*m_23*m_30 - m_01*m_12*m_23*m_30 - m_03*m_12*m_20*m_31 + m_02*m_13*m_20*m_31 +
		m_03*m_10*m_22*m_31 - m_00*m_13*m_22*m_31 - m_02*m_10*m_23*m_31 + m_00*m_12*m_23*m_31 +
		m_03*m_11*m_20*m_32 - m_01*m_13*m_20*m_32 - m_03*m_10*m_21*m_32 + m_00*m_13*m_21*m_32 +
		m_01*m_10*m_23*m_32 - m_00*m_11*m_23*m_32 - m_02*m_11*m_20*m_33 + m_01*m_12*m_20*m_33 +
		m_02*m_10*m_21*m_33 - m_00*m_12*m_21*m_33 - m_01*m_10*m_22*m_33 + m_00*m_11*m_22*m_33;
	return value;
}


Engine::Math::Matrix4x4 Engine::Math::Matrix4x4::getTranspose()const
{
	Matrix4x4 transposeMatrix = Matrix4x4(
		m_00,m_01,m_02,m_03,
		m_10,m_11,m_12,m_13,
		m_20,m_21,m_22,m_23,
		m_30,m_31,m_32,m_33);
	return transposeMatrix;
}


void Engine::Math::Matrix4x4::transpose()
{
	*this = this->getTranspose();
}


Engine::Math::Matrix4x4::Matrix4x4( const Quaternion& i_rotation, const Vector3& i_translation )
	:
	m_30( i_translation.x ), m_31( i_translation.y ), m_32( i_translation.z ),
	m_03( 0.0f ), m_13( 0.0f ), m_23( 0.0f ), m_33( 1.0f )
{

	/*
	http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/index.htm
	*/
	/*
	1−2(y^2+ z^2)	 2(xy−wz)		 2(xz+wy)
	2(xy+wz)		 1−2(x^2+z^2)	 2(yz−wx)	
	2(xz−wy)		 2(yz+wx)		 1−2(x^2+y^2)	
	*/
	
	//Only rotation part Assignment below
	const float _2x = i_rotation.x() + i_rotation.x();
	const float _2y = i_rotation.y() + i_rotation.y();
	const float _2z = i_rotation.z() + i_rotation.z();
	const float _2xx = i_rotation.x() * _2x;
	const float _2xy = _2x * i_rotation.y();
	const float _2xz = _2x * i_rotation.z();
	const float _2xw = _2x * i_rotation.w();
	const float _2yy = _2y * i_rotation.y();
	const float _2yz = _2y * i_rotation.z();
	const float _2yw = _2y * i_rotation.w();
	const float _2zz = _2z * i_rotation.z();
	const float _2zw = _2z * i_rotation.w();

	m_00 = 1.0f - _2yy - _2zz;
	m_10 = _2xy + _2zw;
	m_20 = _2xz - _2yw;

	m_01 = _2xy - _2zw;
	m_11 = 1.0f - _2xx - _2zz;
	m_21 = _2yz + _2xw;

	m_02 = _2xz + _2yw;
	m_12 = _2yz - _2xw;
	m_22 = 1.0f - _2xx - _2yy;
}


Engine::Math::Matrix4x4::Matrix4x4(const Vector3& i_translation, bool direction)	
{
	m_00 = 1.0f; m_01 = 0.0f; m_02 = 0.0f; m_03 = 0.0f;
	m_10 = 0.0f; m_11 = 1.0f; m_12 = 0.0f; m_13 = 0.0f;
	m_20 = 0.0f; m_21 = 0.0f; m_22 = 1.0f; m_23 = 0.0f;
	m_30 = 0.0f; m_31 = 0.0f; m_32 = 0.0f; m_33 = 1.0f;

	if(direction)
		m_33 = 0.0f;
	m_30 = i_translation.x;
	m_31 = i_translation.y;
	m_32 = i_translation.z;
}

Engine::Math::Matrix4x4::Matrix4x4(const Quaternion& i_rotation, bool direction)	
{
	/*
	http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/index.htm
	*/
	/*
	1−2(y^2+ z^2)	 2(xy−wz)		 2(xz+wy)
	2(xy+wz)		 1−2(x^2+z^2)	 2(yz−wx)
	2(xz−wy)		 2(yz+wx)		 1−2(x^2+y^2)
	*/

	m_00 = 1.0f; m_01 = 0.0f; m_02 = 0.0f; m_03 = 0.0f;
	m_10 = 0.0f; m_11 = 1.0f; m_12 = 0.0f; m_13 = 0.0f;
	m_20 = 0.0f; m_21 = 0.0f; m_22 = 1.0f; m_23 = 0.0f;
	m_30 = 0.0f; m_31 = 0.0f; m_32 = 0.0f; m_33 = 1.0f;

	if (direction)
		m_33 = 0.0f;

	//Only rotation part Assignment below
	const float _2x = i_rotation.x() + i_rotation.x();
	const float _2y = i_rotation.y() + i_rotation.y();
	const float _2z = i_rotation.z() + i_rotation.z();
	const float _2xx = i_rotation.x() * _2x;
	const float _2xy = _2x * i_rotation.y();
	const float _2xz = _2x * i_rotation.z();
	const float _2xw = _2x * i_rotation.w();
	const float _2yy = _2y * i_rotation.y();
	const float _2yz = _2y * i_rotation.z();
	const float _2yw = _2y * i_rotation.w();
	const float _2zz = _2z * i_rotation.z();
	const float _2zw = _2z * i_rotation.w();

	m_00 = 1.0f - _2yy - _2zz;
	m_10 = _2xy + _2zw;
	m_20 = _2xz - _2yw;

	m_01 = _2xy - _2zw;
	m_11 = 1.0f - _2xx - _2zz;
	m_21 = _2yz + _2xw;

	m_02 = _2xz + _2yw;
	m_12 = _2yz - _2xw;
	m_22 = 1.0f - _2xx - _2yy;
}




Engine::Math::Matrix4x4::Matrix4x4(
	const float i_00, const float i_10, const float i_20, const float i_30,
	const float i_01, const float i_11, const float i_21, const float i_31,
	const float i_02, const float i_12, const float i_22, const float i_32,
	const float i_03, const float i_13, const float i_23, const float i_33 )
	:
	m_00( i_00 ), m_10( i_10 ), m_20( i_20 ), m_30( i_30 ),
	m_01( i_01 ), m_11( i_11 ), m_21( i_21 ), m_31( i_31 ),
	m_02( i_02 ), m_12( i_12 ), m_22( i_22 ), m_32( i_32 ),
	m_03( i_03 ), m_13( i_13 ), m_23( i_23 ), m_33( i_33 )
{

}


void Engine::Math::Matrix4x4::printMatrix4x4() const
{
	std::cout << "Matrix values is =\n";
	std::cout << m_00 << ", " << m_01 << ", " << m_02 << ", " << m_03 << std::endl;
	std::cout << m_10 << ", " << m_11 << ", " << m_12 << ", " << m_13 << std::endl;
	std::cout << m_20 << ", " << m_21 << ", " << m_22 << ", " << m_23 << std::endl;
	std::cout << m_30 << ", " << m_31 << ", " << m_32 << ", " << m_33 << std::endl;
}

