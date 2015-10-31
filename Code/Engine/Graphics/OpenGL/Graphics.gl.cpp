// Header Files
//=============

#include "../Graphics.h"
#include <gl/GLU.h>
#include <cassert>
#include <cstdint>
#include <string>
#include <sstream>
#include "../../Windows/WindowsFunctions.h"
#include "../../Core/EngineCore/Objects/Scene.h"

// Static Data Initialization
//===========================

namespace Engine
{
	namespace Graphics
	{
		HWND GraphicsSystem::s_renderingWindow = nullptr;
		HDC s_deviceContext = nullptr;
		HGLRC s_openGlRenderingContext = nullptr;

		// Helper Function Declarations
		//=============================

		bool CreateRenderingContext();
		
		
		// This helper struct exists to be able to dynamically allocate memory to get "log info"
		// which will automatically be freed when the struct goes out of scope
		struct sLogInfo
		{
			GLchar* memory;
			sLogInfo(const size_t i_size) { memory = reinterpret_cast<GLchar*>(malloc(i_size)); }
			~sLogInfo() { if (memory) free(memory); }
		};
	}
}

// Interface
//==========
bool Engine::Graphics::GraphicsSystem::create()
{
	// Create an OpenGL rendering context
	if (!CreateRenderingContext())
	{
		goto OnError;
	}

	// Load any required OpenGL extensions
	{
		std::string errorMessage;
		if (!OpenGlExtensions::Load(&errorMessage))
		{
			WindowsUtil::Print( errorMessage );
			goto OnError;
		}
	}

	return true;

OnError:
	ShutDown();
	return false;
}


bool Engine::Graphics::GraphicsSystem::clear()
{
	// Every frame an entirely new image will be created.
	// Before drawing anything, then, the previous image will be erased
	// by "clearing" the image buffer (filling it with a solid color)
	// Black is usually used
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	if (glGetError() != GL_NO_ERROR)
		return false;
	// In addition to the color, "depth" and "stencil" can also be cleared,
	// but for now we only care about color
	const GLbitfield clearColor = GL_COLOR_BUFFER_BIT;
	glClear(clearColor);
	if (glGetError() == GL_NO_ERROR)
		return true;
	
	return false;
}


void Engine::Graphics::GraphicsSystem::beginScene()
{
	//Works like a stub - does nothing
}

void Engine::Graphics::GraphicsSystem::endScene()
{
	//Works like a stub - does nothing
}


	
	
void Engine::Graphics::GraphicsSystem::showBuffer()
{
	// Everything has been drawn to the "back buffer", which is just an image in memory.
	// In order to display it, the contents of the back buffer must be swapped with the "front buffer"
	// (which is what the user sees)
	if (s_renderingWindow)
	{
		BOOL result = SwapBuffers(s_deviceContext);
		assert(result != FALSE);
	}	
}



bool Engine::Graphics::GraphicsSystem::destroy()
{
	bool wereThereErrors = false;

	if (s_openGlRenderingContext != nullptr)
	{
		if (wglMakeCurrent(s_deviceContext, nullptr) != FALSE)
		{
			if (wglDeleteContext(s_openGlRenderingContext) == FALSE)
			{
				std::stringstream errorMessage;
				errorMessage << "Windows failed to delete the OpenGL rendering context: " << WindowsUtil::GetLastWindowsError();
				WindowsUtil::Print( errorMessage.str() );
			}
		}
		else
		{
			std::stringstream errorMessage;
			errorMessage << "Windows failed to unset the current OpenGL rendering context: " << WindowsUtil::GetLastWindowsError();
			WindowsUtil::Print( errorMessage.str() );
		}
		s_openGlRenderingContext = nullptr;
	}

	if (s_deviceContext != nullptr)
	{
		// The documentation says that this call isn't necessary when CS_OWNDC is used
		ReleaseDC(s_renderingWindow, s_deviceContext);
		s_deviceContext = nullptr;
	}

	s_renderingWindow = nullptr;

	return !wereThereErrors;
}




// Helper Function Declarations
//=============================


bool Engine::Graphics::CreateRenderingContext()
	{
		// A "device context" can be thought of an abstraction that Windows uses
		// to represent the graphics adaptor used to display a given window
		s_deviceContext = GetDC( Engine::Graphics::GraphicsSystem::getRenderingWindow() );
		if ( s_deviceContext == nullptr )
		{
			WindowsUtil::Print( "Windows failed to get the device context" );
			return false;
		}
		// Windows requires that an OpenGL "render context" is made for the window we want to use to render into
		{
			// Set the pixel format of the rendering window
			{
				PIXELFORMATDESCRIPTOR desiredPixelFormat = { 0 };
				{
					desiredPixelFormat.nSize = sizeof( PIXELFORMATDESCRIPTOR );
					desiredPixelFormat.nVersion = 1;

					desiredPixelFormat.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
					desiredPixelFormat.iPixelType = PFD_TYPE_RGBA;
					desiredPixelFormat.cColorBits = 32;
					desiredPixelFormat.iLayerType = PFD_MAIN_PLANE ;
				}
				// Get the ID of the desired pixel format
				int pixelFormatId;
				{
					pixelFormatId = ChoosePixelFormat( s_deviceContext, &desiredPixelFormat );
					if ( pixelFormatId == 0 )
					{
						std::stringstream errorMessage;
						errorMessage << "Windows couldn't choose the closest pixel format: " << WindowsUtil::GetLastWindowsError();
						WindowsUtil::Print( errorMessage.str() );
						return false;
					}
				}
				// Set it
				if ( SetPixelFormat( s_deviceContext, pixelFormatId, &desiredPixelFormat ) == FALSE )
				{
					std::stringstream errorMessage;
					errorMessage << "Windows couldn't set the desired pixel format: " << WindowsUtil::GetLastWindowsError();
					WindowsUtil::Print( errorMessage.str() );
					return false;
				}
			}
			// Create the OpenGL rendering context
			s_openGlRenderingContext = wglCreateContext( s_deviceContext );
			if ( s_openGlRenderingContext == NULL )
			{
				std::stringstream errorMessage;
				errorMessage << "Windows failed to create an OpenGL rendering context: " << WindowsUtil::GetLastWindowsError();
				WindowsUtil::Print( errorMessage.str() );
				return false;
			}
			// Set it as the rendering context of this thread
			if ( wglMakeCurrent( s_deviceContext, s_openGlRenderingContext ) == FALSE )
			{
				std::stringstream errorMessage;
				errorMessage << "Windows failed to set the current OpenGL rendering context: " << WindowsUtil::GetLastWindowsError();
				WindowsUtil::Print( errorMessage.str() );
				return false;
			}
		}

		return true;
	}




