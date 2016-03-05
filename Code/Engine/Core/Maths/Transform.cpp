#include "Transform.h"
#include <iostream>


Engine::Math::Transform::Transform()
{
	position = Vector3(0.0f, 0.0f, 0.0f);
	orientation = Quaternion();
}

Engine::Math::Vector3 Engine::Math::Transform::getForwardVector() const
{
	return(getLocalToWorldMatrix().getInverse().mul(Vector3(0.0f, 0.0f, 1.0f),true));
}


Engine::Math::Matrix4x4 Engine::Math::Transform::getLocalToWorldMatrix() const
{
	return(Matrix4x4(orientation, position));
}


void Engine::Math::Transform::TransformTo(Vector3& iPoint)const
{
	iPoint = getLocalToWorldMatrix().getInverse().mul(iPoint,false);
}

void Engine::Math::Transform::TransformFrom(Vector3& iPoint)const
{
	iPoint = getLocalToWorldMatrix().mul(iPoint, false);
}


void Engine::Math::Transform::VectorTransformFrom(Vector3& iDir)const
{
	iDir = getLocalToWorldMatrix().mul(iDir, true);
}

void Engine::Math::Transform::VectorTransformTo(Vector3& iDir)const
{
	iDir = getLocalToWorldMatrix().getInverse().mul(iDir, true);
}

Engine::Math::Vector3 Engine::Math::Transform::getPosition() const
{
	return position;
}

Engine::Math::Quaternion Engine::Math::Transform::getOrientation() const
{
	return orientation;
}


void Engine::Math::Transform::setForwardVector(const Vector3 i_forwardVector)
{
	forwardVector = i_forwardVector;
}


void Engine::Math::Transform::getEulerAngles() const
{
	//to do
}


void Engine::Math::Transform::rotateByEulerAngles(
	const float angleInRadiansForPitch, 
	const float angleInRadiansForYaw, 
	const float angleInRadiansForRoll)
{
	//to do 
}


void Engine::Math::Transform::translate(Vector3 iVector)
{
	position += iVector;
}


void Engine::Math::Transform::rotate(const float angleInRadians,const Vector3 axisOfRotation)
{
	orientation = orientation * Quaternion(angleInRadians, axisOfRotation.CreateNormalized());
}

void Engine::Math::Transform::rotate(const Quaternion rotor)
{
	orientation = orientation * rotor;
}

void Engine::Math::Transform::setOrientation(Quaternion newOrientation)
{
	orientation = newOrientation;
}


void Engine::Math::Transform::setPosition(Vector3 newPosition)
{
	position = newPosition;
}


void Engine::Math::Transform::printTransform()const
{
	std::cout << "Position is ";
	position.printVector();
	std::cout << "Orientation is ";
	orientation.printQuaternion();
}

















