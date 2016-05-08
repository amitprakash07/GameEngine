#ifndef __LIGHT_H
#define __LIGHT_H

#include "../Core/Utilities/SharedPointer.h"
#include "typedefs.h"
#include "../Core/EngineCore/Objects/Object.h"
#include "../Core/Utilities/IMessageHandler.h"
#include "uniformdefs.h"
#include <vector>

namespace Engine
{
	namespace Graphics
	{
		class Light:public IMessageHandler, Engine::Object
		{
		public:
			static SharedPointer<Light> createLight(std::string iLightName, LightType iLightType);				
			void setLightParameterValueToShaderObject();
			void setIntensity(float iIntensity);
			void setColor(Math::Vector3 iColor);
			void setMeshName(std::string iMeshName, std::string iMaterialName);
			void enableShadow(bool enableShadow);
			std::string getName() const;
			void setRenderable(bool iRenderable) override { /*to-do*/ }
			bool isShadowCastingEnabled() const;
			float getLightIntensity() const;
			Engine::Math::Vector3 getLightColor()const;
			void addLightParameter(std::string iLightParameterName,
				DataTypes iLightParameterDataType, Data iParameterValue = Data());
			void setLightParameterValue(std::string iLightParameterName,
				DataTypes iLightParameterDataType, Data iParameterValue);
			void addLightToEffect(std::string iEffectFileName, ShaderType iShaderType);	
			void addLightToAllEffects(ShaderType iShaderType = Fragment);
			void removeLightFromEffect(std::string iEffectFileName, ShaderType iShaderType);
			void removeLightFromAllEffects(ShaderType iShaderType = Fragment);
			void enableLight(bool iRequest);

			//Object functions
			Math::Transform getTransform() override;
			void setTransform(Engine::Math::Vector3 iPosition, 
				Engine::Math::Quaternion iRotation) override;
			void resetTransform() override;
			void draw(bool drawable) override;
			bool isRenderable() const override;
			bool isDebugObject() const override;
			void updateObject() override;
			void setObjectController(IObjectController* iObjectController) override;
			void setScale(float iX, float iY, float iZ) override;
			Math::Vector3 getScale() const override { return Math::Vector3(0.0f);/*Stub*/ }
			Graphics::RGBAColor GetVertexColor() const override { return RGBAColor(0.0f); }
			void SetVertexColor(float iR, float iG, float iB, float iA) override{}
			std::string getMaterialName() override;
			bool isCollidable() override { return false; }
			bool isPhysicsEnabled() override { return false; }
			void enableCollision(bool) override {}
			void enablePhysics(bool) override {}
			void castShadow(bool, ShadowMethod) override{}
			bool castingShadowEnabled() override { return false; }
			void receiveShadow(bool) override {}
			bool receivingShadowEnabled() override { return false; }
			bool IsPlayer() override { return false; }
			void setPlayer(bool) override{};
			void setObjectType(ObjectType iObjectType) override;
			ObjectType getObjectType() override;
			void SetMaterial(std::string iMaterialName) override {}
			//IMessageHandler functions
			void HandleMessage(
				Engine::utils::StringHash &,
				RTTI* i_MessageSender, void* i_pMessageData) override;
			std::string getTypeInfo() const override;
			bool isBothSameType(RTTI*, std::string) const override;
			bool isSSAOEnabled() override { return false; }
			void EnableSSAO(bool iRequest) override {}
		private:			
			void createLightParametersUniformBlock();
			Light(std::string);
			std::string lightName;
			std::vector<EffectStruct> effectFileNames;			
			std::vector<Parameter> mLightParameters;
			char* meshName;
			char* mMaterialName;
			Engine::Math::Transform mTransform;
			Engine::Math::Transform mInitialTransform;
			bool isInitialTransform;
			bool castShadowFlag;		
			float mIntensity;
			Engine::Math::Vector3 mLightColor;
			IObjectController * mObjectController;
			LightType mLightType;
			bool lightParameterInitialized;
			bool lightEnabled;
			ObjectType mObjectType;
		};
	}
}

#endif