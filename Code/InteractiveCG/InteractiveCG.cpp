#include <windows.h>
#include <fstream>
#include <crtdbg.h>
#include "../Engine/Core/EngineCore/Objects/Scene.h"
#include "../Engine/Core/Utilities/SharedPointer.h"
#include "../Engine/Core/EngineCore/Objects/MeshObject.h"
#include "../Engine/Core/EngineCore/ObjectController/CameraController.h"
#include "../Engine/Core/EngineCore/Objects/Camera.h"
#include "../Engine/Core/Maths/Functions.h"
#include "../Engine/Windows/WindowsFunctions.h"
#include "../Engine/Core/EngineCore/EngineCore.h"


int WINAPI WinMain(HINSTANCE i_thisInstanceOfTheProgram, HINSTANCE, char* i_commandLineArguments, int i_initialWindowDisplayState)
{
	{
		//_CrtSetBreakAlloc(156);
		Engine::EngineCore::Initialize(i_thisInstanceOfTheProgram, i_initialWindowDisplayState);

		//Scene
		Engine::SharedPointer<Engine::Scene> scene = Engine::Scene::CreateNewScene("Scene_01");
		scene->renderScene(true);


		//GameObjects		
		Engine::SharedPointer<Engine::MeshObject> ceiling =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/CubeForCubeMap.mesh", "ComputerGraphics/cubeMap.mat");
		ceiling->setTransformation(Engine::Math::cVector(0, 0, 0), Engine::Math::cQuaternion());
		scene->addObjectToScene(ceiling);		


		//Camera
		Engine::SharedPointer<Engine::Camera> mainCamera =
			Engine::Camera::CreateCamera("MainCamera",
				Engine::Math::cVector(-53.258, -108.953, 1043.751),
				Engine::Math::cQuaternion(Engine::Math::ConvertDegreesToRadians(0),
					Engine::Math::cVector(0, 1, 0)));

		

		mainCamera->activateCamera(true);
		mainCamera->setAspectRatio(static_cast<float>(1600.0f / 900.0f));
		mainCamera->setFieldOfView(60.0f);
		mainCamera->setCameraController(new Engine::CameraController());
		scene->addCameraToScene(mainCamera);


		while (!Engine::EngineCore::isWindowClosed(i_thisInstanceOfTheProgram))
			Engine::EngineCore::onNewFrame();

	}
	//_CrtDumpMemoryLeaks();
}