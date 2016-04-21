#ifndef __REFLECTING_OBJECT_H
#define __REFLECTING_OBJECT_H

#include "../Core/EngineCore/Objects/Object.h"
#include "../Core/Utilities/SharedPointer.h"
#include <string>
#include "typedefs.h"
#include "../Core/EngineCore/Objects/Camera.h"

namespace Engine
{
	namespace Graphics
	{
		class ReflectingObject:public Object
		{
		public:
			static SharedPointer<ReflectingObject> CreateReflectingObject(
				std::string meshName, std::string materialName,
				float nearPlane, float farPlane);
			Engine::Math::Transform getTransform() override;
			void setTransform(Engine::Math::Vector3 position,
				Engine::Math::Quaternion rotation) override;
			bool isRenderable() const override;
			bool isDebugObject() const override;
			void draw(bool) override;	
			void setRenderable(bool iRenderable) override { /*to-do*/ }
			void resetTransform() override;
			void generateCubeMap();
			void setDynamicTextureSamplerName(std::string samplerUniformName);	
			void setObjectController(IObjectController *) override;
			void updateObject() override;
			void setScale(float x = 1.0f, float y = 1.0f, float z = 1.0f) override;
			std::string getMaterialName() override { return materialName; }
			bool isCollidable() override;
			bool isPhysicsEnabled() override;
			void enableCollision(bool) override;
			void enablePhysics(bool) override;
			void castShadow(bool, Graphics::ShadowMethod) override;
			bool castingShadowEnabled() override;
			void receiveShadow(bool) override;
			bool receivingShadowEnabled() override;
			bool IsPlayer() override;
			void setPlayer(bool i_isPlayer) override;
			void setObjectType(ObjectType iObjectType) override;
			ObjectType getObjectType() override;
		private:
			ReflectingObject();
			bool init();
			IObjectController *mObjectController;
			bool cubeMapGenerated;
			SharedPointer<Engine::Camera> environmentCamera;
			bool cameraCreated;
			std::string meshName;
			std::string materialName;
			std::string textureName;
			std::string dynamicTextureSamplerName;
			Math::Vector3 scaleFactor;
			TextureResource texture;
			bool isPlayer;
			ObjectType mObjectType;
			void renderScene();
#ifdef PLATFORM_OPEN_GL
			GLuint renderBuffer[6];
			GLuint frameBuffer[6];
#endif
			Engine::Math::Transform mTransform;
			Math::Transform mInitialTransform;
			bool isInitialTransform;
		};
	}
}

#endif