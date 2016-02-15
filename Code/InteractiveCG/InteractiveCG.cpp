#include "InteractiveCG.h"
#include "../Engine/Core/EngineCore/EngineCore.h"
#include <windows.h>
#include <fstream>
#include <crtdbg.h>
#include "../Engine/Core/EngineCore/Objects/Scene.h"
#include "../Engine/Core/Utilities/SharedPointer.h"
#include "../Engine/Core/EngineCore/Objects/MeshObject.h"
#include "../Engine/Core/EngineCore/ObjectController/WalkController.h"
#include "../Engine/Core/EngineCore/ObjectController/CameraController.h"
#include "../Engine/Core/EngineCore/Objects/Camera.h"
#include "../Engine/Core/Maths/Functions.h"





int WINAPI WinMain(HINSTANCE i_thisInstanceOfTheProgram, HINSTANCE, char* i_commandLineArguments, int i_initialWindowDisplayState)
{
	{
		//_CrtSetBreakAlloc(156);
		Engine::EngineCore::Initialize(i_thisInstanceOfTheProgram, i_initialWindowDisplayState);

		//Scene
		Engine::SharedPointer<Engine::Scene> scene = Engine::Scene::CreateNewScene("Scene_01");

		//GameObjects

		Engine::SharedPointer<Engine::MeshObject> BackWall =
			Engine::MeshObject::CreateMeshObject("InteractiveCG/AssignmentOnecubeOpaque/BackWall.mesh", "defaultPhongInFragment.mat");
		BackWall->setTransformation(Engine::Math::cVector(0, 0, 0), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(BackWall);

		Engine::SharedPointer<Engine::MeshObject> Cube =
			Engine::MeshObject::CreateMeshObject("InteractiveCG/AssignmentOnecubeOpaque/Cube.mesh", "defaultPhongInFragment.mat");
		Cube->setTransformation(Engine::Math::cVector(0, 0, 0), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(Cube);

		Engine::SharedPointer<Engine::MeshObject> FrontWall =
			Engine::MeshObject::CreateMeshObject("InteractiveCG/AssignmentOnecubeOpaque/FrontWall.mesh", "defaultPhongInFragment.mat");
		FrontWall->setTransformation(Engine::Math::cVector(0, 0, 0), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(FrontWall);

		Engine::SharedPointer<Engine::MeshObject> Ground =
			Engine::MeshObject::CreateMeshObject("InteractiveCG/AssignmentOnecubeOpaque/Ground.mesh", "defaultPhongInFragment.mat");
		Ground->setTransformation(Engine::Math::cVector(0, 0, 0), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(Ground);

		Engine::SharedPointer<Engine::MeshObject> LeftWall =
			Engine::MeshObject::CreateMeshObject("InteractiveCG/AssignmentOnecubeOpaque/LeftWall.mesh", "defaultPhongInFragment.mat");
		LeftWall->setTransformation(Engine::Math::cVector(0, 0, 0), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(LeftWall);

		Engine::SharedPointer<Engine::MeshObject> RightWall =
			Engine::MeshObject::CreateMeshObject("InteractiveCG/AssignmentOnecubeOpaque/RightWall.mesh", "defaultPhongInFragment.mat");
		RightWall->setTransformation(Engine::Math::cVector(0, 0, 0), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(RightWall);

		Engine::SharedPointer<Engine::MeshObject> Sphere =
			Engine::MeshObject::CreateMeshObject("InteractiveCG/AssignmentOnecubeOpaque/Sphere.mesh", "defaultPhongInFragment.mat");
		Sphere->setTransformation(Engine::Math::cVector(0, 0, 0), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(Sphere);

		Engine::SharedPointer<Engine::MeshObject> TopWall =
			Engine::MeshObject::CreateMeshObject("InteractiveCG/AssignmentOnecubeOpaque/TopWall.mesh", "defaultPhongInFragment.mat");
		TopWall->setTransformation(Engine::Math::cVector(0, 0, 0), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(TopWall);

		//Camera
		Engine::SharedPointer<Engine::Camera> mainCamera =
			Engine::Camera::CreateCamera("MainCamera",
				Engine::Math::cVector(0, 10, 150),
				Engine::Math::cQuaternion::getIdentityQuartenion());



		mainCamera->activateCamera(true);
		mainCamera->setAspectRatio(static_cast<float>(1600 / 900));
		mainCamera->setFieldOfView(60.0f);
		mainCamera->setFarPlane(1000.0f);
		mainCamera->setNearPlane(0.1f);
		mainCamera->setCameraController(new Engine::CameraController());
		scene->addCameraToScene(mainCamera);
		scene->renderScene(true);



		while (!Engine::EngineCore::isWindowClosed(i_thisInstanceOfTheProgram))
			Engine::EngineCore::onNewFrame();

	}
	//_CrtDumpMemoryLeaks();
}