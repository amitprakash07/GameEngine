#ifndef __GAMEOBJECT_H
#define __GAMEOBJECT_H

#include "../../Graphics/Mesh.h"
#include "../../Graphics/Effect.h"
#include "../Utilities/SharedPointer.h"
#include "../Maths/cVector.h"
#include "../MessagingSystem/IMessageHandler.h"

namespace Engine
{
	class GameObject: public IMessageHandler
	{
	public:
		SharedPointer<Engine::Graphics::Mesh>       getMesh();
		SharedPointer<Engine::Graphics::Effect>		getEffect();
		GameObject(SharedPointer<Engine::Graphics::Mesh>, SharedPointer<Engine::Graphics::Effect>);
		void HandleMessage(Engine::utils::StringHash &, void *i_MessageSender, void* i_pMessageData) override;
		bool isRenderable();
	private:
		SharedPointer<Engine::Graphics::Mesh>		mMesh;
		SharedPointer<Engine::Graphics::Effect>		mEffect;
		bool										renderable;
		Engine::Math::cVector						mPositionOffset;
	};
}

#endif