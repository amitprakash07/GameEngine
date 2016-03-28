#ifndef __LIGHT_H
#define __LIGHT_H

#include "../Core/Utilities/SharedPointer.h"
#include "typedefs.h"
#include "../Core/EngineCore/Objects/Object.h"
#include "../Core/Utilities/IMessageHandler.h"

namespace Engine
{
	namespace Graphics
	{
		class Light:public IMessageHandler, Engine::Object
		{
		public:
			static SharedPointer<Light> addLight(std::string iLightName, LightType iLightType);
			static SharedPointer<Light> getLight(std::string iLightName, LightType);
			void setIntensity(float iIntensity);
			void setColor(Math::Vector3 iColor);

			//Object functions
			Math::Transform getTransform() override;
			void setTransform(Engine::Math::Vector3 iPosition, Engine::Math::Quaternion iRotation) override;
			void resetTransform() override;
			void draw(bool drawable) override;
			bool isRenderable() const override;
			bool isDebugObject() const override;
			void updateObject() override;
			void setObjectController(IObjectController* iObjectController) override;
			void setScale(float iX, float iY, float iZ) override;

			//IMessageHandler functions
			void HandleMessage(
				Engine::utils::StringHash &,
				RTTI* i_MessageSender, void* i_pMessageData) override;
			std::string getTypeInfo() const override;

			
		};
	}
}

#endif