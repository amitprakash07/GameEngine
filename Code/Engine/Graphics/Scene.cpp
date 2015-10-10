#include  "Scene.h"
#include "../Windows/WindowsFunctions.h"
std::vector<Engine::Graphics::Mesh*> Engine::Graphics::Scene::scene;


bool Engine::Graphics::Scene::addToScene(std::string i_fileName)
{
	if (!i_fileName.empty())
	{
		Mesh *newMesh = new Mesh();
		newMesh->setMeshFileName(i_fileName);
		newMesh->LoadMesh();
		scene.push_back(newMesh);
		return true;
	}

	std::stringstream errormessage;
	errormessage << "Unable to add Scene. Mesh Pointer is null. Load Mesh again";
	WindowsUtil::Print(errormessage.str());
	return false;
}
void Engine::Graphics::Scene::drawScene()
{
	std::stringstream errormessage;
	size_t meshCount = scene.size();
	if(meshCount == 0)
	{
		errormessage << "There is no mesh in the scene to draw.";
		WindowsUtil::Print(errormessage.str());
	}

	for (int i = 0; i < meshCount;i++)
	{
		if(!scene[i]->drawMesh())
		{
			//char * meshName = scene[i]->getMeshFileName();
			errormessage << "Graphics API is unable to draw the" << scene[i]->getMeshFileName().c_str();
			WindowsUtil::Print(errormessage.str());
		}
	}
}
Engine::Graphics::Scene::Scene()
{
	scene.reserve(10);
}
Engine::Graphics::Scene::~Scene()
{
	
}
void Engine::Graphics::Scene::deleteScene()
{
	for (int i = 0; i < scene.size(); i++)
		delete scene[i];
}


