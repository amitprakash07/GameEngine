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

		Engine::SharedPointer<Engine::Graphics::SkyBox> mFirstSkyBox = 
			Engine::Graphics::SkyBox::CreateSkyBox("ComputerGraphics/skyBoxMaterial.mat");

		mFirstSkyBox->setCurrentSkyBox();

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
		reflectivesphereWithBlend->setObjectController(new Application::ObjectRotateController());

		Engine::SharedPointer<Engine::Graphics::ReflectingObject> environmentMappingSphere =
			Engine::Graphics::ReflectingObject::CreateReflectingObject("ComputerGraphics/environmentMappingSphere.mesh",
				"ComputerGraphics/environmentMappingSphereMaterial.mat",0.1,1000.0f);
		environmentMappingSphere->setTransform(
			Engine::Math::Vector3(0, 0, 0), Engine::Math::Quaternion());
		environmentMappingSphere->setDynamicTextureSamplerName("g_TextureSampler");
		scene->addObjectToScene(environmentMappingSphere);
		//environmentMappingSphere->setObjectController(new Application::ObjectRotateController());
		


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
				Engine::Math::Vector3(0.532f, 48.008f, 152.492f), /*Engine::Math::Quaternion::getIdentityQuartenion());*/
				Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(0.0f),
					Engine::Math::Vector3(0.0f, 1.0f, 0.0f)));
				

		/*Engine::SharedPointer<Engine::Camera> mainCamera =
			Engine::Camera::CreateCamera("MainCamera",
				Engine::Math::Vector3(0, 5, -10),
				Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(0),
					Engine::Math::Vector3(0, 0, 0)));*/

		

		mainCamera->activateCamera(true);
		mainCamera->setAspectRatio(static_cast<float>(1600.0f / 900.0f));
		mainCamera->setFieldOfView(60.0f);
		mainCamera->setObjectController(new Application::WalkController());
		scene->addCameraToScene(mainCamera);


		while (!Engine::EngineCore::isWindowClosed(i_thisInstanceOfTheProgram))
			Engine::EngineCore::onNewFrame();

	}
	//_CrtDumpMemoryLeaks();
}
