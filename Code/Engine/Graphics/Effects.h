#ifndef _EFECTS_H
#define _EFECTS_H

#ifdef PLATFORM_D3D
#include <d3dx9shader.h>
#elif PLATFORM_OPEN_GL
#include "../Graphics/Graphics.h"
#include <gl/GLU.h>
#endif

namespace Engine
{
	namespace Graphics
	{
		class Effect
		{
		public:
			bool setShaders();
			Effect();
			~Effect();
		private:
#ifdef PLATFORM_D3D
			IDirect3DVertexShader9* s_vertexShader;
			IDirect3DPixelShader9* s_fragmentShader;
			bool LoadFragmentShader();
			bool LoadVertexShader();
#elif PLATFORM_OPEN_GL
			GLuint s_programId;
			bool CreateProgram();
#endif
		};
	}
}

#endif

