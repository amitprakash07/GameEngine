#ifndef __TRANSFORM_H
#define __TRANSFORM_H

#include "Quaternion.h"
#include "Vector3.h"
#include "Matrix4x4.h"

namespace Engine
{
	namespace Math
	{
		class Transform
		{
		public:	
			Transform();			
			Vector3 getPosition()const;
			Quaternion getOrientation()const;
			Vector3 getForwardVector()const;
			void setForwardVector(const Vector3 forWardVector);
			void setPosition(const Vector3 newPosition);
			void setOrientation(const Quaternion newOrientation);
			void rotateByEulerAngles(const float angleInRadiansForPitch,
				const float angleInRadiansForYaw,
				const float angleInRadiansForRoll);
			void getEulerAngles() const;
			Matrix4x4 getLocalToWorldMatrix()const;	
			void TransformTo(Vector3& iPoint)const;
			void TransformFrom(Vector3& iPoint)const;
			void VectorTransformTo(Vector3& iDir)const;
			void VectorTransformFrom(Vector3& iDir)const;
		private:
			Vector3 position;
			Quaternion orientation;
			Vector3 forwardVector;
			Vector3 eulerAngles;
		};
	}
}

#endif
