#include "Effect.h"
#include "../Windows/WindowsFunctions.h"
#include "../../Engine/Core/Utilities/HashedString.h"
#include <fstream>

typedef char BYTES;

std::map<std::string, Engine::SharedPointer<Engine::Graphics::Effect>> Engine::Graphics::Effect::mEffectList;

bool Engine::Graphics::Effect::addEffectToList(std::string i_shaderName, std::string i_effectFileName)
{
	bool success = false;
	std::stringstream errormessage;
	if (i_effectFileName.size() > 0)
	{
		if (isEffectExist(i_effectFileName))
		{
			return true;
		}
		else
		{
			Engine::SharedPointer<Engine::Graphics::Effect> effect(new Effect(i_shaderName, i_effectFileName), "Engine::Graphics::Effect");
			if (!effect.isNull())
			{
				if(effect->LoadEffect() && effect->LoadShaders())
				{
					mEffectList[i_shaderName] = effect;
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

//Engine::SharedPointer<Engine::Graphics::Effect> Engine::Graphics::Effect::getEffect(std::string i_vertexShader, std::string i_fragmentShader)
//{
//	if(!i_vertexShader.empty() && (!i_fragmentShader.empty()) && isEffectExist(i_vertexShader, i_fragmentShader))
//	{
//		for (std::map<std::string, SharedPointer<Effect>>::iterator i = mEffectList.begin(); i != mEffectList.end(); ++i)
//		{
//			if (i->second->vertexShader == i_vertexShader &&
//				i->second->fragmentShader == i_fragmentShader)
//				return i->second;
//		}
//	}
//	return SharedPointer<Engine::Graphics::Effect>();
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


bool Engine::Graphics::Effect::isEffectExist(std::string i_effectFileName)
{
	if(!i_effectFileName.empty())
	{
		for (std::map<std::string, SharedPointer<Effect>>::iterator i = mEffectList.begin(); i != mEffectList.end(); ++i)
		{
			if (Engine::utils::StringHash(i->second->effectFileName.c_str()) == Engine::utils::StringHash(i_effectFileName.c_str()))
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
		readFile.open(effectFileName.c_str(), std::ifstream::binary);

	readFile.seekg(0, readFile.end);
	size_t length = static_cast<size_t>(readFile.tellg());
	readFile.seekg(0, readFile.beg);

	BYTES * buffer = new BYTES[length];
	//Lets read evrything from asset binary file
	readFile.read(buffer, length);
	readFile.close();//Closing the file Pointer

	if(buffer)
	{
		vertexShader = buffer;
		fragmentShader = buffer + strlen(buffer) + 1;
		return true;
	}
	return false;		
}





