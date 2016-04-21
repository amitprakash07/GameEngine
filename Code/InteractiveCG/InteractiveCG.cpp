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
#include "ObjectController/BumpToToon.h"



int WINAPI WinMain(HINSTANCE i_thisInstanceOfTheProgram, HINSTANCE, 
	char* i_commandLineArguments, 
	int i_initialWindowDisplayState)
{
	{
		//_CrtSetBreakAlloc(156);
		Engine::EngineCore::Initialize(i_thisInstanceOfTheProgram, i_initialWindowDisplayState);

		//Scene
		Engine::SharedPointer<Engine::Scene> scene = Engine::Scene::CreateNewScene("Scene_01");
		scene->renderScene(true);

		
		//GameObjects	

		/*Engine::SharedPointer<Engine::Graphics::ReflectingObject> environmentMappingSphere =
			Engine::Graphics::ReflectingObject::CreateReflectingObject("ComputerGraphics/sphere.mesh",
				"ComputerGraphics/environmentMappingSphereMaterial.mat", 0.1, 1000.0f);
		environmentMappingSphere->setTransform(
			Engine::Math::Vector3(-5, 8, 0), Engine::Math::Quaternion());
		environmentMappingSphere->setDynamicTextureSamplerName("g_TextureSampler");
		environmentMappingSphere->setScale(3, 3, 3);
		scene->addObjectToScene(environmentMappingSphere);
		Engine::SharedPointer<Engine::Graphics::Effect> environmentMappingSphereEffect = 
			Engine::Graphics::Effect::getEffect(
				Engine::Graphics::Material::getMaterial(environmentMappingSphere->getMaterialName().c_str())->getEffectName());*/
		//environmentMappingSphere->setObjectController(new Application::ObjectRotateController());

		//floor
		Engine::SharedPointer<Engine::MeshObject> floor =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/Plane.mesh",
				"ComputerGraphics/floorMaterial.mat");
		floor->setTransform(Engine::Math::Vector3(0, 0, 0), Engine::Math::Quaternion());
		floor->setScale(30.0f, 20.0f, 20.0f);
		scene->addObjectToScene(floor);

		//ceiling
		Engine::SharedPointer<Engine::MeshObject> ceiling =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/Plane.mesh",
				"ComputerGraphics/ceilingMaterial.mat");
		ceiling->setTransform(Engine::Math::Vector3(0, 20, 0),
			Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(180.0f),
				Engine::Math::Vector3(1.0f, 0.0f, 0.0f)));
		ceiling->setScale(30.0f, 20.0f, 20.0f);
		scene->addObjectToScene(ceiling);

		
		//rightWall
		Engine::SharedPointer<Engine::MeshObject> rightWall =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/Plane.mesh",
				"ComputerGraphics/rightWallMaterial.mat");
		rightWall->setTransform(Engine::Math::Vector3(15, 10, 0),
			Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(90),
				Engine::Math::Vector3(0.0f, 0.0f, -1.0f)));
		rightWall->setScale(20.0f, 20.0f, 20.0f);
		scene->addObjectToScene(rightWall);

		//leftWall
		Engine::SharedPointer<Engine::MeshObject> leftWall =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/Plane.mesh", 
				"ComputerGraphics/leftWallMaterial.mat");
		leftWall->setTransform(Engine::Math::Vector3(-15, 10, 0),
			Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(-90.0f),
				Engine::Math::Vector3(0.0f, 0.0f, -1.0f)));
		leftWall->setScale(20.0f, 20.0f, 20.0f);
		scene->addObjectToScene(leftWall);

		//frontWall
		Engine::SharedPointer<Engine::MeshObject> frontWall =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/Plane.mesh", 
				"ComputerGraphics/frontWallMaterial.mat");
		frontWall->setTransform(Engine::Math::Vector3(0, 10, 20),
			Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(90.0f),
				Engine::Math::Vector3(1.0f, 0.0f, 0.0f)));
		frontWall->setScale(20.0f, 20.0f, 20.0f);
		scene->addObjectToScene(frontWall);


		//backWall
		Engine::SharedPointer<Engine::MeshObject> backWall =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/Plane.mesh", 
				"ComputerGraphics/backWallMaterial.mat");
		backWall->setTransform(Engine::Math::Vector3(0, 10, -10),
			Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(-90.0f),
				Engine::Math::Vector3(1.0f, 0.0f, 0.0f)));
		backWall->setScale(30.0f, 20.0f, 20.0f);
		scene->addObjectToScene(backWall);


		//Sphere
		Engine::SharedPointer<Engine::MeshObject> sphereWithToon =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/sphere.mesh",
				"ComputerGraphics/sphereToonMaterial.mat");
		sphereWithToon->setTransform(Engine::Math::Vector3(5, 8, 0), Engine::Math::Quaternion());
		sphereWithToon->setScale(3, 3, 3);
		scene->addObjectToScene(sphereWithToon);
		sphereWithToon->setRenderable(false);
		sphereWithToon->setObjectController(new Application::BumpToToon());


		Engine::SharedPointer<Engine::MeshObject> sphereWithBump =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/sphere.mesh",
				"ComputerGraphics/sphereMaterial.mat");
		sphereWithBump->setTransform(Engine::Math::Vector3(5, 8, 0), Engine::Math::Quaternion());
		sphereWithBump->setScale(3, 3, 3);
		scene->addObjectToScene(sphereWithBump);
		//sphereWithBump->setRenderable(false);
		sphereWithBump->setObjectController(new Application::BumpToToon());

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

		Engine::SharedPointer<Engine::Graphics::Effect> proxyLightSphereEffect = proxyLightSphere->getEffect();


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
		intensity.floatVal = 0.3f;


		mainLight->addLightParameter("lightPosition", Engine::Graphics::DataTypes::vec3,
			lightPosition);
		mainLight->addLightParameter("intensity", Engine::Graphics::DataTypes::glfloat,
			intensity);
		mainLight->addLightParameter("lightColor", Engine::Graphics::DataTypes::vec3,
			lightColor);
		mainLight->addLightToAllEffects();
		mainLight->setObjectController(new Application::LightController());
		mainLight->removeLightFromEffect(proxyLightSphereEffect->getEffectName(), Engine::Graphics::Fragment);
		//mainLight->removeLightFromEffect(environmentMappingSphereEffect->getEffectName(), Engine::Graphics::Fragment);
		Engine::SharedPointer<Engine::Camera> mainCamera =
			Engine::Camera::CreateCamera("MainCamera",
				Engine::Math::Vector3(0.0f, 10.0f, 25.0f),
				Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(0.0f),
					Engine::Math::Vector3(0.0f, 0.5f, 0.0f)));

		

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
