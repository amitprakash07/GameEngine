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
#include "ObjectController/CameraController.h"
#include "../Engine/Graphics/SkyBox.h"


int WINAPI WinMain(HINSTANCE i_thisInstanceOfTheProgram, HINSTANCE, char* i_commandLineArguments, int i_initialWindowDisplayState)
{
	{
		//_CrtSetBreakAlloc(156);
		Engine::EngineCore::Initialize(i_thisInstanceOfTheProgram, i_initialWindowDisplayState);

		//Scene
		Engine::SharedPointer<Engine::Scene> scene = Engine::Scene::CreateNewScene("Scene_01");
		scene->renderScene(true);

		Engine::Graphics::SkyBox::CreateSkyBox("ComputerGraphics/skyBoxMaterial.mat");

		//GameObjects		
		Engine::SharedPointer<Engine::MeshObject> floor =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/floor.mesh", 
				"ComputerGraphics/floorMaterial.mat");
		floor->setTransform(Engine::Math::Vector3(0, 0, 0), Engine::Math::Quaternion());
		scene->addObjectToScene(floor);


		Engine::SharedPointer<Engine::MeshObject> reflectivesphereWithBlend =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/reflectiveSphere.mesh", 
				"ComputerGraphics/reflectiveSphereMaterial.mat");
		reflectivesphereWithBlend->setTransform(
			Engine::Math::Vector3(0, 5, -10), Engine::Math::Quaternion());
		scene->addObjectToScene(reflectivesphereWithBlend);


		Engine::SharedPointer<Engine::MeshObject> environmentMappingSphere =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/environmentMappingSphere.mesh",
				"ComputerGraphics/environmentMappingSphereMaterial.mat");
		environmentMappingSphere->setTransform(
			Engine::Math::Vector3(0, 5, -10), Engine::Math::Quaternion());
		scene->addObjectToScene(environmentMappingSphere);


		Engine::SharedPointer<Engine::MeshObject> cube =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/Cube.mesh",
				"ComputerGraphics/cubeMaterial.mat");
		cube->setTransform(Engine::Math::Vector3(0, 1, -10), Engine::Math::Quaternion());
		scene->addObjectToScene(cube);


		

		//Camera
		/*Engine::SharedPointer<Engine::Camera> mainCamera =
			Engine::Camera::CreateCamera("MainCamera",
				Engine::Math::Vector3(0.0f, 0.0f, 0.0f),
				Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(0),
					Engine::Math::Vector3(0, 0, 0)));*/

		Engine::SharedPointer<Engine::Camera> mainCamera =
			Engine::Camera::CreateCamera("MainCamera",
				Engine::Math::Vector3(0.532f, 48.008f, 152.492f),
				Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(0),
					Engine::Math::Vector3(0, 0, 0)));

		/*Engine::SharedPointer<Engine::MeshObject> ceiling =
			Engine::MeshObject::CreateMeshObject("Game/Arena/ceilingMaterialMesh.mesh", "Game/Arena/ceilingMaterial.mat");
		ceiling->setTransform(Engine::Math::Vector3(0, 0, 0), Engine::Math::Quaternion());
		scene->addObjectToScene(ceiling);

		Engine::SharedPointer<Engine::MeshObject> cementMatObject =
			Engine::MeshObject::CreateMeshObject("Game/Arena/cementMaterialMesh.mesh", "Game/Arena/cementMaterial.mat");
		cementMatObject->setTransform(Engine::Math::Vector3(0, 0, 0), Engine::Math::Quaternion());
		scene->addObjectToScene(cementMatObject);

		Engine::SharedPointer<Engine::MeshObject> floorMatObject =
			Engine::MeshObject::CreateMeshObject("Game/Arena/FloorMaterialMesh.mesh", "Game/Arena/floorMaterial.mat");
		floorMatObject->setTransform(Engine::Math::Vector3(0, 0, 0), Engine::Math::Quaternion());
		scene->addObjectToScene(floorMatObject);

		Engine::SharedPointer<Engine::MeshObject> lambertTwoMatObjects =
			Engine::MeshObject::CreateMeshObject("Game/Arena/LambertTwoMaterialMesh.mesh", "Game/Arena/lambertTwoMaterial.mat");
		lambertTwoMatObjects->setTransform(Engine::Math::Vector3(0, 0, 0), Engine::Math::Quaternion());
		scene->addObjectToScene(lambertTwoMatObjects);

		Engine::SharedPointer<Engine::MeshObject> metals =
			Engine::MeshObject::CreateMeshObject("Game/Arena/MetalMaterialMesh.mesh", "Game/Arena/metalMaterial.mat");
		metals->setTransform(Engine::Math::Vector3(0, 0, 0), Engine::Math::Quaternion());
		scene->addObjectToScene(metals);

		Engine::SharedPointer<Engine::MeshObject> railing =
			Engine::MeshObject::CreateMeshObject("Game/Arena/railingMaterialMesh.mesh", "Game/Arena/railingMaterial.mat");
		railing->setTransform(Engine::Math::Vector3(0, 0, 0), Engine::Math::Quaternion());
		scene->addObjectToScene(railing);

		Engine::SharedPointer<Engine::MeshObject> walls =
			Engine::MeshObject::CreateMeshObject("Game/Arena/wallsMaterialMesh.mesh", "Game/Arena/wallsMaterial.mat");
		walls->setTransform(Engine::Math::Vector3(0, 0, 0), Engine::Math::Quaternion());
		scene->addObjectToScene(walls);


		Engine::SharedPointer<Engine::Camera> mainCamera =
			Engine::Camera::CreateCamera("MainCamera",
				Engine::Math::Vector3(-53.258, -108.953, 1043.751),
				Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(0),
					Engine::Math::Vector3(0, 1, 0)));*/

		mainCamera->activateCamera(true);
		mainCamera->setAspectRatio(static_cast<float>(1600.0f / 900.0f));
		mainCamera->setFieldOfView(60.0f);
		mainCamera->setCameraController(new Application::CameraController());
		scene->addCameraToScene(mainCamera);


		while (!Engine::EngineCore::isWindowClosed(i_thisInstanceOfTheProgram))
			Engine::EngineCore::onNewFrame();

	}
	//_CrtDumpMemoryLeaks();
}
