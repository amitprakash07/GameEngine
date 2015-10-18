#include "InputController.h"
#include "../WindowingSystem/WindowsProgram.h"
#include <windows.h>
#include "../../MessagingSystem/MessagingSystem.h"
#include "../../StringPoolManager/StringPool.h"
#include "../EngineCore.h"

Engine::SharedPointer<Engine::InputController> Engine::InputController::mInputController;

std::string Engine::InputController::getTypeInfo()
{
	return mTypeName;
}

bool Engine::InputController::isBothSameType(RTTI* i_first, std::string i_second)
{
	if (i_first->getTypeInfo() == i_second)
		return true;
	return false;
}

void Engine::InputController::HandleMessage(Engine::utils::StringHash& i_message, Engine::RTTI* i_MessageSender, void* i_pMessageData)
{
	//SharedPointer<void> temp(*i_MessageSender);
	if(i_MessageSender != nullptr)
	{
		if (/*isBothSameType(i_MessageSender, Engine::EngineCore::getWindowingSystem()->getTypeInfo()) && (*/Engine::utils::StringHash("KeyDown") == i_message)//)
		{
			if (i_pMessageData)
			{
				Engine::typedefs::Direction dir;
				Engine::utils::StringHash temp = Engine::EngineCore::getStringPool()->findString("UpdateGameObject");
				SharedPointer<InputController> tempInputController = Engine::EngineCore::getInputController();
				switch (reinterpret_cast<WPARAM>(i_pMessageData))
				{
				case VK_LEFT:
				case 0x41:
					dir = Engine::typedefs::LEFT;
					Engine::EngineCore::getMessagingSystem()->sendMessage(temp, tempInputController.getRawPointer(), &dir);
					break;
				case VK_RIGHT:
				case 0x44:
					dir = Engine::typedefs::RIGHT;
					Engine::EngineCore::getMessagingSystem()->sendMessage(temp, tempInputController.getRawPointer(), &dir);
					break;
				case VK_DOWN:
				case 0x53:
					dir = Engine::typedefs::DOWN;
					Engine::EngineCore::getMessagingSystem()->sendMessage(temp, tempInputController.getRawPointer(), &dir);
					break;
				case VK_UP:
				case 0x57:
					dir = Engine::typedefs::UP;
					Engine::EngineCore::getMessagingSystem()->sendMessage(temp, tempInputController.getRawPointer(), &dir);
					break;
				}
			}
		}
	}
}

Engine::InputController::InputController()
{
	mTypeName = "Engine::InputController";
}

Engine::SharedPointer<Engine::InputController> Engine::InputController::getInputController()
{
	if (mInputController.isNull())
	{
		SharedPointer<InputController> tempInputController(Engine::SharedPointer<InputController>(new InputController(), Engine::EngineCore::getStringPool()->findString("Engine::InputController")));
		mInputController = tempInputController;
		Engine::utils::StringHash temp = Engine::utils::StringHash(Engine::EngineCore::getStringPool()->findString("KeyDown"));
		Engine::EngineCore::getMessagingSystem()->addMessageHandler(temp, reinterpret_cast<IMessageHandler*>(tempInputController.getRawPointer()), Engine::typedefs::HIGH);
	}
	return mInputController;
}




