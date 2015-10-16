#ifndef __GAMEOBJECT_H
#define __GAMEOBJECT_H

#include "../../../Graphics/Mesh.h"
#include "../../../Graphics/Effect.h"
#include "../../../Core/Utilities/SharedPointer.h"
#include "../../../Core/Maths/cVector.h"
#include "../ObjectController/IObjectController.h"
#include "../../../Core/MessagingSystem/IMessageHandler.h"
#include "../../../Core/Utilities/RTTI.h"


namespace Engine
{
	class GameObject : public IMessageHandler, public RTTI
	{
	public:
		static SharedPointer<GameObject> CreateGameObject(std::string, std::string, std::string, std::string, std::string);
		void setGameObjectController(IObjectController *);
		SharedPointer<Engine::Graphics::Mesh>       getMesh();
		SharedPointer<Engine::Graphics::Effect>		getEffect();
		void setPositionOffset(Engine::Math::cVector);
		Engine::Math::cVector getOffsetPosition();
		bool isRenderable();
		void HandleMessage(Engine::utils::StringHash &, RTTI* i_MessageSender, void* i_pMessageData) override;
		std::string getTypeInfo() override;
		bool isBothSameType(SharedPointer<RTTI>, std::string) override;
		GameObject();
		~GameObject();
	private:
		GameObject(std::string, std::string);
		std::string									mMeshName;
		std::string									mEffectName;
		IObjectController*							mObjectController;
		bool										renderable;
		Engine::Math::cVector						mPositionOffset;
		std::string mTypeInfo;
	};
}

#endif