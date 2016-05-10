#ifndef __SLIDER_H
#define __SLIDER_H
#include "../Core/EngineCore/Objects/Object.h"
#include "../Core/Utilities/IMessageHandler.h"
#include "Light.h"

namespace Engine
{
	namespace UI
	{
		class Slider :public IMessageHandler, Object
		{
		public:
			static SharedPointer<Slider> CreateSlider(std::string iName, 
				float* value, 
				float max, 
				float min);			
			//Object Functions
			Math::Transform getTransform() override;
			void setTransform(Engine::Math::Vector3,
				Engine::Math::Quaternion = Engine::Math::Quaternion()) override;
			void resetTransform() override;
			void draw(bool) override;
			bool isRenderable() const override;
			bool isDebugObject() const override;
			void updateObject() override;
			void setObjectController(IObjectController* objectController) override;
			void setScale(float x = 1.0f, float y = 1.0f, float z = 1.0f) override;
			Math::Vector3 getScale() const override;
			std::string getMaterialName() override;
			void SetMaterial(std::string iMaterialName) override;
			bool isCollidable() override;
			bool isPhysicsEnabled() override;
			void enableCollision(bool) override;
			void enablePhysics(bool) override;
			void castShadow(bool, Graphics::ShadowMethod) override;
			bool castingShadowEnabled() override;
			void receiveShadow(bool) override;
			bool receivingShadowEnabled() override;
			void setRenderable(bool) override;
			bool IsPlayer() override;
			void setPlayer(bool) override;
			void setObjectType(ObjectType) override;
			ObjectType getObjectType() override;
			bool isSSAOEnabled() override;
			void EnableSSAO(bool) override;
			void SetVertexColor(float iR, float iG, float iB, float iA) override;
			Graphics::RGBAColor GetVertexColor() const override;

			//IMessageHnadler functions
			void HandleMessage(Engine::utils::StringHash &, RTTI* i_MessageSender, void* i_pMessageData) override; //Do not delete i_messageSenderPointer
			std::string getTypeInfo() const override;
			bool isBothSameType(RTTI*, std::string) const override ;
		private:
			float* vlaueToBeChanged;
		};
	}
}

#endif
