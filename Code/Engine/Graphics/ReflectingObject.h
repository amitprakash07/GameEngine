#ifndef __REFLECTING_OBJECT_H
#define __REFLECTING_OBJECT_H

#include "../Core/EngineCore/Objects/Object.h"
#include "../Core/Utilities/SharedPointer.h"
#include <string>
#include <vector>
#include "typedefs.h"
#include "uniformdefs.h"

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
			void generateCubeMap();
		private:			
			ReflectingObject();
			bool initialized;
			bool init();
			std::string meshName;
			std::string materialName;
			ShaderType shaderType;
			TextureResource texture;
			SamplerID textureSamplerID;
			TextureType textureType;
#ifdef PLATFORM_OPEN_GL
			GLuint renderBuffer[6];
			GLuint frameBuffer[6];
#endif
			Engine::Math::Transform mTransform;
		};
	}
}

#endif