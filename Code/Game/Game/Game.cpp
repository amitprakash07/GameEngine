#include "Game.h"
#include "../../Engine/Core/EngineCore/EngineCore.h"
#include <windows.h>
#include <fstream>
#include <crtdbg.h>
#include "../../Engine/Core/EngineCore/Objects/Scene.h"
#include "../../Engine/Core/Utilities/SharedPointer.h"
#include "../../Engine/Core/EngineCore/Objects/GameObject.h"
#include "../../Engine/Core/EngineCore/ObjectController/WalkController.h"



int WINAPI WinMain(HINSTANCE i_thisInstanceOfTheProgram,HINSTANCE,char* i_commandLineArguments,	int i_initialWindowDisplayState)
{
	{
		//_CrtSetBreakAlloc(156);
		Engine::EngineCore::Initialize(i_thisInstanceOfTheProgram, i_initialWindowDisplayState);
		Engine::SharedPointer<Engine::Scene> scene = Engine::Scene::CreateNewScene("TriangleSquareTriangle");
		Engine::SharedPointer<Engine::GameObject> square = Engine::GameObject::CreateGameObject("square", "data/SquareMesh.mesh", "standard", "data/standard.vshd", "data/standard.fshd");
		Engine::SharedPointer<Engine::GameObject> triangleOne = Engine::GameObject::CreateGameObject("triangle", "data/TriangleMesh.mesh", "standard", "data/standard.vshd", "data/standard.fshd");
		Engine::SharedPointer<Engine::GameObject> triangleTwo = Engine::GameObject::CreateGameObject("triangle", "data/TriangleMesh.mesh", "standard", "data/standard.vshd", "data/standard.fshd");
		square->setGameObjectController(new Engine::WalkController());
		triangleOne->setPositionOffset(Engine::Math::cVector(0.25, 0.25, 0.25));
		triangleOne->setPositionOffset(Engine::Math::cVector(-0.25, -0.25, -0.25));
		scene->addToScene(square);
		scene->addToScene(triangleOne);
		scene->addToScene(triangleTwo);
		scene->renderScene(true);
		while (!Engine::EngineCore::isWindowClosed(i_thisInstanceOfTheProgram))
			Engine::EngineCore::onNewFrame();
		Engine::EngineCore::shutDownEngine();
	}
	_CrtDumpMemoryLeaks();
}