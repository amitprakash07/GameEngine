#include "Scene.h"
#include "../../../Graphics/Mesh.h"
#include "../../../Graphics/SkyBox.h"
#include <algorithm>

std::map<std::string, Engine::SharedPointer<Engine::Scene>> Engine::Scene::mSceneList;

Engine::Scene::Scene(std::string i_sceneName) :
	mTimer(Engine::Time::FrameTime::getFrameTimeController())
{
	mMeshObjectInSceneList.reserve(20);
	mLineListInScene.reserve(20);
	mSpriteListInScene.reserve(20);
	sceneName = i_sceneName;
	render = false;
	renderDebug = true;
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
	for (std::vector<SharedPointer<MeshObject>>::iterator i = mMeshObjectInSceneList.begin();
	i != mMeshObjectInSceneList.end(); ++i)
		i->deleteObject();

}

template<typename T>
bool Engine::Scene::addObjectToScene(SharedPointer<T> & i_game_object)
{
	return false;
}

template<>
bool Engine::Scene::addObjectToScene<Engine::MeshObject>(
	SharedPointer<MeshObject> & iMeshObject)
{
	if (!iMeshObject.isNull())
	{
		mMeshObjectInSceneList.push_back(iMeshObject);
		return true;
	}
	return false;
}

template<>
bool Engine::Scene::addObjectToScene<Engine::Graphics::Line>(
	SharedPointer<Engine::Graphics::Line> & iLine)
{
	if (!iLine.isNull())
	{
		mLineListInScene.push_back(iLine);
		return true;
	}
	return false;
}

template<>
bool Engine::Scene::addObjectToScene<Engine::Graphics::Sprite>(
	SharedPointer<Engine::Graphics::Sprite> & iSprite)
{
	if (!iSprite.isNull())
	{
		mSpriteListInScene.push_back(iSprite);
		return true;
	}
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


void Engine::Scene::drawScene(bool withDebug)
{
	Engine::SharedPointer<Engine::Graphics::SkyBox> tempSkyBox =
		Engine::Graphics::SkyBox::getSkyBox();
	if(!tempSkyBox.isNull() && tempSkyBox->isSkyBoxAvailableIntialized())
	{
		tempSkyBox->draw(true);
	}

	for (int i = 0; i < mMeshObjectInSceneList.size(); i++)
		mMeshObjectInSceneList[i]->draw(withDebug);

	for (int i = 0; i < mSpriteListInScene.size(); i++)
		mSpriteListInScene[i]->draw(withDebug);

	if (Engine::Graphics::Line::containsDebugLine())
		Engine::Graphics::Line::drawLines(withDebug);

	mTimer->updateDeltaTime();
}

void Engine::Scene::applyPaintersAlgorithmForTransparency()
{
	SharedPointer<Scene> activeScene = getRenderableScene();
	std::sort(activeScene->mMeshObjectInSceneList.begin(), activeScene->mMeshObjectInSceneList.end(), sortingFunc);
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
		for (std::vector<SharedPointer<MeshObject>>::iterator j = i->second->mMeshObjectInSceneList.begin();
		j != i->second->mMeshObjectInSceneList.end(); ++j)
			j->deleteObject();
		for (std::vector<SharedPointer<Graphics::Sprite>>::iterator j = i->second->mSpriteListInScene.begin();
		j != i->second->mSpriteListInScene.end(); ++j)
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












