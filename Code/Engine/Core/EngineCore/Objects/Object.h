#ifndef __OBJECT_H
#define __OBJECT_H

#include "../enginedefs.h"

namespace Engine
{
	class Object
	{
	public:
		virtual Transformation getTransformation() = 0;
		virtual void setTransformation(Engine::Math::cVector,
			Engine::Math::cQuaternion = Engine::Math::cQuaternion()) = 0;
		virtual void draw(bool) = 0;
		virtual bool isRenderable() const = 0;
		virtual bool isDebugObject() const = 0;
		Object() {}
		virtual ~Object() {}
	};
}

#endif