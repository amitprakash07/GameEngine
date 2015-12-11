#include "Texture.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "../Windows/WindowsFunctions.h"
#include "../../Engine/Core/EngineCore/EngineCore.h"

typedef char BYTES;

std::map<std::string, Engine::SharedPointer<Engine::Graphics::Texture>> Engine::Graphics::Texture::mTextureList;

bool Engine::Graphics::Texture::addTextureToList(const char* i_TextureName)
{
	bool success = false;
	std::stringstream errormessage;
	if (i_TextureName)
	{
		if (isTextureExist(i_TextureName))
			return true;
		else
		{
			Engine::SharedPointer<Engine::Graphics::Texture> Texture(new Engine::Graphics::Texture(), "Engine::Graphics::Texture");
			if (!Texture.isNull())
			{
				Texture->setTextureName(i_TextureName);
				if (Texture->loadTexture())
				{
					mTextureList[i_TextureName] = Texture;
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


const char* Engine::Graphics::Texture::getTextureName()
{
	return textureName;
}

void Engine::Graphics::Texture::setTextureName(const char* i_TextureName)
{
	size_t length = strlen(i_TextureName);
	textureName = new char[length];
	memcpy(textureName, i_TextureName, sizeof(char)* length);
	textureName[length] = '\0';
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


Engine::Graphics::TextureResource Engine::Graphics::Texture::getTextureResource()
{
	return texture;
}




