#include <windows.h>
#include <fstream>
#include <crtdbg.h>
#include "../Engine/Core/EngineCore/Objects/Scene.h"
#include "../Engine/Core/Utilities/SharedPointer.h"
#include "../Engine/Core/EngineCore/Objects/MeshObject.h"
#include "../Engine/Core/EngineCore/Objects/Camera.h"
#include "../Engine/Core/Maths/Functions.h"
#include "../Engine/Windows/WindowsFunctions.h"
#include "../Engine/Core/EngineCore/EngineCore.h"
#include "ObjectController/WalkController.h"
#include "ObjectController/LightController.h"
#include "../Engine/Graphics/SkyBox.h"
#include "ObjectController/RotateObject.h"



int WINAPI WinMain(HINSTANCE i_thisInstanceOfTheProgram, HINSTANCE, char* i_commandLineArguments, int i_initialWindowDisplayState)
{
	{
		//_CrtSetBreakAlloc(156);
		Engine::EngineCore::Initialize(i_thisInstanceOfTheProgram, i_initialWindowDisplayState);

		//Scene
		Engine::SharedPointer<Engine::Scene> scene = Engine::Scene::CreateNewScene("Scene_01");
		scene->renderScene(true);		

		//GameObjects
		//floor
		Engine::SharedPointer<Engine::MeshObject> floor =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/floor.mesh", 
				"ComputerGraphics/floorMaterial.mat");
		floor->setTransform(Engine::Math::Vector3(0, -2.5, 0), Engine::Math::Quaternion());
		scene->addObjectToScene(floor);

		//ceiling
		Engine::SharedPointer<Engine::MeshObject> ceiling =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/floor.mesh",
				"ComputerGraphics/ceilingMaterial.mat");
		ceiling->setTransform(Engine::Math::Vector3(0, 7, 0), 
			Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(180.0f),
				Engine::Math::Vector3(1.0f, 0.0f, 0.0f)));
		scene->addObjectToScene(ceiling);


		//rightWall
		Engine::SharedPointer<Engine::MeshObject> rightWall =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/floor.mesh",
				"ComputerGraphics/rightWallMaterial.mat");
		rightWall->setTransform(Engine::Math::Vector3(5, 2, 0), 
			Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(90),
				Engine::Math::Vector3(0.0f, 0.0f, -1.0f)));
		scene->addObjectToScene(rightWall);

		//leftWall
		Engine::SharedPointer<Engine::MeshObject> leftWall =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/floor.mesh",
				"ComputerGraphics/leftWallMaterial.mat");
		leftWall->setTransform(Engine::Math::Vector3(-5, 2, 0), 
			Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(-90.0f),
				Engine::Math::Vector3(0.0f, 0.0f, -1.0f)));
		scene->addObjectToScene(leftWall);

		//frontWall
		Engine::SharedPointer<Engine::MeshObject> frontWall =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/floor.mesh",
				"ComputerGraphics/frontWallMaterial.mat");
		frontWall->setTransform(Engine::Math::Vector3(0, 2, 6), 
			Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(90.0f),
				Engine::Math::Vector3(1.0f, 0.0f, 0.0f)));
		scene->addObjectToScene(frontWall);


		//backWall
		Engine::SharedPointer<Engine::MeshObject> backWall =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/floor.mesh",
				"ComputerGraphics/backWallMaterial.mat");
		backWall->setTransform(Engine::Math::Vector3(0, 2, -4.5), 
			Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(-90.0f),
				Engine::Math::Vector3(1.0f, 0.0f, 0.0f)));
		scene->addObjectToScene(backWall);		

		//cube
		Engine::SharedPointer<Engine::MeshObject> cube =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/Cube.mesh",
				"ComputerGraphics/cubeMaterial.mat");
		cube->setTransform(Engine::Math::Vector3(0,-2,0), Engine::Math::Quaternion());
		scene->addObjectToScene(cube);

		////teapot one
		//Engine::SharedPointer<Engine::MeshObject> teapot1_lid =
		//	Engine::MeshObject::CreateMeshObject("ComputerGraphics/teapot1_lid.mesh",
		//		"ComputerGraphics/backWallMaterial.mat");
		//teapot1_lid->setTransform(Engine::Math::Vector3(0, 0, 0), Engine::Math::Quaternion());
		//scene->addObjectToScene(teapot1_lid);

		//Engine::SharedPointer<Engine::MeshObject> teapot1_handle =
		//	Engine::MeshObject::CreateMeshObject("ComputerGraphics/teapot1_handle.mesh",
		//		"ComputerGraphics/backWallMaterial.mat");
		//teapot1_handle->setTransform(Engine::Math::Vector3(0, 0, 0), Engine::Math::Quaternion());
		//scene->addObjectToScene(teapot1_handle);

		//Engine::SharedPointer<Engine::MeshObject> teapot1_circum =
		//	Engine::MeshObject::CreateMeshObject("ComputerGraphics/teapot1_circum.mesh",
		//		"ComputerGraphics/backWallMaterial.mat");
		//teapot1_circum->setTransform(Engine::Math::Vector3(0, 0, 0), Engine::Math::Quaternion());
		//scene->addObjectToScene(teapot1_circum);

		////teapot two
		//Engine::SharedPointer<Engine::MeshObject> teapot2_circum =
		//	Engine::MeshObject::CreateMeshObject("ComputerGraphics/teapot2_circum.mesh",
		//		"ComputerGraphics/backWallMaterial.mat");
		//teapot2_circum->setTransform(Engine::Math::Vector3(0, 0, 0), Engine::Math::Quaternion());
		//scene->addObjectToScene(teapot2_circum);

		//Engine::SharedPointer<Engine::MeshObject> teapot2_lid =
		//	Engine::MeshObject::CreateMeshObject("ComputerGraphics/teapot2_lid.mesh",
		//		"ComputerGraphics/backWallMaterial.mat");
		//teapot2_lid->setTransform(Engine::Math::Vector3(0, 0, 0), Engine::Math::Quaternion());
		//scene->addObjectToScene(teapot2_lid);

		//Engine::SharedPointer<Engine::MeshObject> teapot2_handle01 =
		//	Engine::MeshObject::CreateMeshObject("ComputerGraphics/teapot2_handle01.mesh",
		//		"ComputerGraphics/backWallMaterial.mat");
		//teapot2_handle01->setTransform(Engine::Math::Vector3(0, 0, 0), Engine::Math::Quaternion());
		//scene->addObjectToScene(teapot2_handle01);

		//Engine::SharedPointer<Engine::MeshObject> teapot2_handle02 =
		//	Engine::MeshObject::CreateMeshObject("ComputerGraphics/teapot2_handle02.mesh",
		//		"ComputerGraphics/backWallMaterial.mat");
		//teapot2_handle02->setTransform(Engine::Math::Vector3(0, 0, 0), Engine::Math::Quaternion());
		//scene->addObjectToScene(teapot2_handle02);

		////tray
		//Engine::SharedPointer<Engine::MeshObject> tray =
		//	Engine::MeshObject::CreateMeshObject("ComputerGraphics/tray.mesh",
		//		"ComputerGraphics/backWallMaterial.mat");
		//tray->setTransform(Engine::Math::Vector3(0, 0, 0), Engine::Math::Quaternion());
		//scene->addObjectToScene(tray);

		////utah teapot
		Engine::SharedPointer<Engine::MeshObject> utahTeapot =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/utahTeapot.mesh",
				"ComputerGraphics/utahTeapotMaterial.mat");
		utahTeapot->setTransform(Engine::Math::Vector3(0, -2, 0), Engine::Math::Quaternion());
		scene->addObjectToScene(utahTeapot);

		//konvinceTeapot
		/*Engine::SharedPointer<Engine::MeshObject> konvinceTeapot =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/konvinceTeapot.mesh",
				"ComputerGraphics/konvinceTeapotMaterial.mat");
		konvinceTeapot->setTransform(Engine::Math::Vector3(0, 0.5, 0), Engine::Math::Quaternion());
		scene->addObjectToScene(konvinceTeapot);*/
		
		//Proxy Light
		Engine::SharedPointer<Engine::MeshObject> proxyLightSphere =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/proxyLightSphere.mesh",
				"ComputerGraphics/proxyLightSphereMaterial.mat");
		proxyLightSphere->setTransform(Engine::Math::Vector3(0, 6, 0), Engine::Math::Quaternion());
		scene->addObjectToScene(proxyLightSphere);
		proxyLightSphere->setObjectController(new Application::LightController());

		Engine::SharedPointer<Engine::Camera> mainCamera =
			Engine::Camera::CreateCamera("MainCamera",
				Engine::Math::Vector3(0.0f, 3.0f, 12.0f), /*Engine::Math::Quaternion::getIdentityQuartenion());*/
				Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(0.0f),
					Engine::Math::Vector3(0.0f, 0.5f, 0.0f)));
		

		mainCamera->activateCamera(true);
		mainCamera->setAspectRatio(static_cast<float>(1600.0f / 900.0f));
		mainCamera->setFieldOfView(60.0f);
		//mainCamera->setObjectController(new Application::WalkController());
		scene->addCameraToScene(mainCamera);


		while (!Engine::EngineCore::isWindowClosed(i_thisInstanceOfTheProgram))
			Engine::EngineCore::onNewFrame();

	}
	//_CrtDumpMemoryLeaks();
}
