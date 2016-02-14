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

namespace Engine
{
	namespace Graphics
	{
		class Texture:public RTTI
		{
		public:
			static bool addTextureToList(const char*);
			static SharedPointer<Texture> getTexture(const char*);
			static bool isTextureExist(const char*);
			static void deleteAll();
			void setTextureName(const char*);
			const char* getTextureName();
			bool loadTexture();
			std::string getTypeInfo() override { return ""; }
			bool isBothSameType(RTTI*, std::string) override { return true; }
			//bool setTexture();
			~Texture();
		private:
			static std::map<std::string, Engine::SharedPointer<Texture>> mTextureList;
			char* textureName;
			Texture(char*);
			Texture();
#ifdef PLATFORM_D3D
			IDirect3DTexture9* texture;			
#elif PLATFORM_OPEN_GL
			GLuint texture;
#endif
		};
	}

}

#endif