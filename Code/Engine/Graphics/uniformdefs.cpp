#include "uniformdefs.h"

#define GARBAGE 0xCDED

#ifdef PLATFORM_D3D
#define INITIAL_VAL nullptr
#define DELETE_HANDLE(X) (X = nullptr)
#elif PLATFORM_OPEN_GL
#define INITIAL_VAL 255
#define DELETE_HANDLE(X) (X = 0)
#endif


Engine::Graphics::MaterialUniform::MaterialUniform()
{
	Handle = INITIAL_VAL;
	values[0] = GARBAGE;
	values[1] = GARBAGE;
	values[2] = GARBAGE;
	values[3] = GARBAGE;
	type = Unknown;
	valCount = 0;
	valType = Float;
}

Engine::Graphics::MaterialUniform::~MaterialUniform()
{
	values[0] = GARBAGE;
	values[1] = GARBAGE;
	values[2] = GARBAGE;
	values[3] = GARBAGE;
}

Engine::Graphics::UniformValues::UniformValues()
{
	boolValue = false;
	boolArray = nullptr;
	intValue = 0xefef;
	intArray = nullptr;
	floatValue = 0.0f;
	floatArray = nullptr;
	matrixValue.matrix = Engine::Math::Matrix4x4();
	matrixValue.Type = Unspecified;
	matrixArray = nullptr;
	vectorValue = VectorStruct();
	vectorArray = nullptr;
}


/*UniformValues(UniformValues &iUniformValues)
{
boolValue = iUniformValues.boolValue;
boolArray = iUniformValues.boolArray;
intValue = iUniformValues.intValue;
intArray = iUniformValues.intArray;
floatValue = iUniformValues.floatValue;
floatArray = iUniformValues.floatArray;
matrixValue.matrix = iUniformValues.matrixValue.matrix;
matrixValue.Type = iUniformValues.matrixValue.Type;
matrixArray = iUniformValues.matrixArray;
vectorValue = iUniformValues.vectorValue;
vectorArray = iUniformValues.vectorArray;
}*/



Engine::Graphics::VectorStruct::VectorStruct()
{
	x = y = z = w = 0.0f;
}


Engine::Graphics::VectorStruct::VectorStruct(VectorStruct& iVectorStruct)
{
	x = iVectorStruct.x;
	y = iVectorStruct.y;
	z = iVectorStruct.z;
	w = iVectorStruct.w;
}







