#include "Effect.h"
#include "../Windows/WindowsFunctions.h"
#include "../../Engine/Core/Utilities/HashedString.h"


std::map<std::string, Engine::SharedPointer<Engine::Graphics::Effect>> Engine::Graphics::Effect::mEffectList;

bool Engine::Graphics::Effect::addEffectToList(std::string i_shaderName, std::string i_vertexShader, std::string i_fragmentShader)
{
	bool success = false;
	std::stringstream errormessage;
	if (i_vertexShader.size() > 0 && i_fragmentShader.size() > 0)
	{
		if (isEffectExist(i_vertexShader, i_fragmentShader))
		{
			return true;
		}
		else
		{
			Engine::SharedPointer<Engine::Graphics::Effect> effect(new Effect(i_shaderName, i_vertexShader, i_fragmentShader), "Engine::Graphics::Effect");
			if (!effect.isNull())
			{
				mEffectList[i_shaderName] = effect;
				success = true;
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

Engine::SharedPointer<Engine::Graphics::Effect> Engine::Graphics::Effect::getEffect(std::string i_vertexShader, std::string i_fragmentShader)
{
	if(!i_vertexShader.empty() && (!i_fragmentShader.empty()) && isEffectExist(i_vertexShader, i_fragmentShader))
	{
		for (std::map<std::string, SharedPointer<Effect>>::iterator i = mEffectList.begin(); i != mEffectList.end(); ++i)
		{
			if (i->second->vertexShader == i_vertexShader &&
				i->second->fragmentShader == i_fragmentShader)
				return i->second;
		}
	}
	return SharedPointer<Engine::Graphics::Effect>();
}

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


bool Engine::Graphics::Effect::isEffectExist(std::string i_vertexShader, std::string i_fragmentShader)
{
	if(!i_vertexShader.empty() && !i_fragmentShader.empty())
	{
		for (std::map<std::string, SharedPointer<Effect>>::iterator i = mEffectList.begin(); i != mEffectList.end(); ++i)
		{
			if (Engine::utils::StringHash(i->second->vertexShader.c_str()) == Engine::utils::StringHash(i_vertexShader.c_str()) &&
				Engine::utils::StringHash(i->second->fragmentShader.c_str()) == Engine::utils::StringHash(i_fragmentShader.c_str()))
				return true;
		}
		return false;
	}
	return false;
}




