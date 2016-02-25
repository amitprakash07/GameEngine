#ifndef __OBJECT_H
#define __OBJECT_H

#include "../../Maths/Math.h"

namespace Engine
{
	class Object
	{
	public:
		virtual Math::Transformation getTransformation() = 0;
		virtual void setTransformation(Engine::Math::Vector3,
			Engine::Math::Quaternion = Engine::Math::Quaternion()) = 0;
		virtual void draw(bool) = 0;
		virtual bool isRenderable() const = 0;
		virtual bool isDebugObject() const = 0;
		Object() {}
		virtual ~Object() {}
	};
}

#endif