#ifndef __DEBUG_MENU_H
#define __DEBUG_MENU_H

#include "../Utilities/IMessageHandler.h"
#include "../Utilities/SharedPointer.h"
#include "../../Graphics/UIElement.h"
#include <map>


namespace Engine
{
	namespace Debug
	{
		class DebugMenu: public IMessageHandler, Object
		{
		public:			
			static SharedPointer<DebugMenu> GetDebugMenu();	
			std::map<int, Engine::SharedPointer<UI::UIElement>>
				GetDebugObjects() const;
			uint16_t GetElementCount() const;
			uint16_t GetCurrentSelectionIndex() const;
			void SetCurrentlySelected(uint8_t iSelected);
			void Activate(bool iRequest);

			void CreateSlider(std::string iSliderName, 
				SharedPointer<MeshObject> associatedObject,
				float min, 
				float max);
			void CreateCheckBox(std::string iCheckBoxName, 
				SharedPointer<MeshObject> associatedObject);
			void CreateText(std::string textName, std::string text,
				SharedPointer<MeshObject> associatedObject);
			void CreateButton(std::string buttonName, 
				SharedPointer<MeshObject> associatedObject);
			bool isActivated() const;
			bool isExist() const;
			
			//Object Overriding functions			
			Math::Transform getTransform() override { return mTransform; }
			void setTransform(Math::Vector3,
				Math::Quaternion = Math::Quaternion()) override{}
			void resetTransform() override {}
			bool isDebugObject() const override { return true; }
			bool isRenderable() const override { return true; }
			void draw(bool drawDebugObject) override{}
			void setRenderable(bool iRenderable) override{}
			void updateObject() override;
			void setObjectController(SharedPointer<IObjectController>)override;
			void setScale(float x = 1.0f, float y = 1.0f, float z = 1.0f) override{}
			Math::Vector3 getScale() const override { return Math::Vector3(1.0f); }
			Graphics::RGBAColor GetVertexColor() const override { return Graphics::RGBAColor(1.0f); }
			void SetVertexColor(float iR, float iG, float iB, float iA) override{}
			std::string getMaterialName() override { return "None"; }
			bool isCollidable() override { return false; }
			bool isPhysicsEnabled() override { return false; }
			void enableCollision(bool) override{}
			void enablePhysics(bool) override{}
			void castShadow(bool, Graphics::ShadowMethod) override{}
			bool castingShadowEnabled() override { return false; }
			void receiveShadow(bool) override{}
			bool receivingShadowEnabled() override { return false; }
			bool IsPlayer() override { return false; }
			void setPlayer(bool) override{}
			void setObjectType(ObjectType iObjectType) override{}
			ObjectType getObjectType() override { return ObjectType::NONE; }
			void SetMaterial(std::string iMaterialName) override{}
			bool isSSAOEnabled() override { return false; }
			void EnableSSAO(bool iRequest) override{}

			//IMessageHandler functions
			void HandleMessage(Engine::utils::StringHash &, 
				SharedPointer<RTTI> i_MessageSender, 
				void* i_pMessageData) override;
			std::string getTypeInfo() const override { return ""; }
			bool isBothSameType(SharedPointer<RTTI>, std::string) const override
			{ return true; }
		private:
			static SharedPointer<DebugMenu> mDebugMenu;
			uint16_t UIElementCount;
			uint16_t currentlySelected;
			bool isActive;
			std::map<int, Engine::SharedPointer<UI::UIElement>> mDebugMenuAssociatedObjectList;
			Math::Transform mTransform;				
			SharedPointer<IObjectController> mObjectController;
			DebugMenu();
		};
	}
}

#endif
