#ifndef __TYPEDEFS_H
#define __TYPEDEFS_H

#include <stdint.h>

#include "../Windows/WindowsIncludes.h"
#ifdef PLATFORM_D3D
#include <d3dx9shader.h>
#elif PLATFORM_OPEN_GL
#include <gl/GLU.h>
#endif



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


		typedef
#ifdef PLATFORM_D3D
			DWORD
#elif PLATFORM_OPEN_GL
			GLenum
#endif
			CullingMode;


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

		enum Coordinate
		{
			SCREEN_COORDINATE = 0,
			VIEWPORT_COORDINATE = 1,
			TEXTURE_COORDINATE = 2
		};

		enum TextureType
		{
			TEXTURE_2D = 0,
			TEXTURE_CUBE = 1,
			TEXTURE_3D = 2		
		};

		struct RGBColor
		{
			float r;
			float g;
			float b;

			RGBColor()
			{
				r = g = b = 0.0f;
			}

			RGBColor(float iR, float iG, float iB)
			{
				r = iR;
				g = iG;
				b = iB;
			}
		};

		struct RGBAColor
		{
			float r;
			float g;
			float b;
			float a;

			RGBAColor()
			{
				r = g = b = 0.0f;
				a = 1.0f;
			}

			RGBAColor(float iR, float iG, float iB, float iA)
			{
				r = iR;
				g = iG;
				b = iB;
				a = iA;
			}
		};

	}
}


#endif