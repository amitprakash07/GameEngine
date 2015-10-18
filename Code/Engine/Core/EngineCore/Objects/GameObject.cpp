#include "GameObject.h"
#include "../../../Core/Utilities/HashedString.h"
#include "../../../Windows/WindowsFunctions.h"
#include "../../../Core/EngineCore/EngineCore.h"




Engine::SharedPointer<Engine::GameObject> Engine::GameObject::CreateGameObject(std::string i_meshName, std::string i_meshFileName, std::string i_effectName, std::string i_vertexShaderFileName, std::string i_fragmentShaderFileName)
{
	SharedPointer<GameObject> tempGameObject(new GameObject(i_meshName, i_effectName), "Engine::GameObject");
	Engine::utils::StringHash temp(Engine::EngineCore::getStringPool()->findString("UpdateGameObject"));
	Engine::EngineCore::getMessagingSystem()->addMessageHandler(temp, reinterpret_cast<IMessageHandler*>(tempGameObject.getRawPointer()), Engine::typedefs::HIGH);
	if (!i_meshName.empty() && !i_meshFileName.empty() && !i_effectName.empty() && !i_vertexShaderFileName.empty() && !i_fragmentShaderFileName.empty())
	{
		std::stringstream errormessage;
		if (!Engine::Graphics::Mesh::addToMeshList(i_meshName, i_meshFileName))
		{
			errormessage << "Unable to Load Mesh";
			MessageBox(nullptr, errormessage.str().c_str(), nullptr, MB_OK);
			tempGameObject.deleteObject();
			return (SharedPointer<GameObject>());
		}
		
		if(!Engine::Graphics::Effect::addEffectToList(i_effectName, i_vertexShaderFileName, i_fragmentShaderFileName))
		{
			errormessage << "Unable to Load Effect";
			MessageBox(nullptr, errormessage.str().c_str(), nullptr, MB_OK);
			tempGameObject.deleteObject();
			return (SharedPointer<GameObject>());
		}
	}
	return tempGameObject;
}

Engine::GameObject::GameObject(std::string i_meshName, std::string i_effectName)
{
	renderable = true;
	mPositionOffset.x = 0.0f;
	mPositionOffset.y = 0.0f;
	mPositionOffset.z = 0.0f;
	mMeshName = i_meshName;
	mEffectName = i_effectName;
	mObjectController = nullptr;
}

Engine::GameObject::GameObject()
{
	renderable = true;
	mPositionOffset.x = 0.0f;
	mPositionOffset.y = 0.0f;
	mPositionOffset.z = 0.0f;
	mMeshName = "";
	mEffectName = "";
	mObjectController = nullptr;
}



void Engine::GameObject::setGameObjectController(IObjectController* i_objectController)
{
	mObjectController = i_objectController;
}


Engine::SharedPointer<Engine::Graphics::Mesh> Engine::GameObject::getMesh()
{
	return Engine::Graphics::Mesh::getMesh(mMeshName);
}

Engine::SharedPointer<Engine::Graphics::Effect> Engine::GameObject::getEffect()
{
	return Engine::Graphics::Effect::getEffect(mEffectName);
}

bool Engine::GameObject::isRenderable()
{
	return renderable;
}

void Engine::GameObject::setPositionOffset(Engine::Math::cVector i_positionOffset)
{
	mPositionOffset = i_positionOffset;
}

void Engine::GameObject::HandleMessage(Engine::utils::StringHash& i_message, RTTI* i_MessageSender, void* i_pMessageData)
{
	if(i_MessageSender!=nullptr)
	{
		if(/*isBothSameType(i_MessageSender, Engine::InputController::getInputController()->getTypeInfo()) && (*/Engine::utils::StringHash("UpdateGameObject") == i_message)//)
		{
			//Engine::SharedPointer<Engine::GameObject> temp= SharedPointer<GameObject>(this); //Need to think about this
			switch(*(reinterpret_cast<Engine::typedefs::Direction*>(i_pMessageData)))
			{
			case Engine::typedefs::NONE:
				break;
			case Engine::typedefs::UP:
				if(mObjectController)
					mObjectController->updateGameObject(*this, Engine::typedefs::UP);
				break;
			case Engine::typedefs::DOWN:
				if (mObjectController)
					mObjectController->updateGameObject(*this, Engine::typedefs::DOWN);
				break;
			case Engine::typedefs::LEFT:
				if (mObjectController)
					mObjectController->updateGameObject(*this, Engine::typedefs::LEFT);
				break;
			case Engine::typedefs::RIGHT:
				if (mObjectController)
					mObjectController->updateGameObject(*this, Engine::typedefs::RIGHT);
				break;
			}			
		}
	}
}

Engine::Math::cVector Engine::GameObject::getOffsetPosition()
{
	return mPositionOffset;
}

Engine::GameObject::~GameObject()
{
	
}










