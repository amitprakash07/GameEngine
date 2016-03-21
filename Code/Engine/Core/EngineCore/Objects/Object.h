#ifndef __OBJECT_H
#define __OBJECT_H

#include "../../Maths/Transform.h"

namespace Engine
{
	class IObjectController;
	class Object
	{
	public:
		virtual Math::Transform getTransform() = 0;
		virtual void setTransform(Engine::Math::Vector3,
			Engine::Math::Quaternion = Engine::Math::Quaternion()) = 0;
		virtual void draw(bool) = 0;
		virtual bool isRenderable() const = 0;
		virtual bool isDebugObject() const = 0;
		virtual void updateObject() = 0;	
		virtual void setObjectController(IObjectController* objectController) = 0;
		Object() {}
		virtual ~Object() {}
	};
}

#endif