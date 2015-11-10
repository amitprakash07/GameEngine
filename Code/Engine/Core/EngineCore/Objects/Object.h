#ifndef __OBJECT_H
#define __OBJECT_H

#include "../../Maths/cVector.h"
#include "../../Maths/cQuaternion.h"

namespace Engine
{
	struct Transformation
	{
		Engine::Math::cVector mPositionOffset;
		Engine::Math::cQuaternion mOrientation;
		Transformation()
		{
			mPositionOffset = Math::cVector();
			mOrientation = Math::cQuaternion();
		}
	};

	class Object
	{
	public:
		virtual Transformation getTransformation() = 0;
		virtual void setTransformation(Engine::Math::cVector, 
			Engine::Math::cQuaternion = Engine::Math::cQuaternion()) = 0;
		Object(){}
		~Object(){}
	};
}

#endif