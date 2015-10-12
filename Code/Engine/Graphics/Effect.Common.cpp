#include "Effect.h"
#include "../Windows/WindowsFunctions.h"


std::map<std::string, Engine::SharedPointer<Engine::Graphics::Effect>> mEffectList;


bool Engine::Graphics::Effect::addEffectToList(std::string i_shaderName, std::string i_vertexShader, std::string i_fragmentShader)
{
	bool success = false;
	std::stringstream errormessage;
	if (i_vertexShader.size() > 0 && i_fragmentShader.size() > 0)
	{
		Engine::SharedPointer<Engine::Graphics::Effect> effect(new Effect(i_shaderName, i_vertexShader, i_fragmentShader));
		if (effect.isNull())
		{
			mEffectList[i_shaderName] = effect;
			success = true;
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

Engine::SharedPointer<Engine::Graphics::Effect> Engine::Graphics::Effect::getEffect(std::string i_shaderName)
{
	if(!i_shaderName.empty() )
	{
		return mEffectList[i_shaderName];
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




