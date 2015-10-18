#ifndef __GAMEOBJECT_H
#define __GAMEOBJECT_H

#include "../../../Graphics/Mesh.h"
#include "../../../Graphics/Effect.h"
#include "../../../Core/Utilities/SharedPointer.h"
#include "../../../Core/Maths/cVector.h"
#include "../../Utilities/IObjectController.h"
#include "../../../Core/Utilities/IMessageHandler.h"


namespace Engine
{
	class GameObject : public IMessageHandler
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
		std::string getTypeInfo() override { return ""; }
		bool isBothSameType(RTTI*, std::string) override { return true; }
		GameObject();
		~GameObject();
	private:
		GameObject(std::string, std::string);
		std::string									mMeshName;
		std::string									mEffectName;
		IObjectController*							mObjectController;
		bool										renderable;
		Engine::Math::cVector						mPositionOffset;
	};
}

#endif