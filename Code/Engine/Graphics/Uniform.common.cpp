#include "Uniform.h"
#include "../Windows/WindowsFunctions.h"
#include "Effect.h"

std::map<std::string, Engine::SharedPointer<Engine::Graphics::Uniform>>
Engine::Graphics::Uniform::mUniformListInSystem;

Engine::Graphics::Uniform::Uniform()
{
	mUniform.uniformName = nullptr;	
}

Engine::SharedPointer<Engine::Graphics::Uniform> 
Engine::Graphics::Uniform::addUniform(
	std::string iUniformName,
	std::string effectFileName, 
	ShaderType iShaderType)
{
	if (!isUnformExist(iUniformName, effectFileName, iShaderType))
	{
		SharedPointer<Uniform> tempUniform =
			SharedPointer<Uniform>(new Uniform(), "Engine::Graphics::Uniform");
		char * tempUniformName = new char[iUniformName.size()];
		strcpy(tempUniformName, iUniformName.c_str());
		tempUniform->setName(tempUniformName);
		tempUniform->effectName = effectFileName;
		tempUniform->setShaderType(iShaderType);
		mUniformListInSystem[tempUniform->prefixUniformName()] = tempUniform;
		return tempUniform;
	}
	return (getUniform(iUniformName, effectFileName, iShaderType));
}

void Engine::Graphics::Uniform::setUniformValue(UniformValues& iinitialValue)
{
	switch (mUniform.valType)
	{
	case Bool:
		mUniform.value.boolValue = iinitialValue.boolValue;
		break;
	case BoolArray:
		WindowsUtil::Assert(mUniform.valCount > 1, "Array Length is One");
		if (mUniform.value.boolArray == nullptr)
			mUniform.value.boolArray = new bool[mUniform.valCount];
		memcpy(mUniform.value.boolArray, iinitialValue.boolArray, sizeof(bool)* mUniform.valCount);
		break;
	case Int:
		mUniform.value.intValue = iinitialValue.intValue;
		break;
	case IntArray:
		WindowsUtil::Assert(mUniform.valCount > 1, "Array Length is One");
		if (mUniform.value.intArray == nullptr)
			mUniform.value.intArray = new int[mUniform.valCount];
		memcpy(mUniform.value.intArray, iinitialValue.intArray, sizeof(int)* mUniform.valCount);
		break;
	case Float:
		mUniform.value.floatValue = iinitialValue.floatValue;
		break;
	case FloatArray:
		WindowsUtil::Assert(mUniform.valCount > 1, "Array Length is One");
		if (mUniform.value.floatArray == nullptr)
			mUniform.value.floatArray = new float[mUniform.valCount];
		memcpy(mUniform.value.floatArray, iinitialValue.floatArray, sizeof(float)* mUniform.valCount);
		break;
	case Matrix:
		mUniform.value.matrixValue.matrix = iinitialValue.matrixValue.matrix;
		break;
	case MatrixArray:
		WindowsUtil::Assert(mUniform.valCount > 1, "Array Length is One");
		if (mUniform.value.matrixArray == nullptr)
			mUniform.value.matrixArray = new MatrixStruct[mUniform.valCount];
		memcpy(mUniform.value.matrixArray, iinitialValue.matrixArray, sizeof(MatrixStruct)* mUniform.valCount);
		break;
	case Vector:
		mUniform.value.vectorValue = iinitialValue.vectorValue;
		break;
	case VectorArray:
		WindowsUtil::Assert(mUniform.valCount > 1, "Array Length is One");
		if (mUniform.value.vectorArray == nullptr)
			mUniform.value.vectorArray = new VectorStruct[mUniform.valCount];
		memcpy(mUniform.value.vectorArray, iinitialValue.vectorArray, sizeof(VectorStruct)* mUniform.valCount);
		break;
	case NotKnown:
		break;
	}
}

void Engine::Graphics::Uniform::setName(char* iUniformName)
{
	if (iUniformName != nullptr)
	{
		int length = static_cast<int>(strlen(iUniformName));
		mUniform.uniformName = new char[length];
		memcpy(mUniform.uniformName, iUniformName, length);
		mUniform.uniformName[length] = '\0';
	}
}

void Engine::Graphics::Uniform::setMatrixType(Transform_Matrix_Type iMatrixType)
{
	WindowsUtil::Assert(mUniform.valType == Matrix || mUniform.valType == MatrixArray,
		"Data type is Not Matrix");
	if (mUniform.valCount == 1)
		mUniform.value.matrixValue.Type = iMatrixType;
	else
	{
		for (int i = 0; i < mUniform.valCount; ++i)
		{
			if (mUniform.value.matrixArray == nullptr)
			{
				mUniform.value.matrixArray = new MatrixStruct[mUniform.valCount];
			}
			mUniform.value.matrixArray[i].Type = iMatrixType;
		}
	}
}

void Engine::Graphics::Uniform::setHandle(UniformHandle iHandle)
{
	mUniform.handle = iHandle;
}

void Engine::Graphics::Uniform::setShaderType(ShaderType iShaderType)
{
	mUniform.shaderType = iShaderType;
}

void Engine::Graphics::Uniform::setValCount(uint8_t iCount)
{
	mUniform.valCount = iCount;
}

void Engine::Graphics::Uniform::setValType(UniformDataType iDataType)
{
	mUniform.valType = iDataType;
}

Engine::Graphics::Uniform::~Uniform()
{
	if (mUniform.uniformName)
		delete mUniform.uniformName;
	switch (mUniform.valType)
	{
	case IntArray:
		delete mUniform.value.intArray;
		break;
	case FloatArray:
		delete mUniform.value.floatArray;
		break;
	case MatrixArray:
		delete mUniform.value.matrixArray;
		break;
	case VectorArray:
		delete mUniform.value.vectorArray;
		break;
	default:
		break;
	}
}

char* Engine::Graphics::Uniform::prefixUniformName() const
{
	std::string prefixedNameWithEffect;
	switch (mUniform.shaderType)
	{
	case Vertex:
		prefixedNameWithEffect += "V";		
		break;
	case Fragment:
		prefixedNameWithEffect += "F";
		break;
	case Tessalation:
		prefixedNameWithEffect += "T";
		break;
	case Geometry:
		prefixedNameWithEffect += "G";
		break;
	case Compute:
		prefixedNameWithEffect += "C";
		break;
	case Unknown:
		prefixedNameWithEffect += "U";
		break;
	}

	prefixedNameWithEffect += effectName;
	prefixedNameWithEffect += mUniform.uniformName;
	char * prefixedName = new char[prefixedNameWithEffect.size()];
	memcpy(prefixedName, prefixedNameWithEffect.c_str(), prefixedNameWithEffect.size());
	prefixedName[prefixedNameWithEffect.size()] = '\0';
	return prefixedName;
}

Engine::Graphics::UniformHandle Engine::Graphics::Uniform::getHandle() const
{
	return mUniform.handle;
}

Engine::Graphics::Transform_Matrix_Type Engine::Graphics::Uniform::getMatrixType() const
{
	return mUniform.value.matrixValue.Type;
}

Engine::Graphics::ShaderType Engine::Graphics::Uniform::getShaderType() const
{
	return mUniform.shaderType;
}

Engine::SharedPointer<Engine::Graphics::Uniform> Engine::Graphics::Uniform::getUniform(
	std::string uniformName,
	std::string effectFileName,
	ShaderType iShaderType)
{
	for (std::map<std::string, SharedPointer<Uniform>>::iterator i = mUniformListInSystem.begin();
	i!=mUniformListInSystem.end(); ++i)
	{
		if (strcmp(i->second->getUniformName(), uniformName.c_str()) == 0 &&
			strcmp(i->second->effectName.c_str(), effectFileName.c_str()) == 0 &&
			i->second->getShaderType() == iShaderType)
			return i->second;
	}
	return SharedPointer<Uniform>();
}

bool Engine::Graphics::Uniform::isUnformExist(std::string i_UniformNamae, 
	std::string effectName, 
	ShaderType iShaderType)
{
	if (mUniformListInSystem.size() > 0)
	{
		SharedPointer<Uniform> tempUniform
			= getUniform(i_UniformNamae, effectName, iShaderType);
		if (tempUniform.isNull())
			return false;
		return true;
	}
	return false;
}


Engine::Graphics::UniformDataType Engine::Graphics::Uniform::getUniformDataType() const
{
	return mUniform.valType;
}

const char* Engine::Graphics::Uniform::getUniformName() const
{
	return mUniform.uniformName;
}

//Engine::Graphics::UniformValues Engine::Graphics::Uniform::getUniformValues() 
//{
//	UniformValues tempUniformValues = mUniform.value;
//	return mUniform.value;
//}

uint8_t Engine::Graphics::Uniform::getValueCount() const
{
	return mUniform.valCount;
}


void Engine::Graphics::Uniform::setUniformValueToShaderObject(
	std::string effect, 
	std::string uniformName,
	ShaderType iShaderType)
{
	
}














