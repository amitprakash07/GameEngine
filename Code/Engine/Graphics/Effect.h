#ifndef _EFECTS_H
#define _EFECTS_H

#ifdef PLATFORM_D3D
#include <d3dx9shader.h>
#elif PLATFORM_OPEN_GL
#include "../Graphics/Graphics.h"
#include <gl/GLU.h>
#endif

#include <vector>

namespace Engine
{
	namespace Graphics
	{
		class Effect
		{
		public:
			bool setShaders();
			Effect(std::string, std::string);
			~Effect();
		private:
			std::string fragmentShader;
			std::string vertexShader;
			bool LoadFragmentShader();
			bool LoadVertexShader();
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

