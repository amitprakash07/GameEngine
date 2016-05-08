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
		static SharedPointer<MeshObject> CreateMeshObject(std::string, std::string, 
			Engine::Graphics::RGBAColor = {1.0f,1.0f,1.0f,1.0f});
		void setObjectController(IObjectController *)override;
		SharedPointer<Engine::Graphics::Mesh>       getMesh() const;
		SharedPointer<Engine::Graphics::Effect>		getEffect() const;
		SharedPointer<Engine::Graphics::Material>   getMaterial() const;
		void setTransform(Engine::Math::Vector3, Engine::Math::Quaternion = Engine::Math::Quaternion()) override;
		Math::Transform getTransform() override;
		bool isRenderable() const override;
		void HandleMessage(Engine::utils::StringHash &, RTTI* i_MessageSender, void* i_pMessageData) override;
		void draw(bool drawDebugObject) override;
		bool IsPlayer() override;
		void setPlayer(bool i_isPlayer) override;
		std::string getTypeInfo() const override { return ""; }
		bool isBothSameType(RTTI*, std::string) const override { return true; }
		void EnableDebugging(bool enable = false);
		bool isDebugObject() const override;	
		void updateObject() override;
		void setScale(float x = 1.0f, float y = 1.0f, float z = 1.0f) override;
		Math::Vector3 getScale() const override;
		void setRenderable(bool iRenderable) override{ renderable = iRenderable; }
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
		void setObjectType(ObjectType iObjectType) override;
		ObjectType getObjectType() override;
		Graphics::RGBAColor GetVertexColor() const override;
		void SetVertexColor(float iR, float iG, float iB, float iA) override;
		void SetMaterial(std::string iMaterialName) override;
		bool isSSAOEnabled() override;
		void EnableSSAO(bool iRequest) override;
		~MeshObject();
		MeshObject();
	private:
		MeshObject(std::string, std::string);		
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
		bool										isPlayer;
		ObjectType									mObjectType;
		bool										isSSAO;
	};
}

#endif