#include "Game.h"
#include "../../Engine/Core/EngineCore/EngineCore.h"
#include <windows.h>
#include <fstream>
#include <crtdbg.h>
#include "../../Engine/Core/EngineCore/Objects/Scene.h"
#include "../../Engine/Core/Utilities/SharedPointer.h"
#include "../../Engine/Core/EngineCore/Objects/GameObject.h"
#include "../../Engine/Core/EngineCore/ObjectController/WalkController.h"
#include "../../Engine/Core/EngineCore/ObjectController/CameraController.h"
#include "../../Engine/Core/EngineCore/Objects/Camera.h"




int WINAPI WinMain(HINSTANCE i_thisInstanceOfTheProgram,HINSTANCE,char* i_commandLineArguments,	int i_initialWindowDisplayState)
{
	{
		//_CrtSetBreakAlloc(156);
		Engine::EngineCore::Initialize(i_thisInstanceOfTheProgram, i_initialWindowDisplayState);
		Engine::SharedPointer<Engine::Scene> scene = Engine::Scene::CreateNewScene("TriangleSquareTriangle");
		Engine::SharedPointer<Engine::GameObject> square = Engine::GameObject::CreateGameObject("square", "data/Box.mesh", "standard", "data/standardEffect.effect");
		//Engine::SharedPointer<Engine::GameObject> triangleOne = Engine::GameObject::CreateGameObject("triangle", "data/TriangleMesh.mesh", "standard", "data/standardEffect.effect");
		//Engine::SharedPointer<Engine::GameObject> triangleTwo = Engine::GameObject::CreateGameObject("triangle", "data/TriangleMesh.mesh", "standard", "data/standardEffect.effect");
		square->setGameObjectController(new Engine::WalkController());
		//triangleOne->setPositionOffset(Engine::Math::cVector(0.75, 0.75, 0.25));
		//triangleOne->setPositionOffset(Engine::Math::cVector(-0.75, -0.75, -0.25));
		//triangleTwo->setPositionOffset(Engine::Math::cVector(0.75, 0.75, 0.25));
		//triangleTwo->setPositionOffset(Engine::Math::cVector(-0.75, -0.75, -0.25));
		Engine::SharedPointer<Engine::GameObject> floor = Engine::GameObject::CreateGameObject("Floor", "data/Floor.mesh", "standard", "data/standardEffect.effect");
		Engine::SharedPointer<Engine::Camera> mainCamera = Engine::Camera::CreateCamera("MainCamera", 
			Engine::Math::cVector(0,0,10),
			Engine::Math::cQuaternion());
		mainCamera->activateCamera(true);
		mainCamera->setAspectRatio(static_cast<float>(800 / 600));
		mainCamera->setFieldOfView(60.0f);
		mainCamera->setCameraController(new Engine::CameraController());
		scene->addGameObjectToScene(square);
		scene->addGameObjectToScene(floor);
		scene->addCameraToScene(mainCamera);
		//scene->addToScene(triangleOne);
		//scene->addToScene(triangleTwo);
		scene->renderScene(true);
		while (!Engine::EngineCore::isWindowClosed(i_thisInstanceOfTheProgram))
			Engine::EngineCore::onNewFrame();
		//Engine::EngineCore::shutDownEngine();
	}
	//_CrtDumpMemoryLeaks();
}