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

		Engine::SharedPointer<Engine::Graphics::Effect> cubeEffect = cube->getEffect();

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

		Engine::Graphics::Data lightPosition;
		Engine::Graphics::Data  intensity;
		Engine::Graphics::Data lightColor;

		Engine::Math::Vector3 vecLightPosition = Engine::Math::Vector3(0, 19, 0);
		Engine::Math::Vector3 vecLightColor = Engine::Math::Vector3(1.0f,1.0f,1.0f);

		memcpy(&lightPosition.vec3, &vecLightPosition, 3 * sizeof(float));
		memcpy(&lightColor.vec3, &vecLightColor, 3 * sizeof(float));
		intensity.floatVal = 0.1f;


		mainLight->addLightParameter("lightPosition", Engine::Graphics::DataTypes::vec3,
			lightPosition);
		mainLight->addLightParameter("intensity", Engine::Graphics::DataTypes::glfloat,
			intensity);
		mainLight->addLightParameter("lightColor", Engine::Graphics::DataTypes::vec3,
			lightColor);
		mainLight->addLightToEffect(cubeEffect->getEffectName(), Engine::Graphics::Fragment);
		mainLight->setObjectController(new Application::WalkController());
		
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
