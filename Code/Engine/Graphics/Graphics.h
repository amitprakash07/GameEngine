/*
	This file contains the function declarations for graphics
*/

#ifndef GRAPHICS_H
#define GRAPHICS_H

// Platform Specific Header Files
//=============
#include "../Windows/WindowsIncludes.h"

#ifdef PLATFORM_D3D
#include <d3d9.h>
#elif PLATFORM_OPEN_GL
//#include "../../Externals/OpenGLExtensions/OpenGlExtensions.h"
#endif

namespace Engine
{
	namespace Graphics
	{
		class GraphicsSystem
		{
		public:
			static bool Initialize(const HWND i_renderingWindow);
			static void Render();
			static bool ShutDown();
			
			static HWND getRenderingWindow()
			{
				if (s_renderingWindow)
					return s_renderingWindow;
				else
					return nullptr;
			}

#ifdef PLATFORM_D3D
			static IDirect3DDevice9* getDevice();
#endif

		private:
			static HWND s_renderingWindow;

		};
	}
}

#endif	
