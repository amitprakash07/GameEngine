//#include "DebugMenu.h"
//#include "../EngineCore/EngineCore.h"
//#include "../../Graphics/Slider.h"
//#include "../../Graphics/Text.h"
//#include "../../Graphics/Button.h"
//#include "../../Graphics/CheckBox.h"
//
//
//void Engine::Debug::DebugMenu::HandleMessage(
//	Engine::utils::StringHash&,
//	SharedPointer<RTTI> i_MessageSender,
//	void* i_pMessageData)
//{
//
//}
//
//void Engine::Debug::DebugMenu::CreateButton(std::string buttonName, Object& value)
//{
//	mDebugMenu->UIElementCount++;
//	SharedPointer<UI::Button> tempButton =
//		UI::Button::CreateButton(buttonName, Math::Transform());
//
//}
//
//
//void Engine::Debug::DebugMenu::CreateCheckBox(std::string iCheckBoxName, Object& value)
//{
//	
//}
//
//
//void Engine::Debug::DebugMenu::CreateSlider(std::string iSliderName, Object& value, float min, float max)
//{
//	
//}
//
//
//void Engine::Debug::DebugMenu::CreateText(std::string textName, Object& value)
//{
//	
//}
//
//
//Engine::Debug::DebugMenu::DebugMenu()
//{
//	UIElementCount = 0;
//	isActive = false;
//}
//
//
//Engine::SharedPointer<Engine::Debug::DebugMenu> Engine::Debug::DebugMenu::GetDebugMenu()
//{
//	if(!mDebugMenu.isNull())
//	{
//		SharedPointer<DebugMenu> tempDebugMenu =
//			SharedPointer<DebugMenu>(new DebugMenu(), "Engine::DebugMenu");
//
//		utils::StringHash temp = Engine::utils::StringHash(
//			Engine::EngineCore::getStringPool()->findString("DebugMenuHandler"));
//
//		EngineCore::getMessagingSystem()->addMessageHandler(temp, 
//			reinterpret_cast<IMessageHandler*>(tempDebugMenu.getRawPointer()), 
//			Engine::typedefs::HIGH);
//	}
//	return mDebugMenu;
//}
//
//
//bool Engine::Debug::DebugMenu::isActivated() const
//{
//	return isActive;
//}
//
//
//bool Engine::Debug::DebugMenu::isExist() const
//{
//	return mDebugMenuObjectList.size() > 0 ? true : false;
//}
//
//
//
//
//
//
//
//
//
//
//
