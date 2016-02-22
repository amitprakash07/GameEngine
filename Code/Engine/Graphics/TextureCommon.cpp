#include "Texture.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "../Windows/WindowsFunctions.h"
#include "../../Engine/Core/EngineCore/EngineCore.h"
#include "Effect.h"

typedef char BYTES;

std::map<std::string, Engine::SharedPointer<Engine::Graphics::Texture>> Engine::Graphics::Texture::mTextureList;

bool Engine::Graphics::Texture::addTextureToList(const char* i_effectFileName,
	const char * i_TextureName, const char* i_samplerName, ShaderType iShaderType)
{
	bool success = false;
	std::stringstream errormessage;
	if (i_TextureName)
	{
		if (isTextureExist(i_TextureName))
			return true;
		else
		{
			Engine::SharedPointer<Engine::Graphics::Texture> tempTexture(new Engine::Graphics::Texture(), "Engine::Graphics::Texture");
			if (!tempTexture.isNull())
			{
				tempTexture->setTextureName(i_TextureName);
				tempTexture->setEffectName(i_effectFileName);
				tempTexture->setUniformName(i_samplerName);
				tempTexture->setShaderType(iShaderType);
				if (tempTexture->loadTexture())
				{
					tempTexture->getSamplerDataFromShader();
					mTextureList[i_TextureName] = tempTexture;
					success = true;
				}
				else success = false;
			}
			else success = false;
		}
	}
	else
	{
		errormessage << "\nEmpty Texture Name";
		WindowsUtil::Print(errormessage.str());
		success = false;
	}
	return success;
}


const char* Engine::Graphics::Texture::getTextureName()const
{
	return textureName;
}

void Engine::Graphics::Texture::setShaderType(ShaderType iShaderType)
{
	shaderType = iShaderType;
}


void Engine::Graphics::Texture::setTextureName(const char* i_TextureName)
{
	size_t length = strlen(i_TextureName);
	textureName = new char[length];
	memcpy(textureName, i_TextureName, sizeof(char)* length);
	textureName[length] = '\0';
}

void Engine::Graphics::Texture::setEffectName(const char* i_effectName)
{
	size_t length = strlen(i_effectName);
	effectName = new char[length];
	memcpy(effectName, i_effectName, sizeof(char)* length);
	effectName[length] = '\0';
}

void Engine::Graphics::Texture::setUniformName(const char* i_samplerName)
{
	size_t length = strlen(i_samplerName);
	samplerName = new char[length];
	memcpy(samplerName, i_samplerName, sizeof(char)* length);
	samplerName[length] = '\0';
}


void Engine::Graphics::Texture::getSamplerDataFromShader()
{
	SharedPointer<Effect> tempEffect = Engine::Graphics::Effect::getEffect(effectName);
	textureSamplerID =
		tempEffect->getSamplerID(tempEffect->getUniformHandle(samplerName, shaderType), shaderType);
}


Engine::SharedPointer<Engine::Graphics::Texture> Engine::Graphics::Texture::getTexture(const char* i_filename)
{
	for (std::map<std::string, SharedPointer<Texture>>::iterator i = mTextureList.begin(); i != mTextureList.end(); ++i)
	{
		if (strcmp(i->first.c_str(), i_filename) == 0)
			return i->second;
	}
	return SharedPointer<Engine::Graphics::Texture>();
}


bool Engine::Graphics::Texture::isTextureExist(const char* i_TextureName)
{
	for (std::map<std::string, SharedPointer<Texture>>::iterator i = mTextureList.begin(); i != mTextureList.end(); ++i)
	{
		if (strcmp(i->first.c_str(), i_TextureName) == 0)
			return true;
	}
	return false;
}


void Engine::Graphics::Texture::deleteAll()
{
	for (std::map<std::string, SharedPointer<Texture>>::iterator i = mTextureList.begin(); i != mTextureList.end(); ++i)
	{
		i->second.deleteObject();
	}
}


Engine::Graphics::TextureResource Engine::Graphics::Texture::getTextureResource() const
{
	return texture;
}




