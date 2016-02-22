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
}


Engine::Graphics::Texture::Texture(char* i_textureName)
{
	if (i_textureName)
	{
		size_t length = strlen(textureName);
		textureName = new char[length];
		memcpy(textureName, i_textureName, length);
	}
	texture = nullptr;
}

Engine::Graphics::Texture::~Texture()
{
	if (textureName)
		delete textureName;
	if (texture)
		texture->Release();
}

//bool Engine::Graphics::Texture::setTexture()
//{
//	HRESULT result = Engine::Graphics::GraphicsSystem::getDevice()->SetTexture(textureHandle, texture);
//	return (SUCCEEDED(result));
//}




