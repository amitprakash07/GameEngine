#include "EngineCore.h"
#include "..\..\Windows\WindowsFunctions.h"
#include "..\..\Graphics\Graphics.h"
#include "..\..\Graphics/Effect.h"
#include "..\..\Graphics/Mesh.h"
#include "Objects/Scene.h"
#include <iostream>
#include "../../Graphics/Material.h"



Engine::SharedPointer<Engine::MessagingSystem> Engine::EngineCore::mMessagingSystem =
Engine::MessagingSystem::getMessagingSystem();
Engine::SharedPointer<Engine::StringPool> Engine::EngineCore::mStringPool =
Engine::StringPool::getStringPool();
Engine::SharedPointer<Engine::Windows::WindowingSystem> Engine::EngineCore::mEngineWindowingSystem =
Engine::Windows::WindowingSystem::getWindowingSystem();
Engine::SharedPointer<Engine::InputController> Engine::EngineCore::mInputController =
Engine::InputController::getInputController();
Engine::SharedPointer<Engine::MouseController> Engine::EngineCore::mMouseController =
Engine::MouseController::getMouseController();


std::string Engine::EngineCore::materialFolderPath;
std::string Engine::EngineCore::shaderFolderName;
std::string Engine::EngineCore::effectFolderName;
std::string Engine::EngineCore::meshFolderName;
std::string Engine::EngineCore::textureFolderName;



void Engine::EngineCore::Initialize(HINSTANCE hInstance, int windowLayout)
{
	std::stringstream errormessage;
	if (!mEngineWindowingSystem.isNull())
	{
		mEngineWindowingSystem->CreateMainWindow(hInstance, windowLayout);
		if (!Engine::Graphics::GraphicsSystem::Initialize(mEngineWindowingSystem->getMainWindow()))
		{
			errormessage << "Unable to initialize Graphics System";
			std::cerr << errormessage.str().c_str();

		}
	}

	std::string other;
	const char* envName = "MeshDir";
	meshFolderName = "data/Meshes/";
	shaderFolderName = "data/Shaders/";
	materialFolderPath = "data/Materials/";
	effectFolderName = "data/Effects/";
	textureFolderName = "data/Textures/";
}

std::string Engine::EngineCore::getEffectFolderPath()
{
	return effectFolderName;
}

std::string Engine::EngineCore::getMaterialFolderPath()
{
	return materialFolderPath;
}

std::string Engine::EngineCore::getMeshFolderPath()
{
	return meshFolderName;
}

std::string Engine::EngineCore::getShaderFolderPath()
{
	return shaderFolderName;
}

std::string Engine::EngineCore::getTextureFolderPath()
{
	return textureFolderName;
}


Engine::EngineCore::EngineCore()
{

}



Engine::SharedPointer<Engine::Windows::WindowingSystem> Engine::EngineCore::getWindowingSystem()
{
	return mEngineWindowingSystem;
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

Engine::SharedPointer<Engine::MouseController> Engine::EngineCore::getMouseInputController()
{
	return mMouseController;
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
	if (mEngineWindowingSystem->getMainWindow() == nullptr)
	{
		shutDownEngine();
		if (mEngineWindowingSystem->OnMainWindowClosed(hInstance))
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
	Engine::Scene::deleteAllScene();
	Engine::Graphics::Mesh::deleteAllMesh();
	Engine::Graphics::Effect::deleteAllEffect();
	mMessagingSystem.deleteObject();
	mStringPool.deleteObject();
	mInputController.deleteObject();
}













