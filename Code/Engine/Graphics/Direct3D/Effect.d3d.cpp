#include "../Effect.h"
#include "../../Windows/WindowsFunctions.h"
#include "../Graphics.h"
#include <assert.h>
#include <fstream>


bool Engine::Graphics::Effect::setShaders() const
{
	if (s_vertexShader && s_fragmentShader)
	{
		HRESULT result = GraphicsSystem::setRenderState(*renderState);
		assert(SUCCEEDED(result));
		result = GraphicsSystem::getDevice()->SetVertexShader(s_vertexShader);
		assert(SUCCEEDED(result));
		result = GraphicsSystem::getDevice()->SetPixelShader(s_fragmentShader);
		assert(SUCCEEDED(result));
		return true;
	}

	return false;
}

bool Engine::Graphics::Effect::LoadShaders()
{
	if (LoadVertexShader() && LoadFragmentShader())
		return true;
	return false;
}

Engine::Graphics::Effect::Effect(std::string i_effectFileName)
{
	s_vertexShader = nullptr;
	s_fragmentShader = nullptr;
	effectName = i_effectFileName;
	s_vertexShaderConstantTable = nullptr;
	s_fragmentShaderConstantTable = nullptr;
	renderState = new uint8_t;
	*renderState = 0;	
	isLocalToWorldTransformExist =
		isWorldToViewTransformExist =
		isViewToScreenTransformExist = false;
}

Engine::Graphics::Effect::~Effect()
{
	if (s_vertexShader)
		s_vertexShader->Release();

	if (s_fragmentShader)
		s_fragmentShader->Release();

	if (s_vertexShaderConstantTable)
		s_vertexShaderConstantTable->Release();

	if (s_fragmentShaderConstantTable)
		s_fragmentShaderConstantTable->Release();

	s_vertexShader = nullptr;
	s_fragmentShader = nullptr;
	s_vertexShaderConstantTable = nullptr;
	s_fragmentShaderConstantTable = nullptr;

	delete renderState;
}

bool Engine::Graphics::Effect::LoadVertexShader()
{
	/**************Reading the shader file**********************/
	std::ifstream readFile;
	if (!readFile.is_open())
		readFile.open(shaderNames[Vertex].c_str(), std::ifstream::binary);
	readFile.seekg(0, readFile.end);
	size_t length = static_cast<size_t>(readFile.tellg());
	readFile.seekg(0, readFile.beg);
	char* buffer = new char[length];
	readFile.read(buffer, length);
	readFile.close();
	/**************Reading the shader file**********************/

	std::stringstream errormessage;
	ID3DXBuffer* errorMessages = nullptr;
	HRESULT result = D3DXGetShaderConstantTable(reinterpret_cast<const DWORD*>(buffer),
		&s_vertexShaderConstantTable);
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
		readFile.open(shaderNames[Fragment].c_str(), std::ifstream::binary);
	readFile.seekg(0, readFile.end);
	size_t length = static_cast<size_t>(readFile.tellg());
	readFile.seekg(0, readFile.beg);
	char* buffer = new char[length];
	readFile.read(buffer, length);
	readFile.close();
	/**************Reading the shader file**********************/

	{
		HRESULT result = D3DXGetShaderConstantTable(reinterpret_cast<const DWORD*>(buffer),
			&s_fragmentShaderConstantTable);
	}

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

void Engine::Graphics::Effect::setMaterialUniformValue(char* i_uniformName,
	MaterialUniform i_material_uniform) const
{
	HRESULT result = FALSE;
	switch (i_material_uniform.type)
	{
	case Engine::Graphics::Vertex:
		result |= s_vertexShaderConstantTable->SetFloatArray(Engine::Graphics::GraphicsSystem::getDevice(),
			i_material_uniform.Handle, i_material_uniform.values, i_material_uniform.valCount);
		break;
	case Engine::Graphics::Fragment:
		result |= s_fragmentShaderConstantTable->SetFloatArray(Engine::Graphics::GraphicsSystem::getDevice(),
			i_material_uniform.Handle, i_material_uniform.values, i_material_uniform.valCount);
		break;
	default:
		break;
	}

	if (!SUCCEEDED(result))
	{
		std::stringstream errormessage;
		errormessage << "Unable to set the Uniform position";
		WindowsUtil::Print(errormessage.str());
	}
}

void Engine::Graphics::Effect::setTextureUniform(TextureResource i_textureResource,
	SamplerID i_textureSamplerID, int i_textureUnit)
{
	HRESULT result = Engine::Graphics::GraphicsSystem::getDevice()->SetTexture(i_textureSamplerID, i_textureResource);
	if (!SUCCEEDED(result))
	{
		WindowsUtil::Print("Unable to set the Texture");
	}
}

Engine::Graphics::UniformHandle Engine::Graphics::Effect::getUniformHandle(const char* i_uniformName,
	ShaderType i_shaderType) const
{
	UniformHandle handle = nullptr;
	switch (i_shaderType)
	{
	case Engine::Graphics::Vertex:
		handle = reinterpret_cast<char*>(const_cast<char*>((s_vertexShaderConstantTable->GetConstantByName(nullptr, i_uniformName))));
		break;
	case Engine::Graphics::Fragment:
		handle = reinterpret_cast<char*>(const_cast<char*>((s_fragmentShaderConstantTable->GetConstantByName(nullptr, i_uniformName))));
		break;
	default:
		break;
	}

	if (!handle)
	{
		WindowsUtil::Print("\nUnable to get the handle\n");
	}
	return handle;
}

Engine::Graphics::SamplerID Engine::Graphics::Effect::getSamplerID(UniformHandle i_handle, ShaderType i_shaderType)
{
	SamplerID sampleID = 0xFFFF;
	switch (i_shaderType)
	{
	case Engine::Graphics::Vertex:
		sampleID = static_cast<DWORD>(s_vertexShaderConstantTable->GetSamplerIndex(i_handle));
		break;
	case Engine::Graphics::Fragment:
		sampleID = static_cast<DWORD>(s_fragmentShaderConstantTable->GetSamplerIndex(i_handle));
		break;
	case Unknown:
		break;
	}

	if (sampleID == 0xFFFF)
		WindowsUtil::Print("D3D is unable to get the sampler Id for the texture");

	return sampleID;
}


const ID3DXConstantTable* Engine::Graphics::Effect::getConstantTable(ShaderType iType) const
{
	switch(iType)
	{
	case Vertex:
		return s_vertexShaderConstantTable;		
	case Fragment:
		return s_fragmentShaderConstantTable;		
	default:
		return nullptr;
	}
}











