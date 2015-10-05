#include "Effects.h"
#include "../Windows/WindowsFunctions.h"


std::vector<Engine::Graphics::Effect*> Engine::Graphics::Effects::effects;

bool Engine::Graphics::Effects::addEffect(std::string i_vertexShader, std::string i_fragmentShader)
{
	bool success = false;
	std::stringstream errormessage;
	if (i_vertexShader.size() > 0 && i_fragmentShader.size() > 0)
	{
		Effect * effect = new Effect(i_vertexShader, i_fragmentShader);
		if (effect)
		{
			effects.push_back(effect);
			effect->setShaders();
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


Engine::Graphics::Effects::Effects()
{
	effects.reserve(20);
}

Engine::Graphics::Effects::~Effects()
{
	for (int i = 0; i < effects.size(); i++)
		delete effects[i];
}







