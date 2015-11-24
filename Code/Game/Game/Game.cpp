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
		
		//Scene
		Engine::SharedPointer<Engine::Scene> scene = Engine::Scene::CreateNewScene("Scene_01");
		
		//GameObjects
		/*Engine::SharedPointer<Engine::GameObject> room =
			Engine::GameObject::CreateGameObject("Floor", "data/Room.mesh", "standard", "data/standardEffect.effect");
		room->setTransformation(Engine::Math::cVector(0, -2, 0), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(room);*/

		/*Engine::SharedPointer<Engine::GameObject> cube =
			Engine::GameObject::CreateGameObject("data/TraansSphere_Maya.mesh", "data/standardMaterial.mat");
		cube->setTransformation(Engine::Math::cVector(-1, 0, -8), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(cube);*/

		/*Engine::SharedPointer<Engine::GameObject> cube =
			Engine::GameObject::CreateGameObject("data/Cube_Maya.mesh", "data/standardMaterial.mat");
		cube->setTransformation(Engine::Math::cVector(-1, 0, -8), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(cube);*/

		Engine::SharedPointer<Engine::GameObject> sphereOpaqueOne =
			Engine::GameObject::CreateGameObject("data/Sphere_Maya.mesh", "data/BlueStandard.mat");
		sphereOpaqueOne->setTransformation(Engine::Math::cVector(-3.5, 0, -5), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(sphereOpaqueOne);

		Engine::SharedPointer<Engine::GameObject> sphereOpaqueTwo =
			Engine::GameObject::CreateGameObject("data/Sphere_Maya.mesh", "data/GreenStandard.mat");
		sphereOpaqueTwo->setTransformation(Engine::Math::cVector(-1.5, 0, -5), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(sphereOpaqueTwo);

		Engine::SharedPointer<Engine::GameObject> sphereTranparentOne =
			Engine::GameObject::CreateGameObject("data/Sphere_Maya.mesh", "data/RedTransparent.mat");
		sphereTranparentOne->setTransformation(Engine::Math::cVector(0.5, 0, -5), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(sphereTranparentOne);

		Engine::SharedPointer<Engine::GameObject> sphereTranparentTwo =
			Engine::GameObject::CreateGameObject("data/Sphere_Maya.mesh", "data/YellowTransparent.mat");
		sphereTranparentTwo->setTransformation(Engine::Math::cVector(2.5, 0, -5), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(sphereTranparentTwo);
		
		Engine::SharedPointer<Engine::GameObject> floor =
			Engine::GameObject::CreateGameObject("data/Floor_Maya.mesh", "data/standardMaterial.mat");
		floor->setTransformation(Engine::Math::cVector(0, -2, -12), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(floor);
		
		Engine::SharedPointer<Engine::GameObject> helix =
		Engine::GameObject::CreateGameObject("data/Helix.mesh", "data/standardMaterial.mat");
		helix->setTransformation(Engine::Math::cVector(2.5,0,-10), Engine::Math::cQuaternion());
		helix->setGameObjectController(new Engine::WalkController());
		scene->addGameObjectToScene(helix);

		//Camera
		Engine::SharedPointer<Engine::Camera> mainCamera =
			Engine::Camera::CreateCamera("MainCamera",
				Engine::Math::cVector(0, 0, 3),
				Engine::Math::cQuaternion());
		mainCamera->activateCamera(true);
		mainCamera->setAspectRatio(static_cast<float>(800 / 600));
		mainCamera->setFieldOfView(60.0f);
		mainCamera->setCameraController(new Engine::CameraController());
		//mainCamera->setCameraController(new Engine::WalkController());
		scene->addCameraToScene(mainCamera);		
		scene->renderScene(true);
		
		while (!Engine::EngineCore::isWindowClosed(i_thisInstanceOfTheProgram))
			Engine::EngineCore::onNewFrame();
		
	}
	//_CrtDumpMemoryLeaks();
}