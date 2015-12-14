#include "GameObject.h"
#include "../../../Core/Utilities/HashedString.h"
#include "../../../Windows/WindowsFunctions.h"
#include "../../../Core/EngineCore/EngineCore.h"




Engine::SharedPointer<Engine::GameObject> Engine::GameObject::CreateGameObject(std::string i_meshFileName, std::string i_materialName)
{
	i_meshFileName = Engine::EngineCore::getMeshFolderPath() + i_meshFileName;
	i_materialName = Engine::EngineCore::getMaterialFolderPath() + i_materialName;
	SharedPointer<GameObject> tempGameObject(new GameObject(i_meshFileName, i_materialName), "Engine::GameObject");
	Engine::utils::StringHash temp(Engine::EngineCore::getStringPool()->findString("UpdateGameObject"));
	Engine::EngineCore::getMessagingSystem()->addMessageHandler(temp, reinterpret_cast<IMessageHandler*>(tempGameObject.getRawPointer()), Engine::typedefs::HIGH);

	if (!i_meshFileName.empty() && !i_meshFileName.empty() && !i_materialName.empty())
	{
		std::stringstream errormessage;

		if (!Engine::Graphics::Material::addMaterialToList(i_materialName.c_str()))
		{
			errormessage << "Unable to Load Effect";
			MessageBox(nullptr, errormessage.str().c_str(), nullptr, MB_OK);
			tempGameObject.deleteObject();
			return (SharedPointer<GameObject>());
		}

		if (!Engine::Graphics::Mesh::addToMeshList(i_meshFileName))
		{
			errormessage << "Unable to Load Mesh";
			MessageBox(nullptr, errormessage.str().c_str(), nullptr, MB_OK);
			tempGameObject.deleteObject();
			return (SharedPointer<GameObject>());
		}
		
		
	}
	return tempGameObject;
}

Engine::GameObject::GameObject(std::string i_meshName, std::string i_materialName)
{
	renderable = true;
	mTransformation = Transformation();
	mMeshName = i_meshName;
	mMaterial = i_materialName;
	mObjectController = nullptr;
}

Engine::GameObject::GameObject()
{
	renderable = true;
	mMeshName = "";
	mMaterial = "";
	mObjectController = nullptr;
	mTransformation.mOrientation = Engine::Math::cQuaternion();
	mTransformation.mPositionOffset = Engine::Math::cVector();
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
	return Engine::Graphics::Effect::getEffect(Engine::Graphics::Material::getMaterial(mMaterial.c_str())->getEffectName());
}

Engine::SharedPointer<Engine::Graphics::Material> Engine::GameObject::getMaterial()
{
	return Engine::Graphics::Material::getMaterial(mMaterial.c_str());
}


bool Engine::GameObject::isRenderable()
{
	return renderable;
}

void Engine::GameObject::setTransformation(Engine::Math::cVector i_positionOffset, Engine::Math::cQuaternion i_orientation)
{
	mTransformation.mOrientation = i_orientation;
	mTransformation.mPositionOffset = i_positionOffset;
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

Engine::Transformation Engine::GameObject::getTransformation()
{
	return mTransformation;
}

Engine::GameObject::~GameObject()
{
	if(mObjectController)
		delete mObjectController;
}










