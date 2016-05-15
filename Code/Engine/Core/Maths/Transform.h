#ifndef __TRANSFORM_H
#define __TRANSFORM_H

#include "Quaternion.h"
#include "Vector3.h"
#include "Matrix4x4.h"

namespace Engine
{
	namespace Math
	{
		enum RotationAxis
		{
			Up,
			Right,
			Forward
		};
		class Transform
		{
		public:	
			Transform();
			Transform(Math::Vector3 iPosition, Math::Quaternion iOrientation);
			Vector3 getPosition()const;
			Quaternion getOrientation()const;
			Vector3 getForwardVector()const;
			Vector3 getRightVector() const;
			Vector3 getUpVector() const;
			void setForwardVector(const Vector3 forWardVector);
			void setPosition(const Vector3 newPosition);
			void setOrientation(const Quaternion newOrientation);
			void rotateByEulerAngles(const float angleInRadiansForPitch,
				const float angleInRadiansForYaw,
				const float angleInRadiansForRoll);
			void getEulerAngles() const;
			void MoveForward(float unit);
			void MoveBackWard(float unit);
			void MoveRight(float unit);
			void MoveLeft(float unit);
			void MoveUp(float unit);
			void MoveDown(float unit);
			void Move(Vector3 along, float unit);
			//void Slide(Vector3 along, float unit);
			void Rotate(const float angleInRadians, RotationAxis iRotationAxis);
			void Rotate(const float angleInRadians, Vector3 arbitraryAxis);
			void rotate(const Quaternion rotor);
			Matrix4x4 getLocalToWorldMatrix()const;	
			void TransformTo(Vector3& iPoint)const;
			void TransformFrom(Vector3& iPoint)const;
			void VectorTransformTo(Vector3& iDir)const;
			void VectorTransformFrom(Vector3& iDir)const;
			void printTransform()const;			
		private:
			Vector3 position;
			Quaternion orientation;
			Vector3 forwardVector;
			Vector3 rightVector;
			Vector3 upVector;
			Vector3 eulerAngles;
		};
	}
}

#endif
