#include "EngineCore.h"
#include "..\..\Windows\WindowsFunctions.h"
#include "..\..\Graphics\Graphics.h"
#include "..\..\Graphics/Effect.h"
#include "..\..\Graphics/Mesh.h"
#include "Objects/Scene.h"
#include <iostream>
#include "../../Graphics/Material.h"



Engine::SharedPointer<Engine::MessagingSystem> Engine::EngineCore::mMessagingSystem;
Engine::SharedPointer<Engine::StringPool> Engine::EngineCore::mStringPool;
Engine::SharedPointer<Engine::Windows::WindowingSystem> Engine::EngineCore::mEngineWindowingSystem;
Engine::SharedPointer<Engine::InputController> Engine::EngineCore::mInputController;
Engine::SharedPointer<Engine::MouseController> Engine::EngineCore::mMouseController;
std::string Engine::EngineCore::materialFolderPath;
std::string Engine::EngineCore::shaderFolderName;
std::string Engine::EngineCore::effectFolderName;
std::string Engine::EngineCore::meshFolderName;
std::string Engine::EngineCore::textureFolderName;



void Engine::EngineCore::Initialize(HINSTANCE hInstance, int windowLayout)
{
	getMessagingSystem();
	getStringPool();
	getWindowingSystem();
	getInputController();
	getMouseInputController();
	
	std::stringstream errormessage;
	if (!getWindowingSystem().isNull())
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
	if(mEngineWindowingSystem.isNull())
	{
		SharedPointer<Engine::Windows::WindowingSystem> tempWindowingSystem = 
			Engine::Windows::WindowingSystem::getWindowingSystem();
		mEngineWindowingSystem = tempWindowingSystem;
	}
	return mEngineWindowingSystem;
}

Engine::SharedPointer<Engine::MessagingSystem> Engine::EngineCore::getMessagingSystem()
{
	if(mMessagingSystem.isNull())
	{
		SharedPointer<Engine::MessagingSystem> tempMessagingSystem = Engine::MessagingSystem::getMessagingSystem();
		mMessagingSystem = tempMessagingSystem;
	}		
	return mMessagingSystem;
}

Engine::SharedPointer<Engine::StringPool> Engine::EngineCore::getStringPool()
{
	if (mStringPool.isNull())
	{
		SharedPointer<Engine::StringPool> tempStringPool = Engine::StringPool::getStringPool();
		mStringPool = tempStringPool;
	}	
	return mStringPool;
}

Engine::SharedPointer<Engine::InputController> Engine::EngineCore::getInputController()
{
	if(mInputController.isNull())
	{
		Engine::SharedPointer<Engine::InputController> tempInputcontroller =
			Engine::InputController::getInputController();
		mInputController = tempInputcontroller;
	}
	return mInputController;
}

Engine::SharedPointer<Engine::MouseController> Engine::EngineCore::getMouseInputController()
{
	if(mMouseController.isNull())
	{
		Engine::SharedPointer<Engine::MouseController> tempMouseController =
			Engine::MouseController::getMouseController();
		mMouseController = tempMouseController;
	}
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













