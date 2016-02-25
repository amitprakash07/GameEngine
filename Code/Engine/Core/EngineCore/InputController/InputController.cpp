#include "InputController.h"
#include "../WindowingSystem/WindowsProgram.h"
#include <windows.h>
#include "../../MessagingSystem/MessagingSystem.h"
#include "../../StringPoolManager/StringPool.h"
#include "../EngineCore.h"

Engine::SharedPointer<Engine::InputController> Engine::InputController::mInputController;

std::string Engine::InputController::getTypeInfo() const
{
	return mTypeName;
}

bool Engine::InputController::isBothSameType(RTTI* i_first, std::string i_second) const
{
	if (i_first->getTypeInfo() == i_second)
		return true;
	return false;
}

void Engine::InputController::HandleMessage(Engine::utils::StringHash& i_message, Engine::RTTI* i_MessageSender, void* i_pMessageData)
{
	if (i_MessageSender != nullptr)
	{
		if (Engine::utils::StringHash("KeyDown") == i_message)
		{
			if (i_pMessageData)
			{
				Engine::typedefs::Action action;
				Engine::utils::StringHash gameObjectController = Engine::EngineCore::getStringPool()->findString("UpdateObject");
				SharedPointer<InputController> tempInputController = Engine::EngineCore::getInputController();
				switch (reinterpret_cast<WPARAM>(i_pMessageData))
				{
				case VK_LEFT:
					action = Engine::typedefs::MoveLeft;
					Engine::EngineCore::getMessagingSystem()->sendMessage(gameObjectController, tempInputController.getRawPointer(), &action);
					break;
				case 0x41:
					action = Engine::typedefs::MoveLeft;
					//Engine::EngineCore::getMessagingSystem()->sendMessage(cameraController, tempInputController.getRawPointer(), &action);
					break;
				case VK_RIGHT:
					action = Engine::typedefs::MoveRight;
					Engine::EngineCore::getMessagingSystem()->sendMessage(gameObjectController, tempInputController.getRawPointer(), &action);
					break;
				case 0x44:
					action = Engine::typedefs::MoveRight;
					//Engine::EngineCore::getMessagingSystem()->sendMessage(cameraController, tempInputController.getRawPointer(), &action);
					break;
				case VK_DOWN:
					action = Engine::typedefs::MoveBackWard;
					Engine::EngineCore::getMessagingSystem()->sendMessage(gameObjectController, tempInputController.getRawPointer(), &action);
					break;
				case 0x53:
					action = Engine::typedefs::MoveBackWard;
					//Engine::EngineCore::getMessagingSystem()->sendMessage(cameraController, tempInputController.getRawPointer(), &action);
					break;
				case VK_UP:
					action = Engine::typedefs::MoveForward;
					Engine::EngineCore::getMessagingSystem()->sendMessage(gameObjectController, tempInputController.getRawPointer(), &action);
					break;
				case 0x57:
					action = Engine::typedefs::MoveForward;
					//Engine::EngineCore::getMessagingSystem()->sendMessage(cameraController, tempInputController.getRawPointer(), &action);
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




