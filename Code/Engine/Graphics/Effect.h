#ifndef _EFECTS_H
#define _EFECTS_H

#ifdef PLATFORM_D3D
#include <d3dx9shader.h>
#elif PLATFORM_OPEN_GL
#include "../Graphics/Graphics.h"
#include <gl/GLU.h>
#endif

#include <vector>
#include <map>
#include "../Core/Utilities/SharedPointer.h"

namespace Engine
{
	namespace Graphics
	{
		class Effect
		{
		public:
			static bool addEffectToList(std::string, std::string, std::string);
			static Engine::SharedPointer<Effect> getEffect(std::string);
			static void deleteAllEffect();
			bool setShaders();
			~Effect();
		private:
			static std::map<std::string, Engine::SharedPointer<Effect>> mEffectList;
			std::string shaderName;
			std::string fragmentShader;
			std::string vertexShader;
			bool LoadFragmentShader();
			bool LoadVertexShader();
			Effect(std::string, std::string, std::string);
#ifdef PLATFORM_D3D
			IDirect3DVertexShader9* s_vertexShader;
			IDirect3DPixelShader9* s_fragmentShader;
#elif PLATFORM_OPEN_GL
			GLuint s_programId;
			bool CreateProgram();
#endif
		};
	}
}

#endif

