#include "SkyBox.h"
#include "../Graphics/Material.h"
#include "../Core/EngineCore/EngineCore.h"
#include "../../Engine/Core/Utilities/IObjectController.h"


std::map<std::string, Engine::SharedPointer<Engine::Graphics::SkyBox>>
Engine::Graphics::SkyBox::mSkyBoxList;
bool Engine::Graphics::SkyBox::isSkyBoxAvailable = false;


Engine::SharedPointer<Engine::Graphics::SkyBox>
	Engine::Graphics::SkyBox::CreateSkyBox(std::string i_materialName)
{
	if (!isSkyBoxExist(i_materialName))
	{
		i_materialName = Engine::EngineCore::getMaterialFolderPath() + i_materialName;
		SharedPointer<SkyBox> tempSkyBox =
			SharedPointer<SkyBox>(new SkyBox(i_materialName), "Engine::Graphics::SkyBox");
		Engine::Graphics::Material::addMaterialToList(i_materialName.c_str());
		Engine::utils::StringHash temp(Engine::EngineCore::getStringPool()->findString("UpdateObject"));
		Engine::EngineCore::getMessagingSystem()->addMessageHandler(temp, 
			static_cast<IMessageHandler*>(tempSkyBox.getRawPointer()), Engine::typedefs::HIGH);
		mSkyBoxList[i_materialName] = tempSkyBox;
		if (tempSkyBox->createBuffer())
		{
			tempSkyBox->isSkyBoxAvailable = true;
			tempSkyBox->isCurrent = false;
			return tempSkyBox;
		}
		return SharedPointer<SkyBox>();
	}
	return getSkyBox(i_materialName);
}

Engine::SharedPointer<Engine::Graphics::SkyBox> Engine::Graphics::SkyBox::getSkyBox(int index)
{
	int counter = 1;
	for (std::map<std::string, SharedPointer<SkyBox>>::iterator i = mSkyBoxList.begin();
	i != mSkyBoxList.end(); ++i)
	{		
		if (index == counter)
			return i->second;
		counter++;		
	}
	return SharedPointer<SkyBox>();
}


void Engine::Graphics::SkyBox::nextSkyBox()
{
	int count = 0;
	if(mSkyBoxList.size()>1)
	{
		for (std::map<std::string, SharedPointer<SkyBox>>::iterator i = mSkyBoxList.begin();
		i != mSkyBoxList.end(); ++i)
		{
			count++;
			if(i->second->isCurrent)
			{
				if(count <= mSkyBoxList.size())
				{
					if (count == mSkyBoxList.size())
					{
						count = 1;
						getSkyBox(count)->setCurrentSkyBox();
					}
					else
						getSkyBox(count+1)->setCurrentSkyBox();
					break;
				}
			}			
		}
	}
}


Engine::SharedPointer<Engine::Graphics::SkyBox> Engine::Graphics::SkyBox::getSkyBox(std::string i_materialName)
{
	if(isSkyBoxExist(i_materialName))
	{
		for (std::map<std::string, SharedPointer<SkyBox>>::iterator i = mSkyBoxList.begin();
		i != mSkyBoxList.end(); ++i)
		{
			if (i->first == i_materialName)
				return i->second;
		}
	}
	return SharedPointer<SkyBox>();
}


bool Engine::Graphics::SkyBox::isSkyBoxExist(std::string materialName)
{
	for (std::map<std::string, SharedPointer<SkyBox>>::iterator i = mSkyBoxList.begin();
	i != mSkyBoxList.end(); ++i)
	{
		if (i->first == materialName)
			return true;
	}
	return false;
}


bool Engine::Graphics::SkyBox::isSkyBoxAvailableIntialized() const
{
	return isSkyBoxAvailable;
}


void Engine::Graphics::SkyBox::setCurrentSkyBox()
{
	deactivateAll();
	isCurrent = true;
}


Engine::Math::Transform Engine::Graphics::SkyBox::getTransform()
{
	return stubTransform;
}

Engine::SharedPointer<Engine::Graphics::SkyBox> 
	Engine::Graphics::SkyBox::getCurrentSkyBox()
{
	for (std::map<std::string, SharedPointer<SkyBox>>::iterator i = mSkyBoxList.begin();
	i!=mSkyBoxList.end();++i)
	{
		if (i->second->isCurrent)
			return i->second;
	}
	return SharedPointer<SkyBox>();
}


void Engine::Graphics::SkyBox::deactivateAll()
{
	for (std::map<std::string, SharedPointer<SkyBox>>::iterator i = mSkyBoxList.begin();
	i != mSkyBoxList.end(); ++i)
	{
		i->second->isCurrent = false;
	}
}




bool Engine::Graphics::SkyBox::isDebugObject() const
{
	return false;
}

void Engine::Graphics::SkyBox::setMaterial(std::string newMaterialName)
{
	mMaterialName = newMaterialName;
}

bool Engine::Graphics::SkyBox::isRenderable() const
{
	return true;
}

void Engine::Graphics::SkyBox::setTransform(Math::Vector3, Math::Quaternion)
{
	
}

void Engine::Graphics::SkyBox::resetTransform()
{
	
}

void Engine::Graphics::SkyBox::setObjectController(IObjectController* i_ObjectController)
{
	if (mObjectController)
		mObjectController = i_ObjectController;
}


void Engine::Graphics::SkyBox::updateObject()
{
	typedefs::ActionWithKeyBound action;
	action.action = typedefs::Default;
	action.keyVal = 0x00;
	if (mObjectController)
		mObjectController->updateObject(*this, action);
}


void Engine::Graphics::SkyBox::HandleMessage(Engine::utils::StringHash& i_message,
	RTTI* i_MessageSender, void* i_pMessageData)
{
	if (i_MessageSender != nullptr)
	{
		if (i_MessageSender != nullptr && Engine::utils::StringHash("UpdateObject") == i_message && mObjectController)
			mObjectController->updateObject(*this, *reinterpret_cast<Engine::typedefs::ActionWithKeyBound*>(i_pMessageData));
	}
}

void Engine::Graphics::SkyBox::enableCollision(bool)
{
	//Nothing to do	- stub
}

void Engine::Graphics::SkyBox::enablePhysics(bool)
{
	//Stub
}

bool Engine::Graphics::SkyBox::isCollidable()
{
	return false;
}

bool Engine::Graphics::SkyBox::isPhysicsEnabled()
{
	return false;
}

void Engine::Graphics::SkyBox::receiveShadow(bool)
{
	//Stub
}

bool Engine::Graphics::SkyBox::receivingShadowEnabled()
{
	return false;
}

void Engine::Graphics::SkyBox::castShadow(bool, Graphics::ShadowMethod)
{
	//Stub
}

bool Engine::Graphics::SkyBox::castingShadowEnabled()
{
	return false;
}


Engine::ObjectType Engine::Graphics::SkyBox::getObjectType()
{
	return mObjectType;
}

void Engine::Graphics::SkyBox::setObjectType(ObjectType iObjectType)
{
	mObjectType = iObjectType;
}




























