
#ifdef _DEBUG
#ifndef __DEBUG_MENU_H
#define __DEBUG_MENU_H

#include "../Utilities/IMessageHandler.h"
#include "../Utilities/SharedPointer.h"
#include <map>

namespace Engine {
	class Object;
}

namespace Engine
{
	namespace Debug
	{
		enum UIElementType
		{
			Slider,
			CheckBox,
			Button,
			Text
		};
		class DebugMenu: public IMessageHandler
		{
		public:			
			static SharedPointer<DebugMenu> GetDebugMenu();
			void CreateSlider(std::string iSliderName, Object& value, float min, float max);
			void CreateCheckBox(std::string iCheckBoxName, Object& value);
			void CreateText(std::string textName, Object& value);
			void CreateButton(std::string buttonName, Object& value);
			bool isActivated() const;
			bool isExist() const;

			//IMessageHnadler functions
			void HandleMessage(Engine::utils::StringHash &, SharedPointer<RTTI> i_MessageSender, void* i_pMessageData) override; //Do not delete i_messageSenderPointer
			std::string getTypeInfo() const override { return ""; }
			bool isBothSameType(SharedPointer<RTTI>, std::string) const override { return true; }
		private:
			static SharedPointer<DebugMenu> mDebugMenu;
			uint16_t UIElementCount;
			bool isActive;
			std::map<int, std::map<UIElementType, Object*>> mDebugMenuObjectList;
			DebugMenu();					
		};
	}
}

#endif
#endif