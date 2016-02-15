#include "Uniform.h"
#include "../Windows/WindowsFunctions.h"


Engine::Graphics::Uniform::Uniform()
{
	mUniform.uniformName = nullptr;
}

Engine::SharedPointer<Engine::Graphics::Uniform> Engine::Graphics::Uniform::createUniform()
{
	return(SharedPointer<Uniform>(new Uniform, "Engine::Graphics::Uniform"));
}

void Engine::Graphics::Uniform::setUniformValue(UniformValues iinitialValue)
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
		if (mUniform.value.intArray == nullptr)
			mUniform.value.floatArray = new float[mUniform.valCount];
		memcpy(mUniform.value.floatArray, iinitialValue.floatArray, sizeof(float)* mUniform.valCount);
		break;
	case Matrix:
		mUniform.value.matrixValue = iinitialValue.matrixValue;
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
		int length = strlen(iUniformName);
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
	int uniformNameLength = strlen(mUniform.uniformName);
	char* prefixedName = new char[uniformNameLength + 1];
	char charToPrefix;
	switch (mUniform.shaderType)
	{
	case Vertex:
		charToPrefix = 'V';
		memcpy(prefixedName, &charToPrefix, 1);
		break;
	case Fragment:
		charToPrefix = 'F';
		memcpy(prefixedName, &charToPrefix, 1);
		break;
	case Tessalation:
		charToPrefix = 'T';
		memcpy(prefixedName, &charToPrefix, 1);
		break;
	case Geometry:
		charToPrefix = 'G';
		memcpy(prefixedName, &charToPrefix, 1);
		break;
	case Compute:
		charToPrefix = 'C';
		memcpy(prefixedName, &charToPrefix, 1);
		break;
	case Unknown:
		charToPrefix = 'U';
		memcpy(prefixedName, &charToPrefix, 1);
		break;
	}

	memcpy(prefixedName + 1, mUniform.uniformName, uniformNameLength);
	prefixedName[uniformNameLength + 1] = '\0';
	return prefixedName;
}