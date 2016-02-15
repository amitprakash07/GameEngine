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
	class MeshObject : public IMessageHandler, Object
	{
	public:
		static SharedPointer<MeshObject> CreateMeshObject(std::string, std::string);
		void setObjectController(IObjectController *);
		SharedPointer<Engine::Graphics::Mesh>       getMesh() const;
		SharedPointer<Engine::Graphics::Effect>		getEffect() const;
		SharedPointer<Engine::Graphics::Material>   getMaterial() const;
		void setTransformation(Engine::Math::cVector, Engine::Math::cQuaternion = Engine::Math::cQuaternion()) override;
		Transformation getTransformation() override;
		bool isRenderable() const override;
		void HandleMessage(Engine::utils::StringHash &, RTTI* i_MessageSender, void* i_pMessageData) override;
		void draw(bool drawDebugObject) override;
		std::string getTypeInfo() const override { return ""; }
		bool isBothSameType(RTTI*, std::string) const override { return true; }
		void EnableDebugging(bool enable = false);
		bool isDebugObject() const override;
		MeshObject();
		~MeshObject();
	private:
		MeshObject(std::string, std::string);
		std::string									mMeshName;
		std::string									mMaterial;
		IObjectController*							mObjectController;
		bool										renderable;
		Transformation								mTransformation;
		bool										debugObject;
	};
}

#endif