#include "../Effect.h"
#include "../../Windows/WindowsFunctions.h"
#include "../Graphics.h"
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

Engine::Graphics::Effect::Effect(std::string i_shaderName, std::string i_vertexShader, std::string i_fragmentShader)
{
	s_vertexShader = nullptr;
	s_fragmentShader = nullptr;
	shaderName = i_shaderName;
	vertexShader = i_vertexShader;
	fragmentShader = i_fragmentShader;
	s_constantsTable = nullptr;
	s_uniformPositionOffset = nullptr;
}

Engine::Graphics::Effect::~Effect()
{
	if (s_vertexShader)
		s_vertexShader->Release();
		
	if (s_fragmentShader)
		s_fragmentShader->Release();

	if (s_constantsTable)
		s_constantsTable->Release();

	if (s_uniformPositionOffset)
		delete s_uniformPositionOffset;

	s_uniformPositionOffset = nullptr;
	s_vertexShader = nullptr;
	s_fragmentShader = nullptr;
	s_constantsTable = nullptr;


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
		//ID3DXConstantTable** noConstants = nullptr;
		HRESULT result = D3DXCompileShaderFromFile(sourceCodeFileName, vertexShaderMacro, noIncludes, entryPoint, profile, noFlags,
			&compiledShader, &errorMessages, &s_constantsTable); //@ Amit for constant table
		if (SUCCEEDED(result))
		{
			s_uniformPositionOffset = s_constantsTable->GetConstantByName(nullptr, "g_position_offset"); //@Amit for getting the position offset
			if(s_uniformPositionOffset == nullptr)
			{
				std::stringstream errormessage_another;
				errormessage_another << "Unable to get the Handle for the uniform offset";
				WindowsUtil::Print(errormessage_another.str());
			}
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

void Engine::Graphics::Effect::setPositionOffset(Engine::Math::cVector i_positionOffset)
{
	FLOAT *temp = new FLOAT[2];
	temp[0] = i_positionOffset.x;
	temp[1] = i_positionOffset.y;
	HRESULT result = s_constantsTable->SetFloatArray(Engine::Graphics::GraphicsSystem::getDevice(), s_uniformPositionOffset, temp, 2);
	if(!SUCCEEDED(result))
	{
		std::stringstream errormessage;
		errormessage << "Unable to set the Uniform position";
		WindowsUtil::Print(errormessage.str());
	}
	delete temp;
}

