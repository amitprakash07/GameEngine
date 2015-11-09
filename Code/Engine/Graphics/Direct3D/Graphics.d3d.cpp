// Header Files
//=============

#include "../Graphics.h"
#include <cassert>
#include "../../Windows/WindowsFunctions.h"
#include "../../Core/EngineCore/Objects/Scene.h"

#pragma warning(disable :4006)

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

bool Engine::Graphics::GraphicsSystem::create()
{
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

void Engine::Graphics::GraphicsSystem::showBuffer()
{
	// Everything has been drawn to the "back buffer", which is just an image in memory.
	// In order to display it, the contents of the back buffer must be "presented"
	// (to the front buffer)
	const RECT* noSourceRectangle = nullptr;
	const RECT* noDestinationRectangle = nullptr;
	const HWND useDefaultWindow = nullptr;
	const RGNDATA* noDirtyRegion = nullptr;
	HRESULT result = s_direct3dDevice->Present( noSourceRectangle, noDestinationRectangle, useDefaultWindow, noDirtyRegion );
	assert( SUCCEEDED( result ) );
}

void Engine::Graphics::GraphicsSystem::beginScene()
{
	HRESULT result = s_direct3dDevice->BeginScene();
	assert(SUCCEEDED(result));
}

void Engine::Graphics::GraphicsSystem::endScene()
{
	HRESULT result = s_direct3dDevice->EndScene();;
	assert(SUCCEEDED(result));
}

bool Engine::Graphics::GraphicsSystem::clear()
{
	// Every frame an entirely new image will be created.
	// Before drawing anything, then, the previous image will be erased
	// by "clearing" the image buffer (filling it with a solid color)
	const D3DRECT* subRectanglesToClear = nullptr;
	const DWORD subRectangleCount = 0;
	const DWORD clearTheRenderTarget = D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER;
	D3DCOLOR clearColor;
	{
		// Black is usually used:
		clearColor = D3DCOLOR_XRGB(0, 0, 0);
	}
	const float zBufferDepth = 1.0f;
	const DWORD noStencilBuffer = 0;
	HRESULT result = s_direct3dDevice->Clear(subRectangleCount, subRectanglesToClear,
		clearTheRenderTarget, clearColor, zBufferDepth, noStencilBuffer);

	if (SUCCEEDED(result))
		return true;
	return false;
}

bool Engine::Graphics::GraphicsSystem::destroy()
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
		presentationParameters.EnableAutoDepthStencil = TRUE; //Changing from False to enable DepthBuffer
		presentationParameters.AutoDepthStencilFormat = D3DFMT_D16;

		presentationParameters.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	}
	HRESULT result = s_direct3dInterface->CreateDevice(useDefaultDevice, useHardwareRendering,
		s_renderingWindow, useHardwareVertexProcessing, &presentationParameters, &s_direct3dDevice);
	
	result |= s_direct3dDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	result |= s_direct3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	result |= s_direct3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
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




	
