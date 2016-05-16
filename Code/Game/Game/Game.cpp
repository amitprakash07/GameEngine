#include "../../Engine/Core/EngineCore/EngineCore.h"
#include <windows.h>
#include "../../Engine/Core/EngineCore/Objects/Scene.h"
#include "../../Engine/Core/Utilities/SharedPointer.h"
#include "../../Engine/Core/EngineCore/Objects/MeshObject.h"
#include "../../Engine/Core/EngineCore/Objects/Camera.h"
#include "../../Engine/Core/Maths/Functions.h"
#include "../../Engine/Windows/WindowsFunctions.h"
#include "../../Engine/Core/Debugging/DebugShapes.h"
#include "../../Engine/Core/NetworkManager/NetworkManager.h"
#include "ObjectController/CameraController.h"
#include "../../Engine/Graphics/Sprite.h"
#include "ObjectController/ClientPlayerController.h"
#include "ObjectController/ServerPlayerController.h"
#include "LightController.h"
#include "ObjectController/WalkController.h"
#include "../../Engine/Graphics/SSAO.h"
#include "ObjectController/DebugMenuController.h"
#include "../../Engine/Core/Debugging/DebugMenu.h"
#include "../../Engine/Core/Physics/PhysicsSystem.h"
#include "ObjectController/PlayerController.h"
#include "ObjectController/ThirdPersonPlayer.h"


#define shared_pointer_reinterpret_cast_to_object(x) \
		*reinterpret_cast<Engine::SharedPointer<Engine::Object>*>(&x)

//#define SERVER_INSTANCE

int WINAPI WinMain(HINSTANCE i_thisInstanceOfTheProgram, 
	HINSTANCE, char* i_commandLineArguments, 
	int i_initialWindowDisplayState)
{
	{
		bool isServer = false;
		std::string  commandLine(i_commandLineArguments);
		if (commandLine == "true")
			isServer = true;
		else
			isServer = false;

		//_CrtSetBreakAlloc(156);
		Engine::EngineCore::Initialize(i_thisInstanceOfTheProgram,
			i_initialWindowDisplayState, isServer);

		//Engine::Graphics::SSAO::InitializeSSAO("Game/SSAOEffect.effect");
		//Scene
		Engine::SharedPointer<Engine::Scene> scene = Engine::Scene::CreateNewScene("Scene_01");
		scene->renderScene(true);

		//GameObjects		
		Engine::SharedPointer<Engine::MeshObject> ceiling =
			Engine::MeshObject::CreateMeshObject("Game/Arena/ceilingMaterialMesh.mesh",
				"Game/Arena/ceilingMaterial.mat");
		ceiling->setTransform(Engine::Math::Vector3(0, 0, 0), Engine::Math::Quaternion());
		scene->addObjectToScene(ceiling);



		Engine::SharedPointer<Engine::Graphics::Effect> standardLightingEffect =
			ceiling->getEffect();

		Engine::SharedPointer<Engine::MeshObject> cementMatObject =
			Engine::MeshObject::CreateMeshObject("Game/Arena/cementMaterialMesh.mesh",
				"Game/Arena/cementMaterial.mat");
		cementMatObject->setTransform(Engine::Math::Vector3(0, 0, 0),
			Engine::Math::Quaternion());
		scene->addObjectToScene(cementMatObject);

		Engine::SharedPointer<Engine::MeshObject> floorMatObject =
			Engine::MeshObject::CreateMeshObject("Game/Arena/FloorMaterialMesh.mesh",
				"Game/Arena/floorMaterial.mat");
		floorMatObject->setTransform(Engine::Math::Vector3(0, 0, 0),
			Engine::Math::Quaternion());
		scene->addObjectToScene(floorMatObject);

		Engine::SharedPointer<Engine::MeshObject> lambertTwoMatObjects =
			Engine::MeshObject::CreateMeshObject("Game/Arena/LambertTwoMaterialMesh.mesh",
				"Game/Arena/lambertTwoMaterial.mat");
		lambertTwoMatObjects->setTransform(Engine::Math::Vector3(0, 0, 0),
			Engine::Math::Quaternion());
		scene->addObjectToScene(lambertTwoMatObjects);

		Engine::SharedPointer<Engine::MeshObject> metals =
			Engine::MeshObject::CreateMeshObject("Game/Arena/MetalMaterialMesh.mesh",
				"Game/Arena/metalMaterial.mat");
		metals->setTransform(Engine::Math::Vector3(0, 0, 0), Engine::Math::Quaternion());
		scene->addObjectToScene(metals);

		Engine::SharedPointer<Engine::MeshObject> railing =
			Engine::MeshObject::CreateMeshObject("Game/Arena/railingMaterialMesh.mesh",
				"Game/Arena/railingMaterial.mat");
		railing->setTransform(Engine::Math::Vector3(0, 0, 0), Engine::Math::Quaternion());
		scene->addObjectToScene(railing);


		Engine::SharedPointer<Engine::MeshObject> walls =
			Engine::MeshObject::CreateMeshObject("Game/Arena/wallsMaterialMesh.mesh",
				"Game/Arena/wallsMaterial.mat");
		walls->setTransform(Engine::Math::Vector3(0, 0, 0), Engine::Math::Quaternion());
		scene->addObjectToScene(walls);


		/*Engine::SharedPointer<Engine::MeshObject> deadPool =
			Engine::MeshObject::CreateMeshObject("Game/Arena/DeadPool.mesh",
				"Game/Arena/DeadPoolMaterial.mat");
		deadPool->setTransform(Engine::Math::Vector3(0, -100, 0), Engine::Math::Quaternion());
		deadPool->setPlayer(true);
		deadPool->setObjectController(Engine::SharedPointer<Game::WalkController>(
			new Game::WalkController(),
			"Game::WalkController").CastSharedPointer<Engine::IObjectController>());
		scene->addObjectToScene(deadPool);*/

		//DebugObjects
		Engine::SharedPointer<Engine::MeshObject> debugSphere =
			Engine::MeshObject::CreateMeshObject("Game/DebugSphereForClass.mesh",
				"Game/defaultDebugShapes.mat");
		debugSphere->setTransform(Engine::Math::Vector3(0.0f, -100.0f, 100.0f),						
			Engine::Math::Quaternion::getIdentityQuartenion());	
		//scene->addObjectToScene(debugSphere);
		/*debugSphere->setScale(0.1, 0.1, 0.1);
		debugSphere->setRenderable(true);
		debugSphere->EnableDebugging(true);
		debugSphere->setPlayer(true);
		debugSphere->setObjectController(
			Engine::SharedPointer<Game::PlayerController>(new Game::PlayerController(),
				"Game::PlayerController").CastSharedPointer<Engine::IObjectController>());*/
		

		Engine::Debug::DebugMenu::GetDebugMenu()->CreateCheckBox("Show Collision Mesh", debugSphere);
		/*Engine::Debug::DebugMenu::GetDebugMenu()->CreateSlider("Radius", debugSphere, 0.2,10.0);
		Engine::Debug::DebugMenu::GetDebugMenu()->CreateButton("Default Radius", debugSphere);*/
		Engine::Debug::DebugMenu::GetDebugMenu()->setObjectController(
			Engine::SharedPointer<Engine::IObjectController>(
				new Game::DebugMenuController(), "").CastSharedPointer<Engine::IObjectController>());


		Engine::Debug::DebugShapes::DrawShape("xaxis",
			Engine::LINE,
			Engine::Math::Vector3(0, 0, 0),
			Engine::Math::Vector3(100, 0, 0),
			Engine::Graphics::RGBColor(1,0,0));

		Engine::Debug::DebugShapes::DrawShape("yaxis",
			Engine::LINE,
			Engine::Math::Vector3(0, 0, 0),
			Engine::Math::Vector3(0, 100, 0),
			Engine::Graphics::RGBColor(0, 1, 0));

		Engine::Debug::DebugShapes::DrawShape("-zaxis",
			Engine::LINE,
			Engine::Math::Vector3(0, 0, 0),
			Engine::Math::Vector3(100, 0, 100),
			Engine::Graphics::RGBColor(0, 0, 1));

		/*Engine::SharedPointer<Engine::Graphics::Sprite> logoSprite =
			Engine::Graphics::Sprite::CreateSprite("EAElogo",
				"Game/spriteMaterial.mat", 0, 100, 900, 800, Engine::Graphics::VIEWPORT_COORDINATE);
		scene->addObjectToScene(logoSprite);*/


		/*Engine::SharedPointer<Engine::Graphics::Sprite> numberSprite =
			Engine::Graphics::Sprite::CreateSprite("numbers",
				"Game/numbersMaterial.mat", 1540, 1590, 890, 840, Engine::Graphics::VIEWPORT_COORDINATE);
		numberSprite->sliceSprite(1, 10);
		numberSprite->setCellToRender(2);
		scene->addObjectToScene(numberSprite);*/

		
		if (Engine::Networking::NetworkManager::isServerInstance())
		{
			Engine::SharedPointer<Engine::MeshObject> serverObject =
				Engine::MeshObject::CreateMeshObject("Game/Arena/DeadPool.mesh",
					"Game/Arena/DeadPoolMaterial.mat");
			serverObject->setTransform(Engine::Math::Vector3(-50.0f, -120.0f, 700.0f),
				Engine::Math::Quaternion());
			serverObject->SetVertexColor(0.0f, 1.0f, 0.0f, 1.0f);
			serverObject->setObjectType(Engine::ObjectType::SERVER);
			serverObject->getMaterial()->changeMaterialColor(0.0, 1.0, 0.0);
			scene->addObjectToScene(serverObject);
			//serverObject->setObjectController(new Game::ServerPlayerController());
			serverObject->EnableDebugging(false);
			serverObject->setObjectController(Engine::SharedPointer<Game::ServerPlayerController>(new Game::ServerPlayerController(),
				"Game::WalkController").CastSharedPointer<Engine::IObjectController>());
			Engine::Networking::NetworkManager::GetHandler().mServer->addToNetworkPlayerList(serverObject, true);

			Engine::SharedPointer<Engine::MeshObject> serverFlag =
				Engine::MeshObject::CreateMeshObject("Game/Arena/serverFlag.mesh",
					"Game/Arena/serverFlagMaterial.mat");
			serverFlag->setTransform(Engine::Math::Vector3(0, 0, 0), Engine::Math::Quaternion());
			scene->addObjectToScene(serverFlag);
			Engine::Networking::NetworkManager::GetHandler().mServer->addToNetworkPlayerList(serverFlag, true);
		}
		else
		{
			Engine::SharedPointer<Engine::MeshObject> clientObject =
				Engine::MeshObject::CreateMeshObject("Game/Arena/DeadPool.mesh",
					"Game/Arena/DeadPoolMaterial.mat");
			clientObject->setTransform(Engine::Math::Vector3(-250.0f, -120.0f, 700.0f),
				Engine::Math::Quaternion());
			clientObject->getMaterial()->changeMaterialColor(1.0, 0.0, 0.0);
			clientObject->setObjectType(Engine::ObjectType::CLIENT);
			scene->addObjectToScene(clientObject);
			clientObject->EnableDebugging(false);
			//clientObject->setObjectController(new Game::ClientPlayerController());
			clientObject->setObjectController(Engine::SharedPointer<Game::ServerPlayerController>(new Game::ServerPlayerController(),
				"Game::WalkController").CastSharedPointer<Engine::IObjectController>());
			Engine::Networking::NetworkManager::GetHandler().mClient->addToNetworkPlayerList(clientObject, true);

			Engine::SharedPointer<Engine::MeshObject> clientFlag =
				Engine::MeshObject::CreateMeshObject("Game/Arena/clientFlag.mesh",
					"Game/Arena/clientFlagMaterial.mat");
			clientFlag->setTransform(Engine::Math::Vector3(0, 0, 0), Engine::Math::Quaternion());
			scene->addObjectToScene(clientFlag);
			Engine::Networking::NetworkManager::GetHandler().mServer->addToNetworkPlayerList(clientFlag, true);
		}


		

		/*Engine::SharedPointer<Engine::Graphics::Effect> standardLightingEffect =
			mCollsionBoundingBoxMesh->getEffect();*/

		Engine::Physics::PhysicsSystem::InitializePhysicsSystem(
			"Game/Arena/CollisionMesh.mesh");
		

		Engine::SharedPointer<Engine::Graphics::Light> mainLight
			= Engine::Graphics::Light::createLight("mainLight",
				Engine::Graphics::LightType::Point);
		mainLight->setIntensity(0.1f);
		mainLight->setColor(Engine::Math::Vector3(1.0f, 0.0f, 0.0f));
		mainLight->setTransform(Engine::Math::Vector3(0, 19, 0),
			Engine::Math::Quaternion());
		scene->addLightToScene(mainLight);
		Engine::Graphics::Data lightPosition;
		Engine::Graphics::Data  intensity;
		Engine::Graphics::Data lightColor;
		Engine::Math::Vector3 vecLightPosition = Engine::Math::Vector3(-50, 100, 700);
		Engine::Math::Vector3 vecLightColor = Engine::Math::Vector3(1.0f, 1.0f, 1.0f);
		memcpy(&lightPosition.vec3, &vecLightPosition, 3 * sizeof(float));
		memcpy(&lightColor.vec3, &vecLightColor, 3 * sizeof(float));
		intensity.floatVal = 0.4f;
		mainLight->addLightParameter("lightPosition", Engine::Graphics::DataTypes::vec3,
			lightPosition);
		mainLight->addLightParameter("intensity", Engine::Graphics::DataTypes::glfloat,
			intensity);
		mainLight->addLightParameter("lightColor", Engine::Graphics::DataTypes::vec3,
			lightColor);
		mainLight->addLightToEffect(standardLightingEffect->getEffectName(),
			Engine::Graphics::Fragment);

		mainLight->setObjectController(Engine::SharedPointer<Game::LightController>(
			new Game::LightController(), "Game::Light").CastSharedPointer<Engine::IObjectController>());

		//Camera
		Engine::SharedPointer<Engine::Camera> mainCamera =
			Engine::Camera::CreateCamera("MainCamera",
				Engine::Math::Vector3(0.0f, -100.0f, 300.0f),
				Engine::Math::Quaternion::getIdentityQuartenion());

		mainCamera->activateCamera(true);
		mainCamera->setAspectRatio(static_cast<float>(1600.0f / 900.0f));
		mainCamera->setFarPlane(10000.0f);
		mainCamera->setFieldOfView(60.0f);
		mainCamera->setObjectController(
			Engine::SharedPointer<Game::WalkController>(new Game::WalkController(),
				"Game::WalkController").CastSharedPointer<Engine::IObjectController>());
		scene->addCameraToScene(mainCamera);

		while (!Engine::EngineCore::isWindowClosed(i_thisInstanceOfTheProgram))
			Engine::EngineCore::onNewFrame();

	}
	//_CrtDumpMemoryLeaks();
}