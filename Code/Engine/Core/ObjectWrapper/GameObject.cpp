#include "GameObject.h"
#include "../EngineCore/EngineCore.h"
#include "../EngineCore/additionaltypes.h"
#include "../Utilities/HashedString.h"


Engine::GameObject::GameObject(SharedPointer<Engine::Graphics::Mesh> i_mesh, SharedPointer<Engine::Graphics::Effect> i_effect)
{
	if (!i_mesh.isNull())
		mMesh = i_mesh;
	if (!i_effect.isNull())
		mEffect = i_effect;
	renderable = true;
	mPositionOffset.x = 0.0f;
	mPositionOffset.y = 0.0f;
	mPositionOffset.z = 0.0f;
	setTypeInfo("Engine::GameObject");
	Engine::utils::StringHash temp(Engine::EngineCore::getStringPool()->findString("UpdateGameObject"));
	Engine::EngineCore::getMessagingSystem()->addMessageHandler(temp, this, Engine::typedefs::HIGH);
}

Engine::SharedPointer<Engine::Graphics::Mesh> Engine::GameObject::getMesh()
{
	return mMesh;
}

Engine::SharedPointer<Engine::Graphics::Effect> Engine::GameObject::getEffect()
{
	return mEffect;
}

bool Engine::GameObject::isRenderable()
{
	return renderable;
}

void Engine::GameObject::setOffset(Engine::Math::cVector i_positionOffset)
{
	mPositionOffset = i_positionOffset;
}

void Engine::GameObject::HandleMessage(Engine::utils::StringHash& i_message, RTTI* i_MessageSender, void* i_pMessageData)
{
	if(i_MessageSender)
	{
		if(Engine::EngineCore::getInputController().isBothSameType(i_MessageSender) && (Engine::utils::StringHash("UpdateGameObject") == i_message))
		{
			Engine::SharedPointer<Engine::GameObject> temp(this);
			switch(*(reinterpret_cast<Engine::typedefs::Direction*>(i_pMessageData)))
			{
			case Engine::typedefs::UP:
				mObjectController->updateGameObject(temp, Engine::typedefs::UP);
				break;
			case Engine::typedefs::DOWN:
				mObjectController->updateGameObject(temp, Engine::typedefs::DOWN);
				break;
			case Engine::typedefs::LEFT:
				mObjectController->updateGameObject(temp, Engine::typedefs::LEFT);
				break;
			case Engine::typedefs::RIGHT:
				mObjectController->updateGameObject(temp, Engine::typedefs::RIGHT);
				break;
			}			
		}
	}
}

Engine::Math::cVector Engine::GameObject::getOffsetPosition()
{
	return mPositionOffset;
}









