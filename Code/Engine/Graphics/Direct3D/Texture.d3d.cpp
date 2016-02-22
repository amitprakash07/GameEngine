#include "../Texture.h"
#include "../../Windows/WindowsFunctions.h"
#include "../Graphics.h"


bool Engine::Graphics::Texture::loadTexture()
{
	const unsigned int useDimensionsFromFile = D3DX_DEFAULT_NONPOW2;
	const unsigned int useMipMapsFromFile = D3DX_FROM_FILE;
	const DWORD staticTexture = 0;
	const D3DFORMAT useFormatFromFile = D3DFMT_FROM_FILE;
	const D3DPOOL letD3dManageMemory = D3DPOOL_MANAGED;
	const DWORD useDefaultFiltering = D3DX_DEFAULT;
	const D3DCOLOR noColorKey = 0;
	D3DXIMAGE_INFO* noSourceInfo = nullptr;
	PALETTEENTRY* noColorPalette = nullptr;
	const HRESULT result = 
		D3DXCreateTextureFromFileEx(Engine::Graphics::GraphicsSystem::getDevice(), textureName, 
			useDimensionsFromFile, useDimensionsFromFile, useMipMapsFromFile, staticTexture,
			useFormatFromFile, letD3dManageMemory, useDefaultFiltering, useDefaultFiltering,
			noColorKey, noSourceInfo, noColorPalette, &texture);
	if (SUCCEEDED(result))
		return true;
	
	WindowsUtil::Print("Unable to load the texture in the device");
	return false;
}
	
Engine::Graphics::Texture::Texture()
{
	textureName = nullptr;
	texture = nullptr;
	effectName = nullptr;
	textureName = nullptr;
	shaderType = Fragment;
	textureSamplerID = -1;
	textureType = TEXTURE_2D;
	samplerName = nullptr;
}


Engine::Graphics::Texture::Texture(char* i_effectName,
	char* i_textureName,
	char* i_samplerName,
	ShaderType iShaderType)
{
	if (i_textureName)
	{
		size_t length = strlen(i_textureName);
		textureName = new char[length];
		memcpy(textureName, i_textureName, length);
	}
	if (i_effectName)
	{
		size_t length = strlen(i_effectName);
		effectName = new char[length];
		memcpy(effectName, i_effectName, length);
	}
	if (i_samplerName)
	{
		size_t length = strlen(i_samplerName);
		samplerName = new char[length];
		memcpy(samplerName, i_samplerName, length);
	}
	texture = nullptr;
	textureSamplerID = -1;
	shaderType = iShaderType;
	textureType = TEXTURE_2D;

}

Engine::Graphics::Texture::~Texture()
{
	if (textureName)
		delete textureName;
	if (texture)
		texture->Release();
}


void Engine::Graphics::Texture::setSamplerID(SamplerID sampleID)
{
	textureSamplerID = sampleID;
} 


void Engine::Graphics::Texture::setTextureInShaderObject(int i_textureUnit)const
{
	HRESULT result = 
		Engine::Graphics::GraphicsSystem::getDevice()->SetTexture(textureSamplerID, texture);
	WindowsUtil::Assert(SUCCEEDED(result), "Unable to set the Texture to ths Shader");	
}





