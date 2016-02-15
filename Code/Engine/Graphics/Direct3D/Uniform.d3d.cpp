#include "../Uniform.h"
#include "../uniformdefs.h"
#include "../../Windows/WindowsFunctions.h"
#include "../Graphics.h"


Engine::Graphics::UniformData::UniformData()
{
	uniformName = nullptr;
	handle = nullptr;
	valType = NotKnown;
	valCount = 0xFF;
	shaderType = Unknown;
}

void Engine::Graphics::Uniform::setValueInShaderObject(ID3DXConstantTable* constantTable) const
{
	HRESULT result = TRUE;
	switch (mUniform.valType)
	{
	case Bool:
		result &= constantTable->SetBool(Engine::Graphics::GraphicsSystem::getDevice(),
			mUniform.handle, mUniform.value.boolValue);
		break;
	case BoolArray:
		result &= constantTable->SetBoolArray(Engine::Graphics::GraphicsSystem::getDevice(),
			mUniform.handle, reinterpret_cast<const BOOL*>(mUniform.value.boolArray), mUniform.valCount);
		break;
	case Int:
		result &= constantTable->SetInt(Engine::Graphics::GraphicsSystem::getDevice(),
			mUniform.handle, mUniform.value.intValue);
		break;
	case IntArray:
		result &= constantTable->SetIntArray(Engine::Graphics::GraphicsSystem::getDevice(),
			mUniform.handle, reinterpret_cast<const INT*>(mUniform.value.intArray), mUniform.valCount);
		break;
	case Float:
		result &= constantTable->SetFloat(Engine::Graphics::GraphicsSystem::getDevice(),
			mUniform.handle, mUniform.value.floatValue);
		break;
	case FloatArray:
		result &= constantTable->SetFloatArray(Engine::Graphics::GraphicsSystem::getDevice(),
			mUniform.handle, reinterpret_cast<const FLOAT*>(mUniform.value.floatArray), mUniform.valCount);
		break;
	case Matrix:
		result &= constantTable->SetMatrixTranspose(Engine::Graphics::GraphicsSystem::getDevice(),
			mUniform.handle, reinterpret_cast<const D3DXMATRIX*>(&mUniform.value.matrixValue));
		break;
	case MatrixArray:
		result &= constantTable->SetMatrixArray(Engine::Graphics::GraphicsSystem::getDevice(),
			mUniform.handle, reinterpret_cast<const D3DXMATRIX*>(mUniform.value.matrixArray), mUniform.valCount);
		break;
	case Vector:
		result &= constantTable->SetVector(Engine::Graphics::GraphicsSystem::getDevice(),
			mUniform.handle, reinterpret_cast<const D3DXVECTOR4*>(&mUniform.value.vectorValue));
		break;
	case VectorArray:
		result &= constantTable->SetVectorArray(Engine::Graphics::GraphicsSystem::getDevice(),
			mUniform.handle, reinterpret_cast<const D3DXVECTOR4*>(mUniform.value.vectorArray), mUniform.valCount);
		break;
	case NotKnown:
		break;
	}
}

