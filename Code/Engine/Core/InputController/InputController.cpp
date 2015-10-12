#include "InputController.h"
#include "../EngineCore/WindowsProgram.h"
#include "../EngineCore/EngineCore.h"
#include <windows.h>
#include  "../EngineCore/additionaltypes.h"

Engine::InputController* Engine::InputController::mInputController = nullptr;

void Engine::InputController::HandleMessage(Engine::utils::StringHash& i_message, RTTI* i_MessageSender, void* i_pMessageData)
{
	if(i_MessageSender)
	{
		if (Engine::EngineCore::getWindowingSystem().isBothSameType(i_MessageSender) && (Engine::utils::StringHash("KeyDown") == i_message))
		{
			if (i_pMessageData)
			{
				Engine::typedefs::Direction dir;
				switch (reinterpret_cast<WPARAM>(i_pMessageData))
				{
				case VK_LEFT:
					dir = Engine::typedefs::LEFT;
					Engine::EngineCore::getMessagingSystem()->sendMessage(Engine::EngineCore::getStringPool()->findString("UpdateGameObject"), mInputController, &dir);
					break;
				case VK_RIGHT:
					dir = Engine::typedefs::RIGHT;
					Engine::EngineCore::getMessagingSystem()->sendMessage(Engine::EngineCore::getStringPool()->findString("UpdateGameObject"), mInputController, &dir);
					break;
				case VK_DOWN:
					dir = Engine::typedefs::DOWN;
					Engine::EngineCore::getMessagingSystem()->sendMessage(Engine::EngineCore::getStringPool()->findString("UpdateGameObject"), mInputController, &dir);
					break;
				case VK_UP:
					dir = Engine::typedefs::UP;
					Engine::EngineCore::getMessagingSystem()->sendMessage(Engine::EngineCore::getStringPool()->findString("UpdateGameObject"), mInputController, &dir);
					break;
				}
			}
		}
	}
}

Engine::InputController::InputController()
{
	setTypeInfo("Engine::InputController");	
}

Engine::SharedPointer<Engine::InputController> Engine::InputController::getINputController()
{
	if (mInputController == nullptr)
	{
		mInputController = new InputController();
		Engine::utils::StringHash temp = Engine::utils::StringHash(Engine::EngineCore::getStringPool()->findString("UpdateGameObject"));
		Engine::EngineCore::getMessagingSystem()->addMessageHandler(temp, mInputController, Engine::typedefs::HIGH);
	}
	return mInputController;
}


