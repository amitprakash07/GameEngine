#include "Scene.h"
#include "../../../Graphics/Effect.h"
#include "../../../Graphics/Mesh.h"
#include "../../../Windows/WindowsFunctions.h"

std::map<std::string, Engine::SharedPointer<Engine::Scene>> Engine::Scene::mSceneList;

Engine::Scene::Scene(std::string i_sceneName):
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
	for (std::vector<SharedPointer<GameObject>>::iterator i = mScene.begin(); i != mScene.end(); ++i)
		i->deleteObject();
	
}

bool Engine::Scene::addGameObjectToScene(SharedPointer<GameObject> & i_game_object)
{
	if(!i_game_object.isNull())
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
		mCameraList.push_back(i_camera);
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
	SharedPointer<Camera> tempCamera = getActiveCamera();
	if (!tempCamera.isNull())
	{	Transformation cameraTransformation = tempCamera->getTransformation();
		float fieldOfView = tempCamera->getFieldOfView();
		float aspectRatio = tempCamera->getAspectRatio();
		for (std::vector<SharedPointer<Engine::GameObject>>::iterator i = mScene.begin(); i != mScene.end(); ++i)
		{
			(*i)->getEffect()->setShaders();
			//(*i)->getEffect()->setPositionOffset((*i)->getOffsetPosition());
			Transformation gameObjectTransformation = (*i)->getTransformation();
			(*i)->getEffect()->setEngineUniformValue(gameObjectTransformation, cameraTransformation, fieldOfView, aspectRatio);
			//(*i)->getEffect()->setMaterialUniformValue();
			(*i)->getMaterial()->setMaterialUniformParameters();
			(*i)->getMesh()->drawMesh();
		}
		mTimer->updateDeltaTime();
		std::stringstream errormessage;
	}
	else
	{
		std::stringstream errormessage;
		errormessage << "Camera is not iniitalized\n";
		WindowsUtil::Print(errormessage.str().c_str());
		return;
	}

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
		for (std::vector<SharedPointer<GameObject>>::iterator j = i->second->mScene.begin(); j != i->second->mScene.end(); ++j)
			j->deleteObject();
	}
}

Engine::SharedPointer<Engine::Camera> Engine::Scene::getActiveCamera()
{
	for (size_t i = 0; i < mCameraList.size(); ++i)
	{
		if (mCameraList[i]->isActive())
			return mCameraList[i];
	}
	return SharedPointer<Camera>();
}








