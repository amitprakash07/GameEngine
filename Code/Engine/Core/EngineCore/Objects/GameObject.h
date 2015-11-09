#ifndef __GAMEOBJECT_H
#define __GAMEOBJECT_H

#include "../../../Graphics/Mesh.h"
#include "../../../Graphics/Effect.h"
#include "../../../Core/Utilities/SharedPointer.h"
#include "../../../Core/Maths/cVector.h"
#include "../../../Core/Maths/cQuaternion.h"
#include "../../Utilities/IObjectController.h"
#include "../../../Core/Utilities/IMessageHandler.h"


namespace Engine
{
	
	class GameObject : public IMessageHandler
	{
	public:
		struct Transformation
		{
			Engine::Math::cVector mPositionOffset;
			Engine::Math::cQuaternion mOrientation;
			Transformation()
			{
				mPositionOffset = Math::cVector();
				mOrientation = Math::cQuaternion();
			}
		};
		static SharedPointer<GameObject> CreateGameObject(std::string, std::string, std::string, std::string);
		void setGameObjectController(IObjectController *);
		SharedPointer<Engine::Graphics::Mesh>       getMesh();
		SharedPointer<Engine::Graphics::Effect>		getEffect();
		void setTransformation(Engine::Math::cVector, Engine::Math::cQuaternion = Engine::Math::cQuaternion());
		Transformation getTransformation();	
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
		Transformation								mTransformation;
	};
}

#endif