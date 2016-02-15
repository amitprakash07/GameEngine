#include "Scene.h"
#include "../../../Graphics/Effect.h"
#include "../../../Graphics/Mesh.h"
#include "../../../Windows/WindowsFunctions.h"
#include <algorithm>

std::map<std::string, Engine::SharedPointer<Engine::Scene>> Engine::Scene::mSceneList;

Engine::Scene::Scene(std::string i_sceneName) :
	mTimer(Engine::Time::FrameTime::getFrameTimeController())
{
	mScene.reserve(20);
	sceneName = i_sceneName;
	render = false;
}

Engine::SharedPointer<Engine::Scene> Engine::Scene::CreateNewScene(std::string i_sceneName)
{
	if (!i_sceneName.empty())
	{
		SharedPointer<Engine::Scene> temp = SharedPointer<Engine::Scene>(new Scene(i_sceneName), "Engine::Scene");
		mSceneList[i_sceneName] = temp;
		return (getScene(i_sceneName));
	}
	return(SharedPointer<Scene>());
}


Engine::SharedPointer<Engine::Time::FrameTime> Engine::Scene::getTimer()
{
	return(getRenderableScene()->mTimer);
}



Engine::Scene::~Scene()
{
	for (std::vector<SharedPointer<MeshObject>>::iterator i = mScene.begin(); i != mScene.end(); ++i)
		i->deleteObject();

}

bool Engine::Scene::addGameObjectToScene(SharedPointer<MeshObject> & i_game_object)
{
	if (!i_game_object.isNull())
	{
		mScene.push_back(i_game_object);
		return true;
	}
	mTimer.deleteObject();
	return false;
}


bool Engine::Scene::addCameraToScene(SharedPointer<Camera>& i_camera)
{
	if (!i_camera.isNull())
	{
		mCameraListInScene[i_camera->getCameraName()] = i_camera;
		return true;
	}
	return false;
}


void Engine::Scene::renderScene(bool i_render)
{
	deactivateAllSceneToRender();
	render = i_render;
}


void Engine::Scene::deactivateAllSceneToRender()
{
	for (std::map<std::string, SharedPointer<Scene>>::iterator i = mSceneList.begin(); i != mSceneList.end(); ++i)
		i->second->render = false;
}


Engine::SharedPointer<Engine::Scene> Engine::Scene::getRenderableScene()
{
	for (std::map<std::string, SharedPointer<Scene>>::iterator i = mSceneList.begin(); i != mSceneList.end(); ++i)
	{
		if (i->second->render)
			return i->second;
	}
	return(SharedPointer<Scene>());
}


void Engine::Scene::drawScene()
{
	for (std::vector<SharedPointer<Engine::MeshObject>>::iterator i = mScene.begin(); i != mScene.end(); ++i)
	{
		(*i)->draw();
	}
	mTimer->updateDeltaTime();
}

void Engine::Scene::applyPaintersAlgorithmForTransparency()
{
	SharedPointer<Scene> activeScene = getRenderableScene();
	std::sort(activeScene->mScene.begin(), activeScene->mScene.end(), sortingFunc);
}


bool Engine::Scene::sortingFunc(SharedPointer<MeshObject> i_gameObjectOne,
	SharedPointer<MeshObject> i_gameObjectTwo)
{
	if (i_gameObjectOne->getTransformation().mPositionOffset.z <
		i_gameObjectTwo->getTransformation().mPositionOffset.z)
		return true;
	return false;
}


bool Engine::Scene::isSceneExist(std::string i_sceneName)
{
	if (!i_sceneName.empty())
	{
		for (std::map<std::string, SharedPointer<Scene>>::iterator i = mSceneList.begin(); i != mSceneList.end(); ++i)
		{
			if (i->first == i_sceneName)
				return true;
		}
		return false;
	}
	return false;
}


Engine::SharedPointer<Engine::Scene> Engine::Scene::getScene(std::string i_sceneName)
{
	if (!i_sceneName.empty() && isSceneExist(i_sceneName))
	{
		for (std::map<std::string, SharedPointer<Scene>>::iterator i = mSceneList.begin(); i != mSceneList.end(); ++i)
		{
			if (i->first == i_sceneName)
			{
				return (i->second);
			}
		}
	}
	return(SharedPointer<Scene>());
}


void Engine::Scene::deleteAllScene()
{
	for (std::map<std::string, SharedPointer<Scene>>::iterator i = mSceneList.begin(); i != mSceneList.end(); ++i)
	{
		for (std::vector<SharedPointer<MeshObject>>::iterator j = i->second->mScene.begin(); j != i->second->mScene.end(); ++j)
			j->deleteObject();
	}
}

Engine::SharedPointer<Engine::Camera> Engine::Scene::getActiveCamera() const
{
	for (std::map<std::string, SharedPointer<Camera>>::const_iterator i = mCameraListInScene.begin();
	i != mCameraListInScene.end(); ++i)
	{
		if (i->second->isActive())
			return i->second;
	}
	return SharedPointer<Camera>();
}

void Engine::Scene::deactivateAllCamera() const
{
	for (std::map<std::string, SharedPointer<Camera>>::const_iterator i = mCameraListInScene.begin();
	i != mCameraListInScene.end(); ++i)
	{
		i->second->activateCamera(false);
	}
}

void Engine::Scene::useCamera(SharedPointer<Camera> iCamera) const
{
	if (findCamera(iCamera))
	{
		deactivateAllCamera();
		iCamera->activateCamera(true);
	}
}

void Engine::Scene::useCamera(const std::string iCamera) const
{
	SharedPointer<Camera> tempCamera = findCamera(iCamera);
	if (!tempCamera.isNull())
		useCamera(tempCamera);
}

bool Engine::Scene::findCamera(const SharedPointer<Camera> iCamera) const
{
	for (std::map<std::string, SharedPointer<Camera>>::const_iterator i = mCameraListInScene.begin();
	i != mCameraListInScene.end(); ++i)
	{
		if (iCamera.isEqual(i->second))
			return true;
	}
	return false;
}

Engine::SharedPointer<Engine::Camera> Engine::Scene::findCamera(const std::string iCamera) const
{
	for (std::map<std::string, SharedPointer<Camera>>::const_iterator i = mCameraListInScene.begin();
	i != mCameraListInScene.end(); ++i)
	{
		if (iCamera == i->first)
			return i->second;
	}
	return SharedPointer<Camera>();
}












