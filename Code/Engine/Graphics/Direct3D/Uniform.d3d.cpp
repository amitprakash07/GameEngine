#include "../Uniform.h"
#include "../uniformdefs.h"
#include "../../Windows/WindowsFunctions.h"
#include "../Graphics.h"
#include "../Effect.h"


Engine::Graphics::UniformData::UniformData()
{
	uniformName = nullptr;
	handle = nullptr;
	valType = NotKnown;
	valCount = 0xFF;
	shaderType = Unknown;
}

void Engine::Graphics::Uniform::setValueInShaderObject(const ID3DXConstantTable* constantTable) const
{
	HRESULT result = TRUE;
	WindowsUtil::Assert(mUniform.handle != nullptr, "There is no handle");
	switch (mUniform.valType)
	{
	case Bool:
		result &= (const_cast<ID3DXConstantTable*>(constantTable))->SetBool(Engine::Graphics::GraphicsSystem::getDevice(),
			mUniform.handle, mUniform.value.boolValue);
		break;
	case BoolArray:
		result &= (const_cast<ID3DXConstantTable*>(constantTable))->SetBoolArray(Engine::Graphics::GraphicsSystem::getDevice(),
			mUniform.handle, reinterpret_cast<const BOOL*>(mUniform.value.boolArray), mUniform.valCount);
		break;
	case Int:
		result &= (const_cast<ID3DXConstantTable*>(constantTable))->SetInt(Engine::Graphics::GraphicsSystem::getDevice(),
			mUniform.handle, mUniform.value.intValue);
		break;
	case IntArray:
		result &= (const_cast<ID3DXConstantTable*>(constantTable))->SetIntArray(Engine::Graphics::GraphicsSystem::getDevice(),
			mUniform.handle, reinterpret_cast<const INT*>(mUniform.value.intArray), mUniform.valCount);
		break;
	case Float:
		result &= (const_cast<ID3DXConstantTable*>(constantTable))->SetFloat(Engine::Graphics::GraphicsSystem::getDevice(),
			mUniform.handle, mUniform.value.floatValue);
		break;
	case FloatArray:
		result &= (const_cast<ID3DXConstantTable*>(constantTable))->SetFloatArray(Engine::Graphics::GraphicsSystem::getDevice(),
			mUniform.handle, reinterpret_cast<const FLOAT*>(mUniform.value.floatArray), mUniform.valCount);
		break;
	case Matrix:
		result &= (const_cast<ID3DXConstantTable*>(constantTable))->SetMatrixTranspose(Engine::Graphics::GraphicsSystem::getDevice(),
			mUniform.handle, reinterpret_cast<const D3DXMATRIX*>(&mUniform.value.matrixValue));
		break;
	case MatrixArray:
		result &= (const_cast<ID3DXConstantTable*>(constantTable))->SetMatrixArray(Engine::Graphics::GraphicsSystem::getDevice(),
			mUniform.handle, reinterpret_cast<const D3DXMATRIX*>(mUniform.value.matrixArray), mUniform.valCount);
		break;
	case Vector:
		result &= (const_cast<ID3DXConstantTable*>(constantTable))->SetVector(Engine::Graphics::GraphicsSystem::getDevice(),
			mUniform.handle, reinterpret_cast<const D3DXVECTOR4*>(&mUniform.value.vectorValue));
		break;
	case VectorArray:
		result &= (const_cast<ID3DXConstantTable*>(constantTable))->SetVectorArray(Engine::Graphics::GraphicsSystem::getDevice(),
			mUniform.handle, reinterpret_cast<const D3DXVECTOR4*>(mUniform.value.vectorArray), mUniform.valCount);
		break;
	case NotKnown:
		break;
	}
}


void Engine::Graphics::Uniform::setAllUniformToShaderObjects()
{
	for (std::map<std::string, SharedPointer<Uniform>>::iterator i = mUniformListInSystem.begin();
	i!= mUniformListInSystem.end(); ++i)
	{
		i->second->setValueInShaderObject(
			Effect::getEffect(i->second->effectName)->getConstantTable(i->second->mUniform.shaderType));
	}
}

