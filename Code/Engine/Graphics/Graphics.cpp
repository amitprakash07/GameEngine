#include "Graphics.h"
#include "../Core/EngineCore/Objects/Scene.h"

bool Engine::Graphics::GraphicsSystem::Initialize(const HWND i_renderingWindow)
{
	s_renderingWindow = i_renderingWindow;
	if (create())
		return true;
	return false;
}

bool Engine::Graphics::GraphicsSystem::ShutDown()
{
	if (destroy())
		return true;
	return false;
}


void Engine::Graphics::GraphicsSystem::Render()
{
	clear();
 	beginScene();
	Engine::Scene::getRenderableScene()->drawScene();
	endScene();
	showBuffer();
}
