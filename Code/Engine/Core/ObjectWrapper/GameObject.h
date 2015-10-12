#ifndef __GAMEOBJECT_H
#define __GAMEOBJECT_H

#include "../../Graphics/Mesh.h"
#include "../../Graphics/Effect.h"
#include "../Utilities/SharedPointer.h"
#include "../Maths/cVector.h"
#include "IObjectController.h"
#include "../MessagingSystem/IMessageHandler.h"
#include "../EngineCore/RTTI.h"


namespace Engine
{
	class GameObject : public IMessageHandler, public RTTI
	{
	public:
		SharedPointer<Engine::Graphics::Mesh>       getMesh();
		SharedPointer<Engine::Graphics::Effect>		getEffect();
		GameObject(SharedPointer<Engine::Graphics::Mesh>, SharedPointer<Engine::Graphics::Effect>);
		void setOffset(Engine::Math::cVector);
		Engine::Math::cVector getOffsetPosition();
		bool isRenderable();
		void HandleMessage(Engine::utils::StringHash &, RTTI *i_MessageSender, void* i_pMessageData) override;
	private:
		SharedPointer<Engine::Graphics::Mesh>		mMesh;
		SharedPointer<Engine::Graphics::Effect>		mEffect;
		SharedPointer<IObjectController>			mObjectController;
		bool										renderable;
		Engine::Math::cVector						mPositionOffset;
	};
}

#endif