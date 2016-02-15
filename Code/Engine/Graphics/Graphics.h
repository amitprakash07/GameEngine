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
#include "../../Externals/OpenGLExtensions/OpenGlExtensions.h"
#endif

#include <stdint.h>
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

			static bool setRenderState(uint8_t);
			static void EnableWireFrame(bool);
			static void EnableAlphaBlending(bool);
			static void EnableDepthTesting(bool);
			static void EnableDepthWriting(bool);
			static void EnableFaceCulling(bool, DWORD cullingMode = D3DCULL_CCW);

#ifdef PLATFORM_D3D
			static IDirect3DDevice9* getDevice();
#endif
		private:
			static HWND s_renderingWindow;
			static bool create();
			static bool clear();
			static void showBuffer();
			static void beginScene();
			static void endScene();
			static bool destroy();
		};
	}
}

namespace Engine
{
	namespace Graphics
	{
		HRESULT GetVertexProcessingUsage(DWORD& o_usage);
	}
}

#endif	
