#ifndef __SLIDER_H
#define __SLIDER_H
#include "../Core/EngineCore/Objects/Object.h"
#include "../Core/Utilities/IMessageHandler.h"
#include "Light.h"
#include "Text.h"

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
				float min,
				Math::Transform iTransform);			
			//Object Functions
			Math::Transform getTransform() override;
			void setTransform(Engine::Math::Vector3,
				Engine::Math::Quaternion = Engine::Math::Quaternion()) override;
			void resetTransform() override;
			void draw(bool) override;
			bool isRenderable() const override { return true; }
			bool isDebugObject() const override { return false; }
			void updateObject() override;
			void setObjectController(SharedPointer<IObjectController>objectController) override;
			void setScale(float x = 1.0f, float y = 1.0f, float z = 1.0f) override;
			Math::Vector3 getScale() const override;
			std::string getMaterialName() override { return "None"; }
			void SetMaterial(std::string iMaterialName) override{}
			bool isCollidable() override { return false; }
			bool isPhysicsEnabled() override { return false; }
			void enableCollision(bool) override {}
			void enablePhysics(bool) override {}
			void castShadow(bool, Graphics::ShadowMethod) override {}
			bool castingShadowEnabled() override { return false; }
			void receiveShadow(bool) override { }
			bool receivingShadowEnabled() override { return false; }
			void setRenderable(bool) override {}
			bool IsPlayer() override { return false; }
			void setPlayer(bool) override {}
			void setObjectType(ObjectType) override{}
			ObjectType getObjectType() override { return ObjectType::NONE; }
			bool isSSAOEnabled() override { return false; }
			void EnableSSAO(bool) override {}
			void SetVertexColor(float iR, float iG, float iB, float iA) override;
			Graphics::RGBAColor GetVertexColor() const override;

			//IMessageHnadler functions
			void HandleMessage(Engine::utils::StringHash &, SharedPointer<RTTI> i_MessageSender, void* i_pMessageData) override; //Do not delete i_messageSenderPointer
			std::string getTypeInfo() const override { return ""; }
			bool isBothSameType(SharedPointer<RTTI>, std::string) const override { return true; }
		private:
			float* vlaueToBeChanged;
			float min;
			float max;
			Slider();			
			SharedPointer<Graphics::Text> mName;
			SharedPointer<Graphics::Text> mTextSlider;
		};
	}
}

#endif
