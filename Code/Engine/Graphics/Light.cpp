#include "Light.h"
#include "../Core/Utilities/additionaltypes.h"
#include "../Core/Utilities/IObjectController.h"
#include "Mesh.h"
#include "UniformBlock.h"
#include "Effect.h"

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
	lightParameterInitialized = false;
	lightEnabled = true;
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

std::string Engine::Graphics::Light::getName() const
{
	return lightName;
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


void Engine::Graphics::Light::addLightToEffect
(std::string iEffectFileName, ShaderType iShaderType)
{
	bool isEffectAlreadyAdded = false;
	for (std::vector<EffectStruct>::iterator i = effectFileNames.begin();
	i!= effectFileNames.end(); ++i)
	{
		if(i->effectName == iEffectFileName && i->shaderType == iShaderType)
		{
			isEffectAlreadyAdded = true;
			break;
		}
	}	
	if(!isEffectAlreadyAdded)
	{
		EffectStruct tempStruct;
		tempStruct.effectName = iEffectFileName;
		tempStruct.shaderType = iShaderType;
		tempStruct.uniformBlockSet = true;
		effectFileNames.push_back(tempStruct);				
	}
}


void Engine::Graphics::Light::addLightToAllEffects(ShaderType iShaderType)
{
	std::vector<SharedPointer<Effect>> tempEffectList
		= Effect::getAllEfects();
	for (std::vector<SharedPointer<Effect>>::iterator i = tempEffectList.begin();
	i != tempEffectList.end(); ++i)
	{
		bool isEffectAlreadyAdded = false;		
		for (std::vector<EffectStruct>::iterator j = effectFileNames.begin();
		j != effectFileNames.end(); ++j)
		{
			if (j->effectName == ((*i)->getEffectName()) && j->shaderType == iShaderType)
			{
				isEffectAlreadyAdded = true;
				break;
			}
		}
		if (!isEffectAlreadyAdded)
		{
			EffectStruct tempStruct;			
			tempStruct.effectName = (*i)->getEffectName();
			tempStruct.shaderType = iShaderType;
			tempStruct.uniformBlockSet = true;
			effectFileNames.push_back(tempStruct);
		}
	}
}


void Engine::Graphics::Light::removeLightFromAllEffects(ShaderType iShaderType)
{
	for (std::vector<EffectStruct>::iterator i = effectFileNames.begin();
	i != effectFileNames.end(); ++i)
	{
		if (i->shaderType == iShaderType)
			effectFileNames.erase(i);
	}
}

void Engine::Graphics::Light::removeLightFromEffect(
	std::string iEffectFileName, ShaderType iShaderType)
{
	for (std::vector<EffectStruct>::iterator i = effectFileNames.begin();
	i!= effectFileNames.end(); ++i)
	{
		if (i->effectName == iEffectFileName && i->shaderType == iShaderType)
		{
			effectFileNames.erase(i);
			break;
		}
	}
}

void Engine::Graphics::Light::addLightParameter(std::string iLightParameterName, 
	DataTypes iLightParameterDataType, 
	Data iParameterValue)
{
	Parameter tempParameter;
	tempParameter.mParameterName = iLightParameterName;
	tempParameter.mDataType = iLightParameterDataType;
	tempParameter.mParameterData = iParameterValue;
	mLightParameters.push_back(tempParameter);
}


void Engine::Graphics::Light::setLightParameterValue(std::string iLightParameterName, 
	DataTypes iLightParameterDataType, 
	Data iParameterValue)
{
	for (std::vector<Parameter>::iterator i = mLightParameters.begin();
	i!= mLightParameters.end(); ++i)
	{
		if (i->mParameterName == iLightParameterName)
			i->mParameterData = iParameterValue;
	}
}


void Engine::Graphics::Light::createLightParametersUniformBlock()
{	
	if(!lightParameterInitialized && lightEnabled)
	{
		std::vector<std::string> lightUniforms;
		for (std::vector<Parameter>::iterator j = mLightParameters.begin();
		j != mLightParameters.end(); ++j)
		{
			lightUniforms.push_back(j->mParameterName);
		}

		for (std::vector<EffectStruct>::iterator i = effectFileNames.begin();
		i != effectFileNames.end(); ++i)
		{
			Engine::SharedPointer<Engine::Graphics::Effect>
				tempEffect = Effect::getEffect(i->effectName);			
			tempEffect->addUniformBlock("lightUniforms",
				Engine::Graphics::Fragment,
				Engine::Graphics::Block,
				lightUniforms);
		}
		lightParameterInitialized = true;
	}
}

void Engine::Graphics::Light::enableLight(bool iRequest)
{
	lightEnabled = iRequest;
}


void Engine::Graphics::Light::setLightParameterValueToShaderObject()
{
	createLightParametersUniformBlock();
	if(lightParameterInitialized && lightEnabled)
	{
		for (std::vector<EffectStruct>::iterator i = effectFileNames.begin();
		i != effectFileNames.end(); ++i)
		{
			SharedPointer<UniformBlock> tempUniformBlock =
				UniformBlock::getUniformBlock(i->effectName, "lightUniforms",
					Fragment);
			for (std::vector<Parameter>::iterator j = mLightParameters.begin();
			j!=mLightParameters.end(); ++j)
			{
				tempUniformBlock->setUniformBlockData(j->mParameterName,
					j->mDataType, j->mParameterData);
			}
		}
	}
}