#include "Game.h"
#include "../../Engine/Core/EngineCore/EngineCore.h"
#include <windows.h>
#include <fstream>
#include <crtdbg.h>
#include "../../Engine/Core/EngineCore/Objects/Scene.h"
#include "../../Engine/Core/Utilities/SharedPointer.h"
#include "../../Engine/Core/EngineCore/Objects/MeshObject.h"
#include "../../Engine/Core/EngineCore/ObjectController/CameraController.h"
#include "../../Engine/Core/EngineCore/Objects/Camera.h"
#include "../../Engine/Core/Maths/Functions.h"
#include "../../Engine/Windows/WindowsFunctions.h"
#include "../../Engine/Core/Debugging/DebugShapes.h"


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
			Engine::MeshObject::CreateMeshObject("Arena/ceilingMaterialMesh.mesh", "Arena/ceilingMaterial.mat");
		ceiling->setTransformation(Engine::Math::cVector(0, 0, 0), Engine::Math::cQuaternion());
		scene->addObjectToScene(ceiling);

		Engine::SharedPointer<Engine::MeshObject> cementMatObject =
			Engine::MeshObject::CreateMeshObject("Arena/cementMaterialMesh.mesh", "Arena/cementMaterial.mat");
		cementMatObject->setTransformation(Engine::Math::cVector(0, 0, 0), Engine::Math::cQuaternion());
		scene->addObjectToScene(cementMatObject);

		Engine::SharedPointer<Engine::MeshObject> floorMatObject =
			Engine::MeshObject::CreateMeshObject("Arena/FloorMaterialMesh.mesh", "Arena/floorMaterial.mat");
		floorMatObject->setTransformation(Engine::Math::cVector(0, 0, 0), Engine::Math::cQuaternion());
		scene->addObjectToScene(floorMatObject);

		Engine::SharedPointer<Engine::MeshObject> lambertTwoMatObjects =
			Engine::MeshObject::CreateMeshObject("Arena/LambertTwoMaterialMesh.mesh", "Arena/lambertTwoMaterial.mat");
		lambertTwoMatObjects->setTransformation(Engine::Math::cVector(0, 0, 0), Engine::Math::cQuaternion());
		scene->addObjectToScene(lambertTwoMatObjects);

		Engine::SharedPointer<Engine::MeshObject> metals =
			Engine::MeshObject::CreateMeshObject("Arena/MetalMaterialMesh.mesh", "Arena/metalMaterial.mat");
		metals->setTransformation(Engine::Math::cVector(0, 0, 0), Engine::Math::cQuaternion());
		scene->addObjectToScene(metals);

		Engine::SharedPointer<Engine::MeshObject> railing =
			Engine::MeshObject::CreateMeshObject("Arena/railingMaterialMesh.mesh", "Arena/railingMaterial.mat");
		railing->setTransformation(Engine::Math::cVector(0, 0, 0), Engine::Math::cQuaternion());
		scene->addObjectToScene(railing);

		Engine::SharedPointer<Engine::MeshObject> walls =
			Engine::MeshObject::CreateMeshObject("Arena/wallsMaterialMesh.mesh", "Arena/wallsMaterial.mat");
		walls->setTransformation(Engine::Math::cVector(0, 0, 0), Engine::Math::cQuaternion());
		scene->addObjectToScene(walls);

		//DebugObjects
		Engine::Debug::DrawShape(Engine::SPHERE,
			Engine::Maths::Point3(-70.0f, 0.0f, 0.0f), 1.0f,
			Engine::Graphics::RGBColor(1.0f, 0.0f, 0.0f));

		Engine::Debug::DrawShape(Engine::SPHERE,
		Engine::Maths::Point3(0.0f, 0.0f, 0.0f), 1.0f,
		Engine::Graphics::RGBColor(0.0f, 1.0f, 0.0f));

		Engine::Debug::DrawShape(Engine::BOX,
		Engine::Maths::Point3(200.0f, 50.0f, 0.0f), 1.0f,1.0f,1.0f,
		Engine::Graphics::RGBColor(1.0f, 0.0f, 1.0f));

		Engine::Debug::DrawShape(Engine::BOX,
			Engine::Maths::Point3(170.0f, 20.0f, -10.0f), 1.0f, 1.0f, 1.0f,
			Engine::Graphics::RGBColor(1.0f, 1.0f, 0.0f));

		Engine::Debug::DrawShape(Engine::CYLINDER,
			Engine::Maths::Point3(100.0f, 20.0f, -20.0f), 1.0f,1.0f,
			Engine::Graphics::RGBColor(0.0f, 0.0f, 1.0f));

		Engine::Debug::DrawShape(Engine::CYLINDER,
			Engine::Maths::Point3(-70.0f, 0.0f, 0.0f), 1.0f, 1.0f,
			Engine::Graphics::RGBColor(0.5f, 0.5f, 0.5f));

		Engine::Debug::DrawShape(Engine::LINE,
			Engine::Maths::Point3(-53.28f,-108.953f,1043.751f), 
			Engine::Maths::Point3(0.0f,0.0f,0.0f),
			Engine::Graphics::RGBColor(0,1.0f,0.0f));


		/*Engine::Debug::DrawShape(Engine::LINE,
			Engine::Maths::Point3(-53.28f, -108.953f, 1043.751f),
			Engine::Maths::Point3(-70.0f, 0.0f, 0.0f),
			Engine::Graphics::RGBColor(0, 1.0f, 1.0f));*/


		//Camera
		Engine::SharedPointer<Engine::Camera> mainCamera =
			Engine::Camera::CreateCamera("MainCamera",
				Engine::Math::cVector(-53.258, -108.953, 1043.751),
				Engine::Math::cQuaternion(Engine::Math::ConvertDegreesToRadians(0),
					Engine::Math::cVector(0, 1, 0)));

		/*Engine::SharedPointer<Engine::Camera> mainCamera =
		Engine::Camera::CreateCamera("MainCamera",
		Engine::Math::cVector(0, -1, -10),
		Engine::Math::cQuaternion(Engine::Math::ConvertDegreesToRadians(0),
		Engine::Math::cVector(0, 1, 0)));*/

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