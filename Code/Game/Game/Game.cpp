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
		
		Engine::Graphics::SSAO::InitializeSSAO("Game/SSAOEffect.effect");
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


		//Proxy Light
		/*Engine::SharedPointer<Engine::MeshObject> proxyLightSphere =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/proxyLightSphere.mesh",
				"ComputerGraphics/proxyLightSphereMaterial.mat");
		proxyLightSphere->setTransform(Engine::Math::Vector3(-50, 100, 700), Engine::Math::Quaternion());
		scene->addObjectToScene(proxyLightSphere);
		proxyLightSphere->setScale(10, 10, 10);
		proxyLightSphere->setObjectController(new Game::LightController());*/

		//Engine::SharedPointer<Engine::Graphics::Effect> proxyLightSphereEffect = proxyLightSphere->getEffect();

		//Nanosuit
		/*Engine::SharedPointer<Engine::MeshObject> arms =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/NanoSuit/arms.mesh",
				"ComputerGraphics/NanoSuit/armsMaterial.mat");
		arms->setTransform(Engine::Math::Vector3(-50, -250, 700), Engine::Math::Quaternion());
		arms->setScale(8.0f, 8.0f, 8.0f);
		scene->addObjectToScene(arms);


		Engine::SharedPointer<Engine::Graphics::Effect> standardLightingEffect =
			arms->getEffect();


		Engine::SharedPointer<Engine::MeshObject> body =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/NanoSuit/body.mesh",
				"ComputerGraphics/NanoSuit/bodyMaterial.mat");
		body->setTransform(Engine::Math::Vector3(-50, -250, 700), Engine::Math::Quaternion());
		body->setScale(8.0f, 8.0f, 8.0f);
		scene->addObjectToScene(body);

		Engine::SharedPointer<Engine::MeshObject> hands =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/NanoSuit/hands.mesh",
				"ComputerGraphics/NanoSuit/handsMaterial.mat");
		hands->setTransform(Engine::Math::Vector3(-50, -250, 700), Engine::Math::Quaternion());
		hands->setScale(8.0f, 8.0f, 8.0f);
		scene->addObjectToScene(hands);


		Engine::SharedPointer<Engine::MeshObject> Helmet =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/NanoSuit/Helmet.mesh",
				"ComputerGraphics/NanoSuit/HelmetMaterial.mat");
		Helmet->setTransform(Engine::Math::Vector3(-50, -250, 700), Engine::Math::Quaternion());
		Helmet->setScale(8.0f, 8.0f, 8.0f);
		scene->addObjectToScene(Helmet);


		Engine::SharedPointer<Engine::MeshObject> legs =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/NanoSuit/legs.mesh",
				"ComputerGraphics/NanoSuit/legsMaterial.mat");
		legs->setTransform(Engine::Math::Vector3(-50, -250, 700), Engine::Math::Quaternion());
		legs->setScale(8.0f, 8.0f, 8.0f);
		scene->addObjectToScene(legs);


		Engine::SharedPointer<Engine::MeshObject> lights =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/NanoSuit/lights.mesh",
				"ComputerGraphics/NanoSuit/lightsMaterial.mat");
		lights->setTransform(Engine::Math::Vector3(-50, -250, 700), Engine::Math::Quaternion());
		lights->setScale(8.0f, 8.0f, 8.0f);
		scene->addObjectToScene(lights);


		Engine::SharedPointer<Engine::MeshObject> Visor =
			Engine::MeshObject::CreateMeshObject("ComputerGraphics/NanoSuit/Visor.mesh",
				"ComputerGraphics/NanoSuit/VisorMaterial.mat");
		Visor->setTransform(Engine::Math::Vector3(-50, -250, 700), Engine::Math::Quaternion());
		Visor->setScale(8.0f, 8.0f, 8.0f);
		scene->addObjectToScene(Visor);*/
				
		//scene->EnableAllMeshObjectsForSSAO();

		//proxyLightSphere->EnableSSAO(false);

		//DebugObjects
		/*Engine::Debug::DrawShape(Engine::SPHERE,
			Engine::Math::Vector3(-70.0f, 0.0f, 0.0f), 1.0f,
			Engine::Graphics::RGBColor(1.0f, 0.0f, 0.0f));

		Engine::Debug::DrawShape(Engine::SPHERE,
			Engine::Math::Vector3(0.0f, 0.0f, 0.0f), 1.0f,
		Engine::Graphics::RGBColor(0.0f, 1.0f, 0.0f));

		Engine::Debug::DrawShape(Engine::BOX,
			Engine::Math::Vector3(200.0f, 50.0f, 0.0f), 1.0f,1.0f,1.0f,
		Engine::Graphics::RGBColor(1.0f, 0.0f, 1.0f));

		Engine::Debug::DrawShape(Engine::BOX,
			Engine::Math::Vector3(170.0f, 20.0f, -10.0f), 1.0f, 1.0f, 1.0f,
			Engine::Graphics::RGBColor(1.0f, 1.0f, 0.0f));

		Engine::Debug::DrawShape(Engine::CYLINDER,
			Engine::Math::Vector3(100.0f, 20.0f, -20.0f), 1.0f,1.0f,
			Engine::Graphics::RGBColor(0.0f, 0.0f, 1.0f));

		Engine::Debug::DrawShape(Engine::CYLINDER,
			Engine::Math::Vector3(-70.0f, 0.0f, 0.0f), 1.0f, 1.0f,
			Engine::Graphics::RGBColor(0.5f, 0.5f, 0.5f));

		Engine::Debug::DrawShape(Engine::LINE,
			Engine::Math::Vector3(-53.28f,-108.953f,1043.751f),
			Engine::Math::Vector3(0.0f,0.0f,0.0f),
			Engine::Graphics::RGBColor(0,1.0f,0.0f));


		Engine::Debug::DrawShape(Engine::LINE,
			Engine::Math::Vector3(-53.28f, -108.953f, 1043.751f),
			Engine::Math::Vector3(-70.0f, 0.0f, 0.0f),
			Engine::Graphics::RGBColor(0, 1.0f, 1.0f));*/

		/*Engine::SharedPointer<Engine::Graphics::Sprite> logoSprite = 
			Engine::Graphics::Sprite::CreateSprite("EAElogo", 
				"Game/spriteMaterial.mat", 0, 100, 900, 800, Engine::Graphics::VIEWPORT_COORDINATE);
		scene->addObjectToScene(logoSprite);


		Engine::SharedPointer<Engine::Graphics::Sprite> numberSprite =
			Engine::Graphics::Sprite::CreateSprite("numbers",
				"Game/numbersMaterial.mat", 1540, 1590, 890, 840, Engine::Graphics::VIEWPORT_COORDINATE);
		numberSprite->sliceSprite(1, 10);
		numberSprite->setCellToRender(2);
		scene->addObjectToScene(numberSprite);*/
		

		if (Engine::Networking::NetworkManager::isServerInstance())
		{
			Engine::SharedPointer<Engine::MeshObject> serverObject =
				Engine::MeshObject::CreateMeshObject("Game/DebugSphereForClass.mesh",
					"Game/defaultDebugShapes.mat");
			serverObject->setTransform(Engine::Math::Vector3(-50.0f, 20.0f, 700.0f),
				Engine::Math::Quaternion());
			serverObject->SetVertexColor(0.0f, 1.0f, 0.0f, 1.0f);
			serverObject->setObjectType(Engine::ObjectType::SERVER);
			serverObject->getMaterial()->changeMaterialColor(0.0, 1.0, 0.0);
			scene->addObjectToScene(serverObject);
			//serverObject->setObjectController(new Game::ServerPlayerController());
			serverObject->EnableDebugging(true);
			serverObject->setObjectController(new Game::WalkController());
			Engine::Networking::NetworkManager::GetHandler().mServer->addToNetworkPlayerList(serverObject, true);			
		}
		else
		{
			Engine::SharedPointer<Engine::MeshObject> clientObject =
				Engine::MeshObject::CreateMeshObject("Game/DebugSphereForClass.mesh",
					"Game/defaultDebugShapes.mat");
			clientObject->setTransform(Engine::Math::Vector3(-250.0f, 20.0f, 700.0f),
				Engine::Math::Quaternion());
			clientObject->getMaterial()->changeMaterialColor(1.0, 0.0, 0.0);
			clientObject->setObjectType(Engine::ObjectType::CLIENT);
			scene->addObjectToScene(clientObject);
			clientObject->EnableDebugging(true);
			//clientObject->setObjectController(new Game::ClientPlayerController());
			clientObject->setObjectController(new Game::WalkController());
			Engine::Networking::NetworkManager::GetHandler().mClient->addToNetworkPlayerList(clientObject, true);
		}


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

		mainLight->setObjectController(new Game::LightController());

		

		//Camera
		Engine::SharedPointer<Engine::Camera> mainCamera =
			Engine::Camera::CreateCamera("MainCamera",
				Engine::Math::Vector3(-53.258f, -108.953f, 1043.751f),
				Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(0),
					Engine::Math::Vector3(0, 1, 0)));

		mainCamera->activateCamera(true);
		mainCamera->setAspectRatio(static_cast<float>(1600.0f / 900.0f));
		mainCamera->setFarPlane(10000.0f);
		mainCamera->setFieldOfView(60.0f);
		//mainCamera->setObjectController(new Game::WalkController());
		scene->addCameraToScene(mainCamera);		

		while (!Engine::EngineCore::isWindowClosed(i_thisInstanceOfTheProgram))
			Engine::EngineCore::onNewFrame();

	}
	//_CrtDumpMemoryLeaks();
}