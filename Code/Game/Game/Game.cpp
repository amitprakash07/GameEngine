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
#include "../../Engine/Core/Maths/Functions.h"





int WINAPI WinMain(HINSTANCE i_thisInstanceOfTheProgram, HINSTANCE, char* i_commandLineArguments, int i_initialWindowDisplayState)
{
	{
		//_CrtSetBreakAlloc(156);
		Engine::EngineCore::Initialize(i_thisInstanceOfTheProgram, i_initialWindowDisplayState);

		//Scene
		Engine::SharedPointer<Engine::Scene> scene = Engine::Scene::CreateNewScene("Scene_01");

		//GameObjects

		/*Engine::SharedPointer<Engine::GameObject> ceiling =
		Engine::GameObject::CreateGameObject("Arena/ceilingMaterialMesh.mesh", "Arena/ceilingMaterial.mat");
		ceiling->setTransformation(Engine::Math::cVector(0, 0, 0), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(ceiling);

		Engine::SharedPointer<Engine::GameObject> cementMatObject =
		Engine::GameObject::CreateGameObject("Arena/cementMaterialMesh.mesh", "Arena/cementMaterial.mat");
		cementMatObject->setTransformation(Engine::Math::cVector(0, 0, 0), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(cementMatObject);

		Engine::SharedPointer<Engine::GameObject> floorMatObject =
		Engine::GameObject::CreateGameObject("Arena/FloorMaterialMesh.mesh", "Arena/FloorMaterial.mat");
		floorMatObject->setTransformation(Engine::Math::cVector(0, 0, 0), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(floorMatObject);

		Engine::SharedPointer<Engine::GameObject> lambertTwoMatObjects =
		Engine::GameObject::CreateGameObject("Arena/LambertTwoMaterialMesh.mesh", "Arena/LambertTwoMaterial.mat");
		lambertTwoMatObjects->setTransformation(Engine::Math::cVector(0, 0, 0), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(lambertTwoMatObjects);

		Engine::SharedPointer<Engine::GameObject> metals =
		Engine::GameObject::CreateGameObject("Arena/MetalMaterialMesh.mesh", "Arena/MetalMaterial.mat");
		metals->setTransformation(Engine::Math::cVector(0, 0, 0), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(metals);

		Engine::SharedPointer<Engine::GameObject> railing =
		Engine::GameObject::CreateGameObject("Arena/railingMaterialMesh.mesh", "Arena/railingMaterial.mat");
		railing->setTransformation(Engine::Math::cVector(0, 0, 0), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(railing);

		Engine::SharedPointer<Engine::GameObject> walls =
		Engine::GameObject::CreateGameObject("Arena/wallsMaterialMesh.mesh", "Arena/wallsMaterial.mat");
		walls->setTransformation(Engine::Math::cVector(0, 0, 0), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(walls);*/


		Engine::SharedPointer<Engine::MeshObject> sphere =
			Engine::MeshObject::CreateMeshObject("Sphere.mesh", "default.mat");
		sphere->setTransformation(Engine::Math::cVector(0, 0, 0), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(sphere);




		//Camera
		/*Engine::SharedPointer<Engine::Camera> mainCamera =
		Engine::Camera::CreateCamera("MainCamera",
		Engine::Math::cVector(79.902, -84.281, 1912.918),
		Engine::Math::cQuaternion(Engine::Math::ConvertDegreesToRadians(0),
		Engine::Math::cVector(0,1,0)));*/

		Engine::SharedPointer<Engine::Camera> mainCamera =
			Engine::Camera::CreateCamera("MainCamera",
				Engine::Math::cVector(0, 0, 5),
				Engine::Math::cQuaternion(Engine::Math::ConvertDegreesToRadians(0),
					Engine::Math::cVector(0, 1, 0)));

		mainCamera->activateCamera(true);
		mainCamera->setAspectRatio(static_cast<float>(1600 / 900));
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