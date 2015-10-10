// Header Files
//=============

#include "../Graphics.h"
#include <d3dx9shader.h>
#include <cassert>
#include "../Scene.h"
#include "../../Windows/WindowsFunctions.h"
#include "../Effects.h"

// Static Data Initialization
//===========================

namespace Engine
{
	namespace Graphics
	{
		HWND GraphicsSystem::s_renderingWindow = nullptr;
		IDirect3D9* s_direct3dInterface = nullptr;
		IDirect3DDevice9* s_direct3dDevice = nullptr;
		IDirect3DVertexShader9* s_vertexShader = nullptr;
		IDirect3DPixelShader9* s_fragmentShader = nullptr;
	}
}

// Helper Function Declarations
//=============================

namespace Engine
{
	namespace Graphics
	{
		bool CreateDevice();
		bool CreateInterface();
	}
}

// Interface
//==========

bool Engine::Graphics::GraphicsSystem::Initialize( const HWND i_renderingWindow )
{
	s_renderingWindow = i_renderingWindow;

	// Initialize the interface to the Direct3D9 library
	if ( !CreateInterface() )
	{
		return false;
	}
	// Create an interface to a Direct3D device
	if ( !CreateDevice() )
	{
		goto OnError;
	}
		
	return true;

OnError:

	ShutDown();
	return false;
}

void Engine::Graphics::GraphicsSystem::Render()
{
	// Every frame an entirely new image will be created.
	// Before drawing anything, then, the previous image will be erased
	// by "clearing" the image buffer (filling it with a solid color)
	{
		const D3DRECT* subRectanglesToClear = nullptr;
		const DWORD subRectangleCount = 0;
		const DWORD clearTheRenderTarget = D3DCLEAR_TARGET;
		D3DCOLOR clearColor;
		{
			// Black is usually used:
			clearColor = D3DCOLOR_XRGB( 0, 0, 0 );
		}
		const float noZBuffer = 0.0f;
		const DWORD noStencilBuffer = 0;
		HRESULT result = s_direct3dDevice->Clear( subRectangleCount, subRectanglesToClear,
			clearTheRenderTarget, clearColor, noZBuffer, noStencilBuffer );
		assert( SUCCEEDED( result ) );
	}

	// The actual function calls that draw geometry must be made between paired calls to
	// BeginScene() and EndScene()
	{
		HRESULT result = s_direct3dDevice->BeginScene();

		assert( SUCCEEDED( result ) );
		{
			Scene::drawScene();

		}
		result = s_direct3dDevice->EndScene();
		assert( SUCCEEDED( result ) );
	}

	// Everything has been drawn to the "back buffer", which is just an image in memory.
	// In order to display it, the contents of the back buffer must be "presented"
	// (to the front buffer)
	{
		const RECT* noSourceRectangle = nullptr;
		const RECT* noDestinationRectangle = nullptr;
		const HWND useDefaultWindow = nullptr;
		const RGNDATA* noDirtyRegion = nullptr;
		HRESULT result = s_direct3dDevice->Present( noSourceRectangle, noDestinationRectangle, useDefaultWindow, noDirtyRegion );
		assert( SUCCEEDED( result ) );
	}
}

bool Engine::Graphics::GraphicsSystem::ShutDown()
{
	bool wereThereErrors = false;

	if ( s_direct3dInterface )
	{
		if ( s_direct3dDevice )
		{
			
			s_direct3dDevice->Release();
			s_direct3dDevice = nullptr;
		}

		s_direct3dInterface->Release();
		s_direct3dInterface = nullptr;
	}
	s_renderingWindow = nullptr;

	return !wereThereErrors;
}

IDirect3DDevice9* Engine::Graphics::GraphicsSystem::getDevice()
{
	if(s_direct3dDevice)
		return s_direct3dDevice;
	return nullptr;
}

// Helper Function Definitions
//============================

bool Engine::Graphics::CreateDevice()
{
	HWND s_renderingWindow = Engine::Graphics::GraphicsSystem::getRenderingWindow();
	const UINT useDefaultDevice = D3DADAPTER_DEFAULT;
	const D3DDEVTYPE useHardwareRendering = D3DDEVTYPE_HAL;
	const DWORD useHardwareVertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	D3DPRESENT_PARAMETERS presentationParameters = { 0 };
	{
		{
			const unsigned int useRenderingWindowDimensions = 0;
			presentationParameters.BackBufferWidth = useRenderingWindowDimensions;
			presentationParameters.BackBufferHeight = useRenderingWindowDimensions;
		}
		presentationParameters.BackBufferFormat = D3DFMT_X8R8G8B8;
		presentationParameters.BackBufferCount = 1;
		presentationParameters.MultiSampleType = D3DMULTISAMPLE_NONE;
		presentationParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
		presentationParameters.hDeviceWindow = s_renderingWindow;
		presentationParameters.Windowed = TRUE;
		presentationParameters.EnableAutoDepthStencil = FALSE;
		presentationParameters.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	}
	HRESULT result = s_direct3dInterface->CreateDevice(useDefaultDevice, useHardwareRendering,
		s_renderingWindow, useHardwareVertexProcessing, &presentationParameters, &s_direct3dDevice);
	if (SUCCEEDED(result))
	{
		return true;
	}
	else
	{
		WindowsUtil::Print("Direct3D failed to create a Direct3D9 device");
		return false;
	}
}

bool Engine::Graphics::CreateInterface()
{
	// D3D_SDK_VERSION is #defined by the Direct3D header files,
	// and is just a way to make sure that everything is up-to-date
	s_direct3dInterface = Direct3DCreate9(D3D_SDK_VERSION);
	if (s_direct3dInterface)
	{
		return true;
	}
	else
	{
		WindowsUtil::Print("DirectX failed to create a Direct3D9 interface");
		return false;
	}
}




	
