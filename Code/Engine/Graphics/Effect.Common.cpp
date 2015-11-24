#include "Effect.h"
#include "../Windows/WindowsFunctions.h"
#include "../../Engine/Core/Utilities/HashedString.h"
#include <fstream>
#include "../Core/Maths/Functions.h"

typedef char BYTES;

std::map<std::string, Engine::SharedPointer<Engine::Graphics::Effect>> Engine::Graphics::Effect::mEffectList;

bool Engine::Graphics::Effect::addEffectToList(std::string i_effectName)
{
	bool success = false;
	std::stringstream errormessage;
	if (i_effectName.size() > 0)
	{
		if (isEffectExist(i_effectName))
		{
			return true;
		}
		else
		{
			Engine::SharedPointer<Engine::Graphics::Effect> effect(new Effect(i_effectName), "Engine::Graphics::Effect");
			if (!effect.isNull())
			{
				if(effect->LoadEffect())
				{
					mEffectList[i_effectName] = effect;
					success = true;
				}
				else
					success = false;
			}
		}
	}
	else
	{
		errormessage << "Vertex Shader and Fragment Shader file name is null";
		WindowsUtil::Print(errormessage.str());
		success = false;
	}
	return success;
}


//void Engine::Graphics::Effect::createMaterialUniforms(size_t i_uniformCount)
//{
//	materialUniformCount = i_uniformCount;
//	materialUniforms = new MaterialUniform[materialUniformCount];
//#ifdef _DEBUG
//	materialUniformNames = new char*[materialUniformCount];
//#endif
//}
//
//
//Engine::Graphics::MaterialUniform* Engine::Graphics::Effect::getMaterialUniform()
//{
//	if (materialUniforms)
//		return materialUniforms;
//	return nullptr;
//}
//
//void Engine::Graphics::Effect::setMaterialUniforms(MaterialUniform* i_materialUniforms)
//{
//	if(i_materialUniforms)
//	{
//		memcpy(materialUniforms, i_materialUniforms, sizeof(MaterialUniform)*materialUniformCount);
//	}
//}
//
//
//size_t Engine::Graphics::Effect::getMaterialUniformCount()
//{
//	return materialUniformCount;
//}


Engine::SharedPointer<Engine::Graphics::Effect> Engine::Graphics::Effect::getEffect(std::string i_shaderName)
{
	for (std::map<std::string, Engine::SharedPointer<Engine::Graphics::Effect>>::iterator i = mEffectList.begin(); i != mEffectList.end(); ++i)
	{
		if (i->first == i_shaderName)
			return i->second;
	}
	return SharedPointer<Engine::Graphics::Effect>();
}

void Engine::Graphics::Effect::deleteAllEffect()
{
	for (std::map<std::string, Engine::SharedPointer<Engine::Graphics::Effect>>::iterator i = mEffectList.begin(); i != mEffectList.end(); ++i)
	{
		i->second.deleteObject();
	}
}

bool Engine::Graphics::Effect::isEffectExist(std::string i_effectName)
{
	if(!i_effectName.empty())
	{
		for (std::map<std::string, SharedPointer<Effect>>::iterator i = mEffectList.begin(); i != mEffectList.end(); ++i)
		{
			if (Engine::utils::StringHash(i->first.c_str()) == Engine::utils::StringHash(i_effectName.c_str()))
				return true;
		}
		return false;
	}
	return false;
}

bool Engine::Graphics::Effect::LoadEffect()
{
	std::stringstream errormessage;
	std::ifstream readFile;

	if (!readFile.is_open())
		readFile.open(effectName.c_str(), std::ifstream::binary);

	readFile.seekg(0, readFile.end);
	size_t length = static_cast<size_t>(readFile.tellg());
	readFile.seekg(0, readFile.beg);

	BYTES * buffer = new BYTES[length];
	//Lets read evrything from asset binary file
	readFile.read(buffer, length);
	readFile.close();//Closing the file Pointer

	if(buffer)
	{
		BYTES * tempBuffer = buffer;
		vertexShader = tempBuffer;
		tempBuffer += vertexShader.size() + 1;
		fragmentShader = tempBuffer;
		tempBuffer += fragmentShader.size() + 1;
		memcpy(renderState, tempBuffer, sizeof(char));
		//uint8_t a = static_cast<uint8_t>(*renderState);
		delete buffer;
		if(LoadShaders())
			return true;
		return false;
	}
	return false;		
}

void Engine::Graphics::EngineUniforms::calculateUniforms(Transformation i_gameObject, Transformation i_camera, float i_fieldOfView, float i_aspectRatio)
{
	g_transform_localToWorld = Engine::Math::cMatrix_transformation(i_gameObject.mOrientation, i_gameObject.mPositionOffset);
	g_transform_worldToView =
		Engine::Math::cMatrix_transformation::CreateWorldToViewTransform(
			i_camera.mOrientation, i_camera.mPositionOffset);
	float aspectRatio = i_aspectRatio;
	float fieldOfViewInRadians = i_fieldOfView;
	g_transform_viewToScreen =
		Engine::Math::cMatrix_transformation::CreateViewToScreenTransform(
			fieldOfViewInRadians, aspectRatio);

}







