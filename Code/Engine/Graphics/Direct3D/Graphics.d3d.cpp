// Header Files
//=============

#include "../Graphics.h"
#include <d3dx9shader.h>
#include <cassert>
#include "../Scene.h"
#include "../../Windows/WindowsFunctions.h"

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
		bool LoadFragmentShader();
		bool LoadVertexShader();
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

	// Initialize the graphics objects
	if ( !LoadVertexShader() )
	{
		goto OnError;
	}
	if ( !LoadFragmentShader() )
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
			// Set the shaders
			{
				result = s_direct3dDevice->SetVertexShader( s_vertexShader );
				assert( SUCCEEDED( result ) );
				result = s_direct3dDevice->SetPixelShader( s_fragmentShader );
				assert( SUCCEEDED( result ) );
			}

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
			if ( s_vertexShader )
			{
				s_vertexShader->Release();
				s_vertexShader = nullptr;
			}
			if ( s_fragmentShader )
			{
				s_fragmentShader->Release();
				s_fragmentShader = nullptr;
			}

			/*if ( s_vertexBuffer )
			{
				s_vertexBuffer->Release();
				s_vertexBuffer = nullptr;
			}
			if ( s_indexBuffer )
			{
				s_indexBuffer->Release();
				s_indexBuffer = nullptr;
			}
			if ( s_vertexDeclaration )
			{
				s_direct3dDevice->SetVertexDeclaration(nullptr);
				s_vertexDeclaration->Release();
				s_vertexDeclaration = nullptr;
			}*/

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

bool Engine::Graphics::LoadFragmentShader()
{
	// Load the source code from file and compile it
	ID3DXBuffer* compiledShader;
	{
		const char* sourceCodeFileName = "data/standard.fshd"; //@Amit- To do to change the file name
		const D3DXMACRO fragmentShaderMacro[] =   //@Amit - now macro is not null changed to access the #defined platform code in shader file 
		{
			{"PLATFORM_D3D" , "1" },
			{NULL,NULL}
		};

		ID3DXInclude* noIncludes = nullptr;
		const char* entryPoint = "main";
		const char* profile = "ps_3_0";
		const DWORD noFlags = 0;
		ID3DXBuffer* errorMessages = nullptr;
		ID3DXConstantTable** noConstants = nullptr;
		HRESULT result = D3DXCompileShaderFromFile(sourceCodeFileName, fragmentShaderMacro, noIncludes, entryPoint, profile, noFlags,
			&compiledShader, &errorMessages, noConstants);
		if (SUCCEEDED(result))
		{
			if (errorMessages)
			{
				errorMessages->Release();
			}
		}
		else
		{
			if (errorMessages)
			{
				std::stringstream errorMessage;
				errorMessage << "Direct3D failed to compile the fragment shader from the file " << sourceCodeFileName
					<< ":\n" << reinterpret_cast<char*>(errorMessages->GetBufferPointer());
				WindowsUtil::Print(errorMessage.str());
				errorMessages->Release();
			}
			else
			{
				std::stringstream errorMessage;
				errorMessage << "Direct3D failed to compile the fragment shader from the file " << sourceCodeFileName;
				WindowsUtil::Print(errorMessage.str());
			}
			return false;
		}
	}
	// Create the fragment shader object
	bool wereThereErrors = false;
	{
		HRESULT result = s_direct3dDevice->CreatePixelShader(reinterpret_cast<DWORD*>(compiledShader->GetBufferPointer()),
			&s_fragmentShader);
		if (FAILED(result))
		{
			WindowsUtil::Print("Direct3D failed to create the fragment shader");
			wereThereErrors = true;
		}
		compiledShader->Release();
	}
	return !wereThereErrors;
}

bool Engine::Graphics::LoadVertexShader()
{
	// Load the source code from file and compile it
	ID3DXBuffer* compiledShader;
	{
		const char* sourceCodeFileName = "data/standard.vshd";//@Amit- To do to change the file name
		const D3DXMACRO vertexShaderMacro[] =   //@Amit - now macro is not null changed to access the #defined platform code in shader file 
		{
			{ "PLATFORM_D3D", "1" },
			{NULL,NULL}
		};
		ID3DXInclude* noIncludes = nullptr;
		const char* entryPoint = "main";
		const char* profile = "vs_3_0";
		const DWORD noFlags = 0;
		ID3DXBuffer* errorMessages = nullptr;
		ID3DXConstantTable** noConstants = nullptr;
		HRESULT result = D3DXCompileShaderFromFile(sourceCodeFileName, vertexShaderMacro, noIncludes, entryPoint, profile, noFlags,
			&compiledShader, &errorMessages, noConstants);
		if (SUCCEEDED(result))
		{
			if (errorMessages)
			{
				errorMessages->Release();
			}
		}
		else
		{
			if (errorMessages)
			{
				std::stringstream errorMessage;
				errorMessage << "Direct3D failed to compile the vertex shader from the file " << sourceCodeFileName
					<< ":\n" << reinterpret_cast<char*>(errorMessages->GetBufferPointer());
				WindowsUtil::Print(errorMessage.str());
				errorMessages->Release();
			}
			else
			{
				std::stringstream errorMessage;
				errorMessage << "Direct3D failed to compile the vertex shader from the file " << sourceCodeFileName;
				WindowsUtil::Print(errorMessage.str());
			}
			return false;
		}
	}
	// Create the vertex shader object
	bool wereThereErrors = false;
	{
		HRESULT result = s_direct3dDevice->CreateVertexShader(reinterpret_cast<DWORD*>(compiledShader->GetBufferPointer()),
			&s_vertexShader);
		if (FAILED(result))
		{
			WindowsUtil::Print("Direct3D failed to create the vertex shader");
			wereThereErrors = true;
		}
		compiledShader->Release();
	}
	return !wereThereErrors;
}
	
