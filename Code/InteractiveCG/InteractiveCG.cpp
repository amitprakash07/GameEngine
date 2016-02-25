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


		//GameObjects		
		/*Engine::SharedPointer<Engine::MeshObject> floor =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/CheckerBoardPlane.mesh", 
				"ComputerGraphics/checkerBoardMaterial.mat");
		floor->setTransformation(Engine::Math::Vector3(0, -10, 0), Engine::Math::Quaternion());
		scene->addObjectToScene(floor);*/


		Engine::SharedPointer<Engine::MeshObject> sphere =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/DefaultSphere.mesh", 
				"ComputerGraphics/environmentMappingMaterial.mat", 
				Engine::Graphics::RGBAColor(1.0f,0.0f,0.0f,1.0f));
		sphere->setTransformation(Engine::Math::Vector3(0, 5, -10), Engine::Math::Quaternion());
		scene->addObjectToScene(sphere);

		/*Engine::SharedPointer<Engine::MeshObject> cube =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/DefaultCube.mesh", 
				"ComputerGraphics/environmentMappingMaterial.mat", 
				Engine::Graphics::RGBAColor(0.0f, 1.0f, 0.0f, 1.0f));
		cube->setTransformation(Engine::Math::Vector3(0, -5, -10), Engine::Math::Quaternion());
		scene->addObjectToScene(cube);*/


		Engine::Graphics::SkyBox::CreateSkyBox("ComputerGraphics/skyBox.mat");

		//Camera
		Engine::SharedPointer<Engine::Camera> mainCamera =
			Engine::Camera::CreateCamera("MainCamera",
				Engine::Math::Vector3(0.0f, 0.0f, 50.0f),
				Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(0),
					Engine::Math::Vector3(0, 15, 0)));

		

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
