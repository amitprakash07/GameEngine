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
			void resetTransform() override;
			void generateCubeMap();
			void setDynamicTextureSamplerName(std::string samplerUniformName);	
			void setObjectController(IObjectController *) override;
			void updateObject() override;
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
			TextureResource texture;			
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