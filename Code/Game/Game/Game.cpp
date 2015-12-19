#include "Game.h"
#include "../../Engine/Core/EngineCore/EngineCore.h"
#include <windows.h>
#include <fstream>
#include <crtdbg.h>
#include "../../Engine/Core/EngineCore/Objects/Scene.h"
#include "../../Engine/Core/Utilities/SharedPointer.h"
#include "../../Engine/Core/EngineCore/Objects/GameObject.h"
#include "../../Engine/Core/EngineCore/ObjectController/WalkController.h"
#include "../../Engine/Core/EngineCore/ObjectController/CameraController.h"
#include "../../Engine/Core/EngineCore/Objects/Camera.h"
#include "../../Engine/Core/Maths/Functions.h"





int WINAPI WinMain(HINSTANCE i_thisInstanceOfTheProgram,HINSTANCE,char* i_commandLineArguments,	int i_initialWindowDisplayState)
{
	{
		//_CrtSetBreakAlloc(156);
		Engine::EngineCore::Initialize(i_thisInstanceOfTheProgram, i_initialWindowDisplayState);
		
		//Scene
		Engine::SharedPointer<Engine::Scene> scene = Engine::Scene::CreateNewScene("Scene_01");
		
		//GameObjects
		
		

		Engine::SharedPointer<Engine::GameObject> sphereOne =
			Engine::GameObject::CreateGameObject("Sphere.mesh", "BrickMaterial_opaque.mat");
		sphereOne->setTransformation(Engine::Math::cVector(-4, -3, -7), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(sphereOne);
		
		Engine::SharedPointer<Engine::GameObject> sphereTwo =
			Engine::GameObject::CreateGameObject("Sphere.mesh", "BrickMaterial_opaque_Blue.mat");
		sphereTwo->setTransformation(Engine::Math::cVector(-2, -3, -7), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(sphereTwo);


		Engine::SharedPointer<Engine::GameObject> sphereThree =
			Engine::GameObject::CreateGameObject("Sphere.mesh", "BrickMaterial_transparent_blue_green.mat");
		sphereThree->setTransformation(Engine::Math::cVector(0, -3, -7), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(sphereThree);

		Engine::SharedPointer<Engine::GameObject> sphereFour =
			Engine::GameObject::CreateGameObject("Sphere.mesh", "BrickMaterial_transparent_red_green.mat");
		sphereFour->setTransformation(Engine::Math::cVector(2, -3, -7), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(sphereFour);

		Engine::SharedPointer<Engine::GameObject> ground =
			Engine::GameObject::CreateGameObject("Ground.mesh", "GroundOpaque.mat");
		ground->setTransformation(Engine::Math::cVector(0, -3, -12), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(ground);


		Engine::SharedPointer<Engine::GameObject> helix =
		Engine::GameObject::CreateGameObject("HelixOpaque.mesh", "BrickMaterial_opaque_Blue.mat");
		helix->setTransformation(Engine::Math::cVector(2.5,0,-10), Engine::Math::cQuaternion());
		helix->setGameObjectController(new Engine::WalkController());
		scene->addGameObjectToScene(helix);

		Engine::SharedPointer<Engine::GameObject> verticalPlaneOpaque =
			Engine::GameObject::CreateGameObject("Plane.mesh", "verticalPlaneOpaque.mat");
		verticalPlaneOpaque->setTransformation(Engine::Math::cVector(2.5, 0, -10), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(verticalPlaneOpaque);

		Engine::SharedPointer<Engine::GameObject> verticalPlaneTransparent=
			Engine::GameObject::CreateGameObject("Plane.mesh", "verticalPlaneTransparent.mat");
		verticalPlaneTransparent->setTransformation(Engine::Math::cVector(-2, 0, -10), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(verticalPlaneTransparent);




		/*Engine::SharedPointer<Engine::GameObject> backDoor =
		Engine::GameObject::CreateGameObject("RoomMeshes/AdditionalFloorFrames.mesh", "Room/FloorCrossSection.mat");
		backDoor->setTransformation(Engine::Math::cVector(0, 0, 0), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(backDoor);


		Engine::SharedPointer<Engine::GameObject> BackWall =
			Engine::GameObject::CreateGameObject("RoomMeshes/Walls.mesh", "Room/BackWall.mat");
		BackWall->setTransformation(Engine::Math::cVector(0, 0, 0), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(BackWall);

		Engine::SharedPointer<Engine::GameObject> BookCenterTable =
			Engine::GameObject::CreateGameObject("RoomMeshes/CenterBook.mesh", "Room/BookCenterTable.mat");
		BookCenterTable->setTransformation(Engine::Math::cVector(0, 0, 0), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(BookCenterTable);


		Engine::SharedPointer<Engine::GameObject> BookPile2 =
			Engine::GameObject::CreateGameObject("RoomMeshes/Books.mesh", "Room/BookPile2.mat");
		BookPile2->setTransformation(Engine::Math::cVector(0, 0, 0), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(BookPile2);

		Engine::SharedPointer<Engine::GameObject> Carpet =
		Engine::GameObject::CreateGameObject("RoomMeshes/Carpets.mesh", "Room/Carpet.mat");
		Carpet->setTransformation(Engine::Math::cVector(0, 0, 0), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(Carpet);


		Engine::SharedPointer<Engine::GameObject> CenterTable =
			Engine::GameObject::CreateGameObject("RoomMeshes/CenterTable.mesh", "Room/CenterTable.mat");
		CenterTable->setTransformation(Engine::Math::cVector(0, 0, 0), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(CenterTable);


		Engine::SharedPointer<Engine::GameObject> Couch =
			Engine::GameObject::CreateGameObject("RoomMeshes/Couch.mesh", "Room/Couch.mat");
		Couch->setTransformation(Engine::Math::cVector(0, 0, 0), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(Couch);


		Engine::SharedPointer<Engine::GameObject> Curtain =
			Engine::GameObject::CreateGameObject("RoomMeshes/Curtain.mesh", "Room/Curtain.mat");
		Curtain->setTransformation(Engine::Math::cVector(0, 0, 0), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(Curtain);


		Engine::SharedPointer<Engine::GameObject> Doors =
			Engine::GameObject::CreateGameObject("RoomMeshes/Doors.mesh", "Room/Doors.mat");
		Doors->setTransformation(Engine::Math::cVector(0, 0, 0), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(Doors);


		Engine::SharedPointer<Engine::GameObject> Floor =
			Engine::GameObject::CreateGameObject("RoomMeshes/FloorAndFrames.mesh", "Room/Floor.mat");
		Floor->setTransformation(Engine::Math::cVector(0, 0, 0), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(Floor);

		Engine::SharedPointer<Engine::GameObject> Shelves =
			Engine::GameObject::CreateGameObject("RoomMeshes/Shelves.mesh", "Room/Shelves.mat");
		Shelves->setTransformation(Engine::Math::cVector(0, 0, 0), Engine::Math::cQuaternion());
		scene->addGameObjectToScene(Shelves);*/

		


		//Camera
		/*Engine::SharedPointer<Engine::Camera> mainCamera =
			Engine::Camera::CreateCamera("MainCamera",
				Engine::Math::cVector(0, 5, 45.85),
				Engine::Math::cQuaternion(Engine::Math::ConvertDegreesToRadians(0),
					Engine::Math::cVector(0,1,0)));*/

		Engine::SharedPointer<Engine::Camera> mainCamera =
			Engine::Camera::CreateCamera("MainCamera",
				Engine::Math::cVector(0, 0,5),
				Engine::Math::cQuaternion(Engine::Math::ConvertDegreesToRadians(0),
					Engine::Math::cVector(0, 1, 0)));

		mainCamera->activateCamera(true);
		mainCamera->setAspectRatio(static_cast<float>(1600 / 900));
		mainCamera->setFieldOfView(60.0f);
		mainCamera->setCameraController(new Engine::CameraController());
		//mainCamera->setCameraController(new Engine::WalkController());
		scene->addCameraToScene(mainCamera);		
		scene->renderScene(true);
		
		while (!Engine::EngineCore::isWindowClosed(i_thisInstanceOfTheProgram))
			Engine::EngineCore::onNewFrame();
		
	}
	//_CrtDumpMemoryLeaks();
}