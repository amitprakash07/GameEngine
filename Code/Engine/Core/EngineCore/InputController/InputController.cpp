#include "InputController.h"
#include "../WindowingSystem/WindowsProgram.h"
#include <windows.h>
#include "../../MessagingSystem/MessagingSystem.h"
#include "../../StringPoolManager/StringPool.h"
#include "../EngineCore.h"
#include "../../Debugging/DebugMenu.h"
#include "../Objects/Scene.h"
#include "../../Physics/PhysicsSystem.h"

Engine::SharedPointer<Engine::InputController> Engine::InputController::mInputController;

std::string Engine::InputController::getTypeInfo() const
{
	return mTypeName;
}

bool Engine::InputController::isBothSameType(SharedPointer<RTTI> i_first, std::string i_second) const
{
	if (i_first->getTypeInfo() == i_second)
		return true;
	return false;
}

void Engine::InputController::HandleMessage(Engine::utils::StringHash& i_message,
	SharedPointer<RTTI> i_MessageSender, 
	void* i_pMessageData)
{
	if (!i_MessageSender.isNull())
	{
		if (Engine::utils::StringHash("KeyDown") == i_message)
		{
			if (i_pMessageData && Scene::getRenderableScene()->IsNewFrame())
			{
				Engine::typedefs::ActionWithKeyBound action;
				Engine::utils::StringHash gameObjectController = Engine::EngineCore::getStringPool()->findString("UpdateObject");
				Engine::utils::StringHash debugMenuController = Engine::EngineCore::getStringPool()->findString("DebugMenuHandler");
				SharedPointer<InputController> tempInputController = Engine::EngineCore::getInputController();
				action.keyVal = reinterpret_cast<WPARAM>(i_pMessageData);
				action.action = typedefs::Default;				
				
				
				if (action.keyVal == VK_OEM_3)
				{
					bool CurrentStatus = Debug::DebugMenu::GetDebugMenu()->isActivated();
					Debug::DebugMenu::GetDebugMenu()->Activate(!CurrentStatus);
				}					

				if (Debug::DebugMenu::GetDebugMenu()->isActivated())
					EngineCore::getMessagingSystem()->sendMessage(debugMenuController,
						tempInputController.CastSharedPointer<RTTI>(), &action);
				else
					EngineCore::getMessagingSystem()->sendMessage(gameObjectController,
						tempInputController.CastSharedPointer<RTTI>(), &action);
				
				if(Physics::PhysicsSystem::GetPhysicsSystem()->CollisionDebuggingStatus())
				{
					EngineCore::getMessagingSystem()->sendMessage(gameObjectController,
						tempInputController.CastSharedPointer<RTTI>(), &action);
				}

				Scene::getRenderableScene()->SetNewFrame(false);
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
		Engine::EngineCore::getMessagingSystem()->addMessageHandler(temp, 
			tempInputController.CastSharedPointer<IMessageHandler>(), Engine::typedefs::HIGH);
	}
	return mInputController;
}




