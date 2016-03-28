#ifndef __GAMEOBJECT_H
#define __GAMEOBJECT_H

#include "../../../Graphics/Mesh.h"
#include "../../../Graphics/Material.h"
#include "../../../Core/Utilities/SharedPointer.h"
#include "../../Utilities/IObjectController.h"
#include "../../../Core/Utilities/IMessageHandler.h"
#include "Object.h"
#include "../../../Graphics/typedefs.h"


namespace Engine
{
	class MeshObject : public IMessageHandler, Object
	{
	public:
		static SharedPointer<MeshObject> CreateMeshObject(std::string, std::string, Engine::Graphics::RGBAColor = {1.0f,1.0f,1.0f,1.0f});
		void setObjectController(IObjectController *)override;
		SharedPointer<Engine::Graphics::Mesh>       getMesh() const;
		SharedPointer<Engine::Graphics::Effect>		getEffect() const;
		SharedPointer<Engine::Graphics::Material>   getMaterial() const;
		void setTransform(Engine::Math::Vector3, Engine::Math::Quaternion = Engine::Math::Quaternion()) override;
		Math::Transform getTransform() override;
		bool isRenderable() const override;
		void HandleMessage(Engine::utils::StringHash &, RTTI* i_MessageSender, void* i_pMessageData) override;
		void draw(bool drawDebugObject) override;
		std::string getTypeInfo() const override { return ""; }
		bool isBothSameType(RTTI*, std::string) const override { return true; }
		void EnableDebugging(bool enable = false);
		bool isDebugObject() const override;	
		void updateObject() override;
		void setScale(float x = 1.0f, float y = 1.0f, float z = 1.0f) override;
		void resetTransform() override;
		std::string getMaterialName() override { return mMaterial; }
		bool isCollidable() override;
		bool isPhysicsEnabled() override;
		void enableCollision(bool) override;
		void enablePhysics(bool) override;
		void castShadow(bool, Graphics::ShadowMethod) override;
		bool castingShadowEnabled() override;
		void receiveShadow(bool) override;
		bool receivingShadowEnabled() override;
		~MeshObject();
	private:
		MeshObject(std::string, std::string);
		MeshObject();
		std::string									mMeshName;
		std::string									mMaterial;
		std::string									vertexModifierUniform;
		IObjectController*							mObjectController;
		bool										renderable;
		Math::Transform								mTransform;
		Math::Transform								mInitialTransform;
		bool										isInitialTransform;
		Math::Vector3								scaleFactor;
		bool										debugObject;
		Engine::Graphics::RGBAColor					vertexColor;
		
	};
}

#endif