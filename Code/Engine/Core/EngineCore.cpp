
#include "EngineCore.h"
#include "..\Windows\WindowsProgram.h"
#include "..\Graphics\Graphics.h"
#include "..\Graphics\Scene.h"
#include "..\Windows\WindowsFunctions.h"
#include "..\Graphics\Effects.h"

void Engine::EngineCore::Initialize(HINSTANCE hInstance, int windowLayout)
{
	std::stringstream errormessage;
	Engine::WindowUtil::WindowingSystem::CreateMainWindow(hInstance, windowLayout);
	if (Engine::Graphics::GraphicsSystem::Initialize(Engine::WindowUtil::WindowingSystem::getMainWindow()))
	{
		if (!Engine::Graphics::Effects::addEffect("data/standard.vshd", "data/standard.fshd"))
		{
			errormessage << "Unable to set the shader effets";
			WindowsUtil::Print(errormessage.str());
			exit(0);
		} 

		if (!Engine::Graphics::Scene::addToScene("data/SquareMesh.mesh"))
		{
			errormessage << "Unable to add the Mesh";
			WindowsUtil::Print(errormessage.str());
			exit(0);
		}
		if (!Engine::Graphics::Scene::addToScene("data/TriangleMesh.mesh"))
		{
			errormessage << "Unable to add the Mesh";
			WindowsUtil::Print(errormessage.str());
			exit(0);
		}
	}
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
	if (Engine::WindowUtil::WindowingSystem::getMainWindow() == nullptr)
	{
		if (Engine::WindowUtil::WindowingSystem::OnMainWindowClosed(hInstance))
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
	Engine::Graphics::Effects::removeAllEffects();
	Engine::Graphics::Scene::deleteScene();
}
Engine::SharedPointer<Engine::MessagingSystem> Engine::EngineCore::getMessagingSystem()
{
	return Engine::MessagingSystem::getMessagingSystem();
}
Engine::SharedPointer<Engine::Time::FrameTime> Engine::EngineCore::getFrameTimeController()
{
	return Engine::Time::FrameTime::getFrameTimeController();
}
Engine::SharedPointer<Engine::StringPool> Engine::EngineCore::getStringPool()
{
	return Engine::StringPool::getStringPool();
}


