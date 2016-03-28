#include "Light.h"
#include "../Core/Utilities/additionaltypes.h"
#include "../Core/Utilities/IObjectController.h"
#include "Mesh.h"


Engine::Graphics::Light::Light(std::string iLightName)
{
	lightName = iLightName;
	meshName = nullptr;
	mMaterialName = nullptr;
	mTransform = Math::Transform();
	mInitialTransform = Math::Transform();
	isInitialTransform = false;
	castShadowFlag = true;
	mIntensity = 1.0f;
	mLightColor = Math::Vector3(1.0f);	
	mObjectController = nullptr;
	mLightType = LightType::Directional;
	effectFileNames.reserve(20);
}

void Engine::Graphics::Light::updateObject()
{
	if(mObjectController)
	{
		typedefs::ActionWithKeyBound action;
		action.action = typedefs::Default;
		mObjectController->updateObject(*this, action);
	}
}


void Engine::Graphics::Light::setObjectController(IObjectController* iObjectController)
{
	if (iObjectController)
		mObjectController = iObjectController;
}


void Engine::Graphics::Light::draw(bool drawable)
{
	if(meshName && mMaterialName)
	{
		Mesh::getMesh(meshName)->drawMesh();
	}
}


void Engine::Graphics::Light::HandleMessage(
	Engine::utils::StringHash& i_message, 
	RTTI* i_MessageSender, void* i_pMessageData)
{
	if (i_MessageSender != nullptr && mObjectController)
	{
		if (i_MessageSender != nullptr && Engine::utils::StringHash("UpdateObject") == i_message && mObjectController)
			mObjectController->updateObject(*this, *reinterpret_cast<Engine::typedefs::ActionWithKeyBound*>(i_pMessageData));
	}
}


bool Engine::Graphics::Light::isRenderable() const
{
	return true;
}


bool Engine::Graphics::Light::isDebugObject() const
{
	return false;
}


std::string Engine::Graphics::Light::getMaterialName()
{
	return mMaterialName;
}



Engine::SharedPointer<Engine::Graphics::Light> 
Engine::Graphics::Light::createLight(std::string iLightName, LightType iLightType)
{
	SharedPointer<Light> tempLight =
		SharedPointer<Light>(new Light(iLightName), "Engine::Graphics::Light");
	tempLight->mLightType = iLightType;
	return tempLight;
}

void Engine::Graphics::Light::enableShadow(bool enableShadow)
{
	castShadowFlag = enableShadow;
}


bool Engine::Graphics::Light::isBothSameType(RTTI*, std::string) const
{
	return true;
}


Engine::Math::Transform Engine::Graphics::Light::getTransform()
{
	return mTransform;
}


std::string Engine::Graphics::Light::getTypeInfo() const
{
	return "Engine::Graphics::Light";
}


bool Engine::Graphics::Light::isShadowCastingEnabled() const
{
	return castShadowFlag;
}


void Engine::Graphics::Light::resetTransform()
{
	mTransform = mInitialTransform;
}


void Engine::Graphics::Light::setColor(Math::Vector3 iColor)
{
	mLightColor = iColor;
}

void Engine::Graphics::Light::setIntensity(float iIntensity)
{
	mIntensity = iIntensity;
}


void Engine::Graphics::Light::setMeshName(std::string iMeshName, std::string iMaterialName)
{
	if(!meshName)
		meshName = new char[iMeshName.size()];		
	else
		delete meshName;
	
	strcpy(meshName, iMeshName.c_str());

	if (!mMaterialName)
		mMaterialName = new char[iMaterialName.size()];
	else delete mMaterialName;
	
	strcpy(mMaterialName, iMaterialName.c_str());	
}

void Engine::Graphics::Light::setScale(float iX, float iY, float iZ)
{
	//stub - no implementation required
}


void Engine::Graphics::Light::setTransform(Engine::Math::Vector3 iPosition, Engine::Math::Quaternion iRotation)
{
	mTransform.setOrientation(iRotation);
	mTransform.setPosition(iPosition);
	if(!isInitialTransform)
	{
		mInitialTransform = mTransform;
		isInitialTransform = true;
	}
	
}


Engine::Math::Vector3 Engine::Graphics::Light::getLightColor() const
{
	return mLightColor;
}

float Engine::Graphics::Light::getLightIntensity() const
{
	return mIntensity;
}


void Engine::Graphics::Light::addLightToObjectEffect
(std::string iEffectFileName, ShaderType iShaderType)
{
	EffectStruct tempEffectStruct;
	tempEffectStruct.effectName = iEffectFileName;
	tempEffectStruct.shaderType = iShaderType;
	effectFileNames.push_back(tempEffectStruct);
}
























