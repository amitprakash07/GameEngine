#include "../../Engine/Core/EngineCore/EngineCore.h"
#include <windows.h>
#include "../../Engine/Core/EngineCore/Objects/Scene.h"
#include "../../Engine/Core/Utilities/SharedPointer.h"
#include "../../Engine/Core/EngineCore/Objects/MeshObject.h"
#include "../../Engine/Core/EngineCore/Objects/Camera.h"
#include "../../Engine/Core/Maths/Functions.h"
#include "../../Engine/Windows/WindowsFunctions.h"
#include "../../Engine/Core/Debugging/DebugShapes.h"
#include "ObjectController/CameraController.h"
#include "../../Engine/Graphics/Sprite.h"


#define shared_pointer_reinterpret_cast_to_object(x) \
		*reinterpret_cast<Engine::SharedPointer<Engine::Object>*>(&x)




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

		//DebugObjects
		Engine::Debug::DrawShape(Engine::SPHERE,
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
			Engine::Graphics::RGBColor(0, 1.0f, 1.0f));

		Engine::SharedPointer<Engine::Graphics::Sprite> logoSprite = 
			Engine::Graphics::Sprite::CreateSprite("EAElogo", 
				"Game/spriteMaterial.mat", 0, 100, 900, 800, Engine::Graphics::VIEWPORT_COORDINATE);
		scene->addObjectToScene(logoSprite);


		Engine::SharedPointer<Engine::Graphics::Sprite> numberSprite =
			Engine::Graphics::Sprite::CreateSprite("numbers",
				"Game/numbersMaterial.mat", 1540, 1590, 890, 840, Engine::Graphics::VIEWPORT_COORDINATE);
		scene->addObjectToScene(numberSprite);
		numberSprite->sliceSprite(1, 10);
		numberSprite->setCellToRender(2);

		//Camera
		Engine::SharedPointer<Engine::Camera> mainCamera =
			Engine::Camera::CreateCamera("MainCamera",
				Engine::Math::Vector3(-53.258, -108.953, 1043.751),
				Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(0),
					Engine::Math::Vector3(0, 1, 0)));

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