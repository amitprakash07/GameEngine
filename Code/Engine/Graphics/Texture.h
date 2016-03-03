#ifndef __TEXTURE_H
#define __TEXTURE_H

#include "../Windows/WindowsIncludes.h"

#ifdef PLATFORM_D3D
#include <d3dx9shader.h>
#elif PLATFORM_OPEN_GL
#include "../Graphics/Graphics.h"
#include <gl/GLU.h>
#endif

#include "../Core/Utilities/SharedPointer.h"
#include <map>
#include "typedefs.h"
#include "uniformdefs.h"
#include <vector>

namespace Engine
{
	namespace Graphics
	{
		class Texture :public RTTI
		{
		public:
			static bool addTextureToList(const char* i_effectFileName,
				const char * i_TextureName, const char* i_samplerName,
				ShaderType iShaderType);
			static bool addTextureToList(const char* i_effectFileName,
				const char * textureName, TextureResource textureResource,
				const char* samplerName, ShaderType shaderType, 
				TextureType textureType);
			static SharedPointer<Texture> getTexture(const char*);
			static bool isTextureExist(const char*);
			static void deleteAll();
			void setTextureName(const char*);
			void setEffectName(const char*);
			void setUniformName(const char*);
			void setShaderType(ShaderType iShaderType);
			const char* getTextureName()const;
			bool loadTexture();
			std::string getTypeInfo() const override { return ""; }
			bool isBothSameType(RTTI*, std::string) const override { return true; }
			TextureResource getTextureResource() const;
			void setTextureResource(TextureResource textureResource);
			void setSamplerID(SamplerID sampleID);
			void setTextureInShaderObject(int i_textureUnit);
			~Texture();
		private:
			static std::map<std::string, Engine::SharedPointer<Texture>> mTextureList;
			std::string textureName;
			std::string effectName;
			std::string samplerName;
			ShaderType shaderType;
			TextureResource texture;
			SamplerID textureSamplerID;
			TextureType textureType;
			void associateSamplerDataFromShader();
			Texture(char* i_effectName, 
				char* i_textureName,
				char* i_samplerName,
				ShaderType iShaderType);
			Texture();
		};
	}

}

#endif