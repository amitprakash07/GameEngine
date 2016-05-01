#include "../Engine/Core/Maths/Vector3.h"
#include "../Engine/Graphics/uniformdefs.h"
#include "../Engine/Graphics/Light.h"
#include "../Engine/Core/NetworkManager/NetworkManager.h"
#include "../Engine/Core/EngineCore/Objects/MeshObject.h"
#include "../Engine/Core/EngineCore/Objects/Scene.h"
#include "../Engine/Core/EngineCore/EngineCore.h"
#include "../Game/Game/ObjectController/CameraController.h"
#include "../Engine/Core/Maths/Functions.h"


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


		Engine::SharedPointer<Engine::MeshObject> clientObject =
			Engine::MeshObject::CreateMeshObject("Game/DebugSphereForClass.mesh",
				"Game/defaultDebugShapes.mat");
		clientObject->setTransform(Engine::Math::Vector3(-250.0f, 20.0f, 700.0f),
			Engine::Math::Quaternion());
		clientObject->getMaterial()->changeMaterialColor(1.0, 0.0, 0.0);
		clientObject->setObjectType(Engine::ObjectType::CLIENT);
		scene->addObjectToScene(clientObject);
		clientObject->EnableDebugging(true);
		clientObject->setObjectController(new Game::ClientPlayerController());
		if (Engine::Networking::NetworkManager::isServerInstance())
			clientObject->setRenderable(false);
		else
		{
			//client system
			Engine::Networking::NetworkPacket mSendPacket{ clientObject->getTransform() };
			Engine::Networking::NetworkManager::setSendingNetworkPacket(mSendPacket);
		}





		Engine::SharedPointer<Engine::MeshObject> serverObject =
			Engine::MeshObject::CreateMeshObject("Game/DebugSphereForClass.mesh",
				"Game/defaultDebugShapes.mat");
		serverObject->setTransform(Engine::Math::Vector3(-50.0f, 20.0f, 700.0f),
			Engine::Math::Quaternion());
		serverObject->setObjectType(Engine::ObjectType::SERVER);
		serverObject->getMaterial()->changeMaterialColor(0.0, 1.0, 0.0);
		scene->addObjectToScene(serverObject);
		serverObject->setObjectController(new Game::ServerPlayerController());
		serverObject->EnableDebugging(true);
		if (Engine::Networking::NetworkManager::isServerInstance())
		{
			//server system
			Engine::Networking::NetworkPacket mSendPacket{ serverObject->getTransform() };
			Engine::Networking::NetworkManager::setSendingNetworkPacket(mSendPacket);
		}
		else
			//client system
			serverObject->setRenderable(false);



		Engine::SharedPointer<Engine::Graphics::Light> mainLight
			= Engine::Graphics::Light::createLight("mainLight",
				Engine::Graphics::LightType::Point);
		mainLight->setIntensity(1.0f);
		mainLight->setColor(Engine::Math::Vector3(1.0f, 0.0f, 0.0f));
		mainLight->setTransform(Engine::Math::Vector3(0, 19, 0),
			Engine::Math::Quaternion());
		scene->addLightToScene(mainLight);
		Engine::Graphics::Data lightPosition;
		Engine::Graphics::Data  intensity;
		Engine::Graphics::Data lightColor;
		Engine::Math::Vector3 vecLightPosition = Engine::Math::Vector3(100.0f, 50.0f, -20.0f);
		Engine::Math::Vector3 vecLightColor = Engine::Math::Vector3(1.0f, 1.0f, 1.0f);
		memcpy(&lightPosition.vec3, &vecLightPosition, 3 * sizeof(float));
		memcpy(&lightColor.vec3, &vecLightColor, 3 * sizeof(float));
		intensity.floatVal = 0.8f;
		mainLight->addLightParameter("lightPosition", Engine::Graphics::DataTypes::vec3,
			lightPosition);
		mainLight->addLightParameter("intensity", Engine::Graphics::DataTypes::glfloat,
			intensity);
		mainLight->addLightParameter("lightColor", Engine::Graphics::DataTypes::vec3,
			lightColor);
		mainLight->addLightToEffect(standardLightingEffect->getEffectName(),
			Engine::Graphics::Fragment);
		mainLight->setObjectController(new Game::CameraController());

		//Camera
		Engine::SharedPointer<Engine::Camera> mainCamera =
			Engine::Camera::CreateCamera("MainCamera",
				Engine::Math::Vector3(-53.258, -108.953, 1043.751),
				Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(0),
					Engine::Math::Vector3(0, 1, 0)));

		mainCamera->activateCamera(true);
		mainCamera->setAspectRatio(static_cast<float>(1600.0f / 900.0f));
		mainCamera->setFarPlane(10000.0f);
		mainCamera->setFieldOfView(60.0f);
		mainCamera->setObjectController(new Game::CameraController());
		scene->addCameraToScene(mainCamera);

		while (!Engine::EngineCore::isWindowClosed(i_thisInstanceOfTheProgram))
			Engine::EngineCore::onNewFrame();

	}
	//_CrtDumpMemoryLeaks();
}