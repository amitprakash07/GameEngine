#include "../Effect.h"
#include "../../Windows/WindowsFunctions.h"
#include "../Graphics.h"
#include <assert.h>
#include <fstream>


bool Engine::Graphics::Effect::setShaders()
{
	if (s_vertexShader && s_fragmentShader)
	{
		HRESULT result = GraphicsSystem::getDevice()->SetVertexShader(s_vertexShader);
		assert(SUCCEEDED(result));
		result = GraphicsSystem::getDevice()->SetPixelShader(s_fragmentShader);
		assert(SUCCEEDED(result));
		return true;
	}
	else
		return false;
}

bool Engine::Graphics::Effect::LoadShaders()
{
	if (LoadVertexShader() && LoadFragmentShader())
		return true;
	return false;
}


Engine::Graphics::Effect::Effect(std::string i_shaderName, std::string i_effectFileName)
{
	s_vertexShader = nullptr;
	s_fragmentShader = nullptr;
	shaderName = i_shaderName;
	s_constantsTable = nullptr;
	s_uniformPositionOffset = nullptr;
	effectFileName = i_effectFileName;
}

Engine::Graphics::Effect::~Effect()
{
	if (s_vertexShader)
		s_vertexShader->Release();
		
	if (s_fragmentShader)
		s_fragmentShader->Release();

	if (s_constantsTable)
		s_constantsTable->Release();

	//if (s_uniformPositionOffset)
	//	delete s_uniformPositionOffset;

	s_uniformPositionOffset = nullptr;
	s_vertexShader = nullptr;
	s_fragmentShader = nullptr;
	s_constantsTable = nullptr;


}

bool Engine::Graphics::Effect::LoadVertexShader()
{
	/**************Reading the shader file**********************/
	std::ifstream readFile;
	if (!readFile.is_open())
		readFile.open(vertexShader.c_str(), std::ifstream::binary);
	readFile.seekg(0, readFile.end);
	size_t length = static_cast<size_t>(readFile.tellg());
	readFile.seekg(0, readFile.beg);
	char* buffer = new char[length];
	readFile.read(buffer, length);
	readFile.close();
	/**************Reading the shader file**********************/
	
	std::stringstream errormessage;
	ID3DXBuffer* errorMessages = nullptr;
		

		HRESULT result = D3DXGetShaderConstantTable(reinterpret_cast<const DWORD*>(buffer), &s_constantsTable);

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
				errorMessage << "Direct3D failed to compile the vertex shader from the file " << vertexShader.c_str()
					<< ":\n" << reinterpret_cast<char*>(errorMessages->GetBufferPointer());
				WindowsUtil::Print(errorMessage.str());
				errorMessages->Release();
			}
			else
			{
				std::stringstream errorMessage;
				errorMessage << "Direct3D failed to compile the vertex shader from the file " << vertexShader.c_str();
				WindowsUtil::Print(errorMessage.str());
			}
			return false;
		}
	
	// Create the vertex shader object
	bool wereThereErrors = false;
	{
		result = GraphicsSystem::getDevice()->CreateVertexShader(reinterpret_cast<DWORD*>(buffer),
			&s_vertexShader);
		if (FAILED(result))
		{
			WindowsUtil::Print("Direct3D failed to create the vertex shader");
			wereThereErrors = true;
		}
		delete buffer;
	}
	return !wereThereErrors;
}

bool Engine::Graphics::Effect::LoadFragmentShader()
{
		/**************Reading the shader file**********************/
		std::ifstream readFile;
		if (!readFile.is_open())
			readFile.open(fragmentShader.c_str(), std::ifstream::binary);
		readFile.seekg(0, readFile.end);
		size_t length = static_cast<size_t>(readFile.tellg());
		readFile.seekg(0, readFile.beg);
		char* buffer = new char[length];
		readFile.read(buffer, length);
		readFile.close();
		/**************Reading the shader file**********************/
		

	// Create the fragment shader object
	bool wereThereErrors = false;
	{
		HRESULT result = GraphicsSystem::getDevice()->CreatePixelShader(reinterpret_cast<DWORD*>(buffer),
			&s_fragmentShader);
		if (FAILED(result))
		{
			WindowsUtil::Print("Direct3D failed to create the fragment shader");
			wereThereErrors = true;
		}
		
		delete buffer;
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

