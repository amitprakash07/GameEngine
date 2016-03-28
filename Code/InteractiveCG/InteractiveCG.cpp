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
#include "../Engine/Graphics/Plane.h"
#include "../Engine/Graphics/SkyBox.h"
#include "../Engine/Graphics/SkyBox.h"
#include "ObjectController/RotateObject.h"
#include "ObjectController/FilterChanger.h"
#include "../Engine/Graphics/Light.h"



int WINAPI WinMain(HINSTANCE i_thisInstanceOfTheProgram, HINSTANCE, char* i_commandLineArguments, int i_initialWindowDisplayState)
{
	{
		//_CrtSetBreakAlloc(156);
		Engine::EngineCore::Initialize(i_thisInstanceOfTheProgram, i_initialWindowDisplayState);

		//Scene
		Engine::SharedPointer<Engine::Scene> scene = Engine::Scene::CreateNewScene("Scene_01");
		scene->renderScene(true);

		//Engine::SharedPointer<Engine::Graphics::SkyBox> mFirstSkyBox =
		//	Engine::Graphics::SkyBox::CreateSkyBox("ComputerGraphics/skyBoxMaterial.mat");

		//mFirstSkyBox->setCurrentSkyBox();

		//Engine::SharedPointer<Engine::Graphics::SkyBox> mSecondSkyBox =
		//	Engine::Graphics::SkyBox::CreateSkyBox("ComputerGraphics/skyBoxMaterialTwo.mat");


		//Engine::SharedPointer<Engine::Graphics::SkyBox> mThirdSkyBox =
		//	Engine::Graphics::SkyBox::CreateSkyBox("ComputerGraphics/skyBoxMaterialThree.mat");

		//Engine::SharedPointer<Engine::MeshObject> floor =
		//	Engine::MeshObject::CreateMeshObject("ComputerGraphics/floor.mesh",
		//		"ComputerGraphics/floorMaterial.mat");
		//floor->setTransform(Engine::Math::Vector3(0, 0.2, -4), Engine::Math::Quaternion());
		//scene->addObjectToScene(floor);
		//floor->setObjectController(new Application::TextureFilterChanger());

		//Engine::SharedPointer<Engine::MeshObject> reflectivesphereWithBlend =
		//	Engine::MeshObject::CreateMeshObject("ComputerGraphics/reflectiveSphere.mesh",
		//		"ComputerGraphics/reflectiveSphereMaterial.mat");
		//reflectivesphereWithBlend->setTransform(
		//	Engine::Math::Vector3(0, 2.5, -4), Engine::Math::Quaternion());
		//scene->addObjectToScene(reflectivesphereWithBlend);
		//reflectivesphereWithBlend->setObjectController(new Application::ObjectRotateController());
		////reflectivesphereWithBlend->setObjectController(new Application::WalkController());

		//Engine::SharedPointer<Engine::Graphics::ReflectingObject> environmentMappingSphere =
		//	Engine::Graphics::ReflectingObject::CreateReflectingObject("ComputerGraphics/environmentMappingSphere.mesh",
		//		"ComputerGraphics/environmentMappingSphereMaterial.mat", 0.1, 1000.0f);
		//environmentMappingSphere->setTransform(
		//	Engine::Math::Vector3(-3, 2, -4), Engine::Math::Quaternion());
		//environmentMappingSphere->setDynamicTextureSamplerName("g_TextureSampler");
		//scene->addObjectToScene(environmentMappingSphere);
		////environmentMappingSphere->setObjectController(new Application::ObjectRotateController());

		//Engine::SharedPointer<Engine::MeshObject> cube =
		//	Engine::MeshObject::CreateMeshObject("ComputerGraphics/Cube.mesh",
		//		"ComputerGraphics/cubeMaterial.mat");
		//cube->setTransform(Engine::Math::Vector3(0, 1, -4), Engine::Math::Quaternion());
		//scene->addObjectToScene(cube);
		//cube->setObjectController(new Application::ObjectRotateController());

		/*Engine::SharedPointer<Engine::Graphics::Sprite> logoSprite =
		Engine::Graphics::Sprite::CreateSprite("EAElogo",
		"Game/spriteMaterial.mat", 0, 500, 0, 500, Engine::Graphics::VIEWPORT_COORDINATE);
		scene->addObjectToScene(logoSprite);*/


		/*Engine::SharedPointer<Engine::Graphics::Sprite> numberSprite =
		Engine::Graphics::Sprite::CreateSprite("numbers",
		"Game/numbersMaterial.mat", 1540, 1590, 890, 840, Engine::Graphics::VIEWPORT_COORDINATE);
		numberSprite->sliceSprite(1, 10);
		numberSprite->setCellToRender(2);
		scene->addObjectToScene(numberSprite);*/
		//numberSprite->setObjectController(new Application::WalkController());

		/*Engine::SharedPointer<Engine::Camera> mainCamera =
			Engine::Camera::CreateCamera("MainCamera",
				Engine::Math::Vector3(0.0f, 3.0f, 10.0f),
				Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(0.0f),
					Engine::Math::Vector3(0.0f, 0.0f, 0.0f)));*/

		//GameObjects
		//floor
		Engine::SharedPointer<Engine::Graphics::Plane> floor =
			Engine::Graphics::Plane::CreatePlane("ComputerGraphics/floorMaterial.mat");
		floor->setTransform(Engine::Math::Vector3(0, 0, 0), Engine::Math::Quaternion());
		floor->setScale(30.0f, 20.0f, 20.0f);
		scene->addObjectToScene(floor);;

		//ceiling
		Engine::SharedPointer<Engine::Graphics::Plane> ceiling =
			Engine::Graphics::Plane::CreatePlane("ComputerGraphics/ceilingMaterial.mat");
		ceiling->setTransform(Engine::Math::Vector3(0, 20, 0), 
			Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(180.0f),
				Engine::Math::Vector3(1.0f, 0.0f, 0.0f)));
		ceiling->setScale(30.0f, 20.0f, 20.0f);
		scene->addObjectToScene(ceiling);

		Engine::Math::Vector3 normal = ceiling->getNormal();


		//rightWall
		Engine::SharedPointer<Engine::Graphics::Plane> rightWall =
			Engine::Graphics::Plane::CreatePlane("ComputerGraphics/rightWallMaterial.mat");
		rightWall->setTransform(Engine::Math::Vector3(15, 10, 0), 
			Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(90),
				Engine::Math::Vector3(0.0f, 0.0f, -1.0f)));
		rightWall->setScale(20.0f, 20.0f, 20.0f);
		scene->addObjectToScene(rightWall);

		//leftWall
		Engine::SharedPointer<Engine::Graphics::Plane> leftWall =
			Engine::Graphics::Plane::CreatePlane("ComputerGraphics/leftWallMaterial.mat");
		leftWall->setTransform(Engine::Math::Vector3(-15, 10, 0), 
			Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(-90.0f),
				Engine::Math::Vector3(0.0f, 0.0f, -1.0f)));
		leftWall->setScale(20.0f, 20.0f, 20.0f);
		scene->addObjectToScene(leftWall);

		//frontWall
		Engine::SharedPointer<Engine::Graphics::Plane> frontWall =
			Engine::Graphics::Plane::CreatePlane("ComputerGraphics/frontWallMaterial.mat");
		frontWall->setTransform(Engine::Math::Vector3(0, 10, 20), 
			Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(90.0f),
				Engine::Math::Vector3(1.0f, 0.0f, 0.0f)));
		frontWall->setScale(20.0f, 20.0f, 20.0f);
		scene->addObjectToScene(frontWall);


		//backWall
		Engine::SharedPointer<Engine::Graphics::Plane> backWall =
			Engine::Graphics::Plane::CreatePlane("ComputerGraphics/backWallMaterial.mat");
		backWall->setTransform(Engine::Math::Vector3(0, 10, -10), 
			Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(-90.0f),
				Engine::Math::Vector3(1.0f, 0.0f, 0.0f)));
		backWall->setScale(30.0f, 20.0f, 20.0f);
		scene->addObjectToScene(backWall);		

		//cube
		Engine::SharedPointer<Engine::MeshObject> cube =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/Cube.mesh",
				"ComputerGraphics/cubeMaterial.mat");
		cube->setTransform(Engine::Math::Vector3(-2,2,0), Engine::Math::Quaternion());
		cube->setScale(4,4,4);
		scene->addObjectToScene(cube);

		//utah teapot
		Engine::SharedPointer<Engine::MeshObject> utahTeapot =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/utahTeapot.mesh",
				"ComputerGraphics/utahTeapotMaterial.mat");
		utahTeapot->setTransform(Engine::Math::Vector3(0, 3.5, 0), Engine::Math::Quaternion());
		scene->addObjectToScene(utahTeapot);

		
		//Proxy Light
		Engine::SharedPointer<Engine::MeshObject> proxyLightSphere =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/proxyLightSphere.mesh",
				"ComputerGraphics/proxyLightSphereMaterial.mat");
		proxyLightSphere->setTransform(Engine::Math::Vector3(0, 18, 0), Engine::Math::Quaternion());
		scene->addObjectToScene(proxyLightSphere);
		proxyLightSphere->setObjectController(new Application::LightController());


		Engine::SharedPointer<Engine::Graphics::Light> mainLight
			= Engine::Graphics::Light::createLight("mainLight", Engine::Graphics::LightType::Point);
		mainLight->setIntensity(1.0f);
		mainLight->setColor(Engine::Math::Vector3(1.0f, 0.0f, 0.0f));
		mainLight->setTransform(Engine::Math::Vector3(0, 19, 0),
			Engine::Math::Quaternion());
		scene->addLightToScene(mainLight);

		
		Engine::Graphics::UniformValues lightUniform;
		lightUniform.floatArray = mainLight->getTransform().getPosition().toFloatArray();
		Engine::SharedPointer<Engine::Graphics::Effect> utahTeapotEffect = utahTeapot->getEffect();
		
		utahTeapotEffect->addUniform("lightPosition", Engine::Graphics::Vertex, Engine::Graphics::FloatArray,
			3, lightUniform);
		
		Engine::Graphics::UniformValues lightIntensity;
		lightIntensity.floatValue = mainLight->
		utahTeapotEffect->addUniform("lightIntensity", Engine::Graphics::Vertex, Engine::Graphics::Float,
			3, lightUniform);
		utahTeapotEffect->addUniform("lightPosition", Engine::Graphics::Vertex, Engine::Graphics::FloatArray,
			3, lightUniform);



		Engine::SharedPointer<Engine::Camera> mainCamera =
			Engine::Camera::CreateCamera("MainCamera",
				Engine::Math::Vector3(0.0f, 10.0f, 25.0f),
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
