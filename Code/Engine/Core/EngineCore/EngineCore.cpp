
#include "EngineCore.h"
#include "..\..\Graphics\Graphics.h"
#include "..\..\Windows\WindowsFunctions.h"
#include "Objects/Scene.h"
#include <iostream>


Engine::SharedPointer<Engine::MessagingSystem> Engine::EngineCore::mMessagingSystem = Engine::MessagingSystem::getMessagingSystem();
Engine::SharedPointer<Engine::StringPool> Engine::EngineCore::mStringPool = Engine::StringPool::getStringPool();
Engine::SharedPointer<Engine::WindowUtil::WindowingSystem> Engine::EngineCore::mWindowingSystem = Engine::WindowUtil::WindowingSystem::getWindowingSystem();
Engine::SharedPointer<Engine::InputController> Engine::EngineCore::mInputController = Engine::InputController::getInputController();
//Engine::SharedPointer<Engine::EngineCore> Engine::EngineCore::mEngineInstance;


void Engine::EngineCore::Initialize(HINSTANCE hInstance, int windowLayout)
{
	std::stringstream errormessage;	
	//mEngineInstance->mWindowingSystem = SharedPointer<Engine::WindowUtil::WindowingSystem>(Engine::WindowUtil::WindowingSystem::getWindowingSystem());
	if (!mWindowingSystem.isNull())
	{
		mWindowingSystem->CreateMainWindow(hInstance, windowLayout);
		if (!Engine::Graphics::GraphicsSystem::Initialize(mWindowingSystem->getMainWindow()))
		{
			errormessage << "Unable to initialize Graphics System";
			std::cerr << errormessage.str().c_str();
			/*mMessagingSystem = Engine::MessagingSystem::getMessagingSystem();
			mStringPool = Engine::StringPool::getStringPool();
			mInputController = Engine::InputController::getInputController();*/
		}
	}
}


Engine::EngineCore::EngineCore()
{

}

Engine::SharedPointer<Engine::WindowUtil::WindowingSystem> Engine::EngineCore::getWindowingSystem()
{
	return mWindowingSystem;
}

Engine::SharedPointer<Engine::MessagingSystem> Engine::EngineCore::getMessagingSystem()
{
	return mMessagingSystem;
}

Engine::SharedPointer<Engine::StringPool> Engine::EngineCore::getStringPool()
{
	return mStringPool;
}

Engine::SharedPointer<Engine::InputController> Engine::EngineCore::getInputController()
{
	return mInputController;
}

void Engine::EngineCore::onNewFrame()
{
	MSG message = {};
	bool hasWindowsSentAMessage;


	{
		HWND getMessagesFromAnyWindowBelongingToTheCurrentThread = nullptr;
		unsigned int getAllMessageTypes = 0;
		unsigned int ifAMessageExistsRemoveItFromTheQueue = PM_REMOVE;
		hasWindowsSentAMessage = PeekMessage(&message, getMessagesFromAnyWindowBelongingToTheCurrentThread,
			getAllMessageTypes, getAllMessageTypes, ifAMessageExistsRemoveItFromTheQueue) == TRUE;
	}

	if (!hasWindowsSentAMessage)
	{
		Engine::Graphics::GraphicsSystem::Render();
	}
	else
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

}

bool Engine::EngineCore::isWindowClosed(HINSTANCE hInstance)
{
	if (mWindowingSystem->getMainWindow() == nullptr)
	{
		if (mWindowingSystem->OnMainWindowClosed(hInstance))
			return true;
		else
		{
			std::stringstream errormessage;
			errormessage << "Unable to close and clean up the windowing system";
			WindowsUtil::Print(errormessage.str());
			return false;
		}
	}
	return false;
}

void Engine::EngineCore::shutDownEngine()
{
	mMessagingSystem.deleteObject();
	mStringPool.deleteObject();
	mInputController.deleteObject();
	Engine::Scene::deleteAllScene();
}













