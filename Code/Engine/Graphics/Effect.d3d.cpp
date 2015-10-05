
#include "Effect.h"
#include "../Windows/WindowsFunctions.h"
#include "Graphics.h"
#include <assert.h>

bool Engine::Graphics::Effect::setShaders()
{
	if (LoadVertexShader() && LoadFragmentShader())
	{
		{
			HRESULT result = GraphicsSystem::getDevice()->SetVertexShader(s_vertexShader);
			assert(SUCCEEDED(result));
			result = GraphicsSystem::getDevice()->SetPixelShader(s_fragmentShader);
			assert(SUCCEEDED(result));
			return true;
		}
	}
	return false;
}

Engine::Graphics::Effect::Effect(std::string i_vertexShader, std::string i_fragmentShader)
{
	s_vertexShader = nullptr;
	s_fragmentShader = nullptr;
	vertexShader = i_vertexShader;
	fragmentShader = i_fragmentShader;
}

Engine::Graphics::Effect::~Effect()
{
	if (s_vertexShader)
		s_vertexShader->Release();
		
	if (s_fragmentShader)
		s_fragmentShader->Release();

	s_vertexShader = nullptr;
	s_fragmentShader = nullptr;

}

bool Engine::Graphics::Effect::LoadVertexShader()
{
	// Load the source code from file and compile it
	ID3DXBuffer* compiledShader;
	{
		const char* sourceCodeFileName = vertexShader.c_str();//@Amit- To do to change the file name
		const D3DXMACRO vertexShaderMacro[] =   //@Amit - now macro is not null changed to access the #defined platform code in shader file 
		{
			{ "PLATFORM_D3D", "1" },
			{ NULL,NULL }
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
		HRESULT result = GraphicsSystem::getDevice()->CreateVertexShader(reinterpret_cast<DWORD*>(compiledShader->GetBufferPointer()),
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

bool Engine::Graphics::Effect::LoadFragmentShader()
{
	// Load the source code from file and compile it
	ID3DXBuffer* compiledShader;
	{
		const char* sourceCodeFileName = fragmentShader.c_str(); //@Amit- To do to change the file name
		const D3DXMACRO fragmentShaderMacro[] =   //@Amit - now macro is not null changed to access the #defined platform code in shader file 
		{
			{ "PLATFORM_D3D" , "1" },
			{ NULL,NULL }
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
		HRESULT result = GraphicsSystem::getDevice()->CreatePixelShader(reinterpret_cast<DWORD*>(compiledShader->GetBufferPointer()),
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

