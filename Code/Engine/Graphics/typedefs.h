#ifndef __TYPEDEFS_H
#define __TYPEDEFS_H

#include "../Windows/WindowsIncludes.h"
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
		typedef
#ifdef PLATFORM_D3D 
			char*
#elif PLATFORM_OPEN_GL
			GLint
#endif
			UniformHandle;


#ifdef PLATFORM_D3D
#define INITIAL_VAL nullptr
#define DELETE_HANDLE(X) (X = nullptr)
#elif PLATFORM_OPEN_GL
#define INITIAL_VAL 0
#define DELETE_HANDLE(X) (X = 0)
#endif




		
	}
}

	
#endif