#ifndef __GAMEOBJECT_H
#define __GAMEOBJECT_H

#include "../../../Graphics/Mesh.h"
#include "../../../Graphics/Material.h"
#include "../../../Core/Utilities/SharedPointer.h"
#include "../../Utilities/IObjectController.h"
#include "../../../Core/Utilities/IMessageHandler.h"
#include "Object.h"


namespace Engine
{
	
	class GameObject : public IMessageHandler, Object
	{
	public:
		static SharedPointer<GameObject> CreateGameObject(std::string, std::string);
		void setGameObjectController(IObjectController *);
		SharedPointer<Engine::Graphics::Mesh>       getMesh();
		SharedPointer<Engine::Graphics::Effect>		getEffect();
		SharedPointer<Engine::Graphics::Material>   getMaterial();
		void setTransformation(Engine::Math::cVector, Engine::Math::cQuaternion = Engine::Math::cQuaternion()) override;
		Transformation getTransformation() override;	
		bool isRenderable();
		void HandleMessage(Engine::utils::StringHash &, RTTI* i_MessageSender, void* i_pMessageData) override;
		std::string getTypeInfo() override { return ""; }
		bool isBothSameType(RTTI*, std::string) override { return true; }
		GameObject();
		~GameObject();
	private:
		GameObject(std::string, std::string);
		std::string									mMeshName;
		std::string									mMaterial;
		IObjectController*							mObjectController;
		bool										renderable;
		Transformation								mTransformation;
	};
}

#endif