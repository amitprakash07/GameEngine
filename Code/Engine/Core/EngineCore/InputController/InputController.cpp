#include "InputController.h"
#include "../WindowingSystem/WindowsProgram.h"
#include <windows.h>
#include "../../MessagingSystem/MessagingSystem.h"
#include "../../StringPoolManager/StringPool.h"
#include "../EngineCore.h"

Engine::InputController* Engine::InputController::mInputController = nullptr;

std::string Engine::InputController::getTypeInfo()
{
	return mTypeName;
}

bool Engine::InputController::isBothSameType(SharedPointer<RTTI> i_first, std::string i_second)
{
	if (i_first->getTypeInfo() == i_second)
		return true;
	return false;
}

void Engine::InputController::HandleMessage(Engine::utils::StringHash& i_message, RTTI* i_MessageSender, void* i_pMessageData)
{
	if(i_MessageSender==nullptr)
	{
		if (isBothSameType(i_MessageSender, Engine::EngineCore::getWindowingSystem()->getTypeInfo()) && (Engine::utils::StringHash("KeyDown") == i_message))
		{
			if (i_pMessageData)
			{
				Engine::typedefs::Direction dir;
				Engine::utils::StringHash temp = Engine::EngineCore::getStringPool()->findString("UpdateGameObject");
				switch (reinterpret_cast<WPARAM>(i_pMessageData))
				{
				case VK_LEFT:
					dir = Engine::typedefs::LEFT;
					Engine::EngineCore::getMessagingSystem()->sendMessage(temp, mInputController, &dir);
					break;
				case VK_RIGHT:
					dir = Engine::typedefs::RIGHT;
					Engine::EngineCore::getMessagingSystem()->sendMessage(temp, mInputController, &dir);
					break;
				case VK_DOWN:
					dir = Engine::typedefs::DOWN;
					Engine::EngineCore::getMessagingSystem()->sendMessage(temp, mInputController, &dir);
					break;
				case VK_UP:
					dir = Engine::typedefs::UP;
					Engine::EngineCore::getMessagingSystem()->sendMessage(temp, mInputController, &dir);
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
	if (mInputController == nullptr)
	{
		mInputController = new InputController();
		Engine::utils::StringHash temp = Engine::utils::StringHash(Engine::EngineCore::getStringPool()->findString("KeyDown"));
		Engine::EngineCore::getMessagingSystem()->addMessageHandler(temp, mInputController, Engine::typedefs::HIGH);
	}
	return mInputController;
}




