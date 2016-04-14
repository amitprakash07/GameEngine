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
	mReflectingObjectList.reserve(20);
	mPlaneList.reserve(20);
	mLightList.reserve(10);
	sceneName = i_sceneName;
	render = false;
	renderDebug = true;
	mObjectController = nullptr;
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

//MeshObjects
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


//Lines
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


//Sprites
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


//Planes
template<>
bool Engine::Scene::addObjectToScene<Engine::Graphics::Plane>(
	SharedPointer<Engine::Graphics::Plane> & iPlane)
{
	if (!iPlane.isNull())
	{
		mPlaneList.push_back(iPlane);
		return true;
	}
	return false;
}


//Reflecting Objects - Environment Maps
template<>
bool Engine::Scene::addObjectToScene<Engine::Graphics::ReflectingObject>(
	SharedPointer<Engine::Graphics::ReflectingObject> & iReflectingObject)
{
	if (!iReflectingObject.isNull())
	{
		mReflectingObjectList.push_back(iReflectingObject);
		return true;
	}
	return false;
}

//Camera
bool Engine::Scene::addCameraToScene(SharedPointer<Camera>& i_camera)
{
	if (!i_camera.isNull())
	{
		mCameraListInScene[i_camera->getCameraName()] = i_camera;
		return true;
	}
	return false;
}

//Light
bool Engine::Scene::addLightToScene(SharedPointer<Graphics::Light>& iLight)
{
	if(!iLight.isNull())
	{
		mLightList.push_back(iLight);
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
	if(mLightList.size()>0)
	{
		for (std::vector<SharedPointer<Graphics::Light>>::iterator iL = mLightList.begin();
		iL!=mLightList.end(); ++iL)
		{
			(*iL)->setLightParameterValueToShaderObject();
		}
	}
	//Generate dynamic Cube Maps
	if(mReflectingObjectList.size()>0)
	{
		sortAllReflectingObjects();
		for (uint8_t i = 0; i < mReflectingObjectList.size(); i++)
		{
			mReflectingObjectList[i]->generateCubeMap();
		}
	}

	Engine::SharedPointer<Engine::Graphics::SkyBox> tempSkyBox =
		Engine::Graphics::SkyBox::getCurrentSkyBox();
	if(!tempSkyBox.isNull() && tempSkyBox->isSkyBoxAvailableIntialized())
	{
		tempSkyBox->draw(true);
	}

	for (uint8_t i = 0; i < mMeshObjectInSceneList.size(); i++)
		mMeshObjectInSceneList[i]->draw(withDebug);

	for (uint8_t i = 0; i < mPlaneList.size(); i++)
		mPlaneList[i]->draw(withDebug);

	if (Engine::Graphics::Line::containsDebugLine())
		Engine::Graphics::Line::drawLines(withDebug);

	
	//Draw the environment mapping reflecting Objects
	if (mReflectingObjectList.size()>0)
	{
		for (uint8_t i = 0; i < mReflectingObjectList.size(); i++)
		{
			mReflectingObjectList[i]->draw(true);
		}
	}

	for (uint8_t i = 0; i < mSpriteListInScene.size(); i++)
		mSpriteListInScene[i]->draw(withDebug);

	mTimer->updateDeltaTime();
	updateScene();
}



void Engine::Scene::updateScene()
{
	if (mReflectingObjectList.size()>0)
	{
		for (uint8_t i = 0; i < mReflectingObjectList.size(); i++)
		{
			mReflectingObjectList[i]->updateObject();
		}
	}

	Engine::SharedPointer<Engine::Graphics::SkyBox> tempSkyBox =
		Engine::Graphics::SkyBox::getCurrentSkyBox();
	if (!tempSkyBox.isNull() && tempSkyBox->isSkyBoxAvailableIntialized())
	{
		tempSkyBox->updateObject();
	}

	for (uint8_t i = 0; i < mMeshObjectInSceneList.size(); i++)
		mMeshObjectInSceneList[i]->updateObject();

	for (uint8_t i = 0; i < mSpriteListInScene.size(); i++)
		mSpriteListInScene[i]->updateObject();

	//Draw the environment mapping reflecting Objects
	if (mReflectingObjectList.size()>0)
	{
		for (uint8_t i = 0; i < mReflectingObjectList.size(); i++)
		{
			mReflectingObjectList[i]->updateObject();
		}
	}
}

void Engine::Scene::applyPaintersAlgorithmForTransparency()
{
	SharedPointer<Scene> activeScene = getRenderableScene();
	std::sort(activeScene->mMeshObjectInSceneList.begin(), 
		activeScene->mMeshObjectInSceneList.end(), sortMeshObject);
}

void Engine::Scene::sortAllReflectingObjects()
{
	SharedPointer<Scene> activeScene = getRenderableScene();
	std::sort(activeScene->mReflectingObjectList.begin(), 
		activeScene->mReflectingObjectList.end(), sortReflectingObject);
}


std::vector<Engine::SharedPointer<Engine::MeshObject>> 
	Engine::Scene::getMeshObjectList() const
{
	return mMeshObjectInSceneList;
}

std::vector<Engine::SharedPointer<Engine::Graphics::Sprite>> 
	Engine::Scene::getSpriteObjectList() const
{
	return mSpriteListInScene;
}


std::vector<Engine::SharedPointer<Engine::Graphics::Line>> 
	Engine::Scene::getLineList() const
{
	return mLineListInScene;
}


std::vector<Engine::SharedPointer<Engine::Graphics::ReflectingObject>> 
	Engine::Scene::getReflectingObjectList() const
{
	return mReflectingObjectList;
}


std::vector<Engine::SharedPointer<Engine::Graphics::Plane>> 
	Engine::Scene::getPlaneList() const
{
	return mPlaneList;
}


std::vector<Engine::SharedPointer<Engine::Graphics::Light>> 
	Engine::Scene::getLightList() const
{
	return mLightList;
}



bool Engine::Scene::sortMeshObject(
	SharedPointer<MeshObject> i_gameObjectOne,
	SharedPointer<MeshObject> i_gameObjectTwo)
{
	if (i_gameObjectOne->getTransform().getPosition().z <
		i_gameObjectTwo->getTransform().getPosition().z)
		return true;
	return false;
}


bool Engine::Scene::sortSprites(
	SharedPointer<Engine::Graphics::Sprite> i_gameObjectOne,
	SharedPointer<Engine::Graphics::Sprite> i_gameObjectTwo)
{
	if (i_gameObjectOne->getTransform().getPosition().z <
		i_gameObjectTwo->getTransform().getPosition().z)
		return true;
	return false;
}


bool Engine::Scene::sortReflectingObject(
	SharedPointer<Engine::Graphics::ReflectingObject> i_gameObjectOne,
	SharedPointer<Engine::Graphics::ReflectingObject> i_gameObjectTwo)
{
	if (i_gameObjectOne->getTransform().getPosition().z <
		i_gameObjectTwo->getTransform().getPosition().z)
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


void Engine::Scene::updateObject()
{
	typedefs::ActionWithKeyBound action;
	action.action = typedefs::Default;
	action.keyVal = 0x00;
	if (mObjectController)
		mObjectController->updateObject(*this, action);
}

void Engine::Scene::setScale(float x, float y, float z)
{
	//Need to implement Later
}



void Engine::Scene::setObjectController(IObjectController* iObjectController)
{
	if (iObjectController)
		mObjectController = iObjectController;
}


void Engine::Scene::HandleMessage(Engine::utils::StringHash& i_message,
	RTTI* i_MessageSender, 
	void* i_pMessageData)
{
	if (i_MessageSender != nullptr)
	{
		if (i_MessageSender != nullptr && Engine::utils::StringHash("UpdateObject") == i_message && mObjectController)
			mObjectController->updateObject(*this, *reinterpret_cast<Engine::typedefs::ActionWithKeyBound*>(i_pMessageData));
	}
}


bool Engine::Scene::isCollidable()
{
	return false;
}

bool Engine::Scene::isPhysicsEnabled()
{
	return false;
}

void Engine::Scene::enableCollision(bool)
{
	//Stub
}

void Engine::Scene::enablePhysics(bool)
{
	//Stub
}

void Engine::Scene::receiveShadow(bool)
{
	//Stub
}

bool Engine::Scene::receivingShadowEnabled()
{
	return false;
}


void Engine::Scene::castShadow(bool, Graphics::ShadowMethod)
{
	//Stub
}

bool Engine::Scene::castingShadowEnabled()
{
	return false;
}























