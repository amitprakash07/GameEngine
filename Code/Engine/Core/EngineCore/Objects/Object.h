#ifndef __OBJECT_H
#define __OBJECT_H

#include "../../Maths/Transform.h"
#include <string>
#include "../../../Graphics/typedefs.h"

namespace Engine
{
	class IObjectController;
	class Object
	{
	public:
		virtual Math::Transform getTransform() = 0;
		virtual void setTransform(Engine::Math::Vector3,
			Engine::Math::Quaternion = Engine::Math::Quaternion()) = 0;
		virtual void resetTransform() = 0;
		virtual void draw(bool) = 0;
		virtual bool isRenderable() const = 0;
		virtual bool isDebugObject() const = 0;
		virtual void updateObject() = 0;	
		virtual void setObjectController(IObjectController* objectController) = 0;
		virtual void setScale(float x = 1.0f, float y = 1.0f, float z = 1.0f) = 0;
		virtual std::string getMaterialName() = 0;
		virtual bool isCollidable() = 0;
		virtual bool isPhysicsEnabled() = 0;
		virtual void enableCollision(bool) = 0;
		virtual void enablePhysics(bool) = 0;
		virtual void castShadow(bool, Graphics::ShadowMethod) = 0;
		virtual bool castingShadowEnabled() = 0;
		virtual void receiveShadow(bool) = 0;
		virtual bool receivingShadowEnabled() = 0;
		virtual void setRenderable(bool) = 0;
		virtual bool IsPlayer() = 0;
		virtual void setPlayer(bool) = 0;
		virtual void setObjectType(ObjectType) = 0;
		virtual ObjectType getObjectType() = 0;
		Object() {}
		virtual ~Object() {}
	};
}

#endif