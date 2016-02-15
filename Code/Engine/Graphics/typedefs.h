#ifndef __TYPEDEFS_H
#define __TYPEDEFS_H

#include "../Windows/WindowsIncludes.h"
#ifdef PLATFORM_D3D
#include <d3dx9shader.h>
#elif PLATFORM_OPEN_GL
#include "../Graphics/Graphics.h"
#include <gl/GLU.h>
#endif

#include <stdint.h>

namespace Engine
{
	namespace Graphics
	{
		typedef
#ifdef PLATFORM_D3D 
			D3DXHANDLE
#elif PLATFORM_OPEN_GL
			GLint
#endif
			UniformHandle;

		typedef
#ifdef PLATFORM_D3D
			DWORD
#elif PLATFORM_OPEN_GL
			GLint
#endif
			SamplerID;

		typedef
#ifdef PLATFORM_D3D
			IDirect3DTexture9*
#elif PLATFORM_OPEN_GL
			GLuint
#endif
			TextureResource;

		typedef
#ifdef PLATFORM_D3D
			ID3DXConstantTable*
#elif PLATFORM_OPEN_GL
			GLuint
#endif
			ConstantTable;




		enum indiceWinding
		{
			RIGHT = 0,
			LEFT = 1
		};
		typedef indiceWinding winding;

		struct vertex
		{
			// Position
			float X, Y, Z;
			// Normal
			float nx, ny, nz;
			// Tangent
			float tx, ty, tz;
			// Bitangent
			float btx, bty, btz;
			// Texture coordinates
			float u, v;
#ifdef PLATFORM_D3D
			uint8_t B, G, R, A;
#elif PLATFORM_OPEN_GL
			uint8_t R, G, B, A;
#endif
		};


#ifdef PLATFORM_D3D
#define INITIAL_VAL nullptr
#define DELETE_HANDLE(X) (X = nullptr)
#elif PLATFORM_OPEN_GL
#define INITIAL_VAL 0
#define DELETE_HANDLE(X) (X = 0)
#endif

		enum Coordinate
		{
			SCREEN_COORDINATE = 0,
			VIEWPORT_COORDINATE = 1,
			TEXTURE_COORDINATE = 2
		};

	}
}


#endif