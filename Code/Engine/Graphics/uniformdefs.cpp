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


Engine::Graphics::Data::Data()
{
	/*floatVal = 1.0f;
	vec2[0] = 1.0f;
	vec2[1] = 1.0f;
	for (int i = 0; i < 3; i++)
		vec3[i] = 1.0f;
	for (int i = 0; i < 4; i++)
		vec4[i] = 1.0f;


	iVal = 1;
	iVec2[0] = 1;
	iVec2[1] = 1;
	for (int i = 0; i < 3; i++)
		iVec3[i] = 1;
	for (int i = 0; i < 4; i++)
		iVec4[i] = 1;


	dVal = 1.0l;
	dVal2[0] = 1.0l;
	dVal2[1] = 1.0l;
	for (int i = 0; i < 3; i++)
		dVal3[i] = 1.0l;
	for (int i = 0; i < 4; i++)
		dVal4[i] = 1.0l;


	uiVal = 1;
	uiVal2[0] = 1;
	uiVal2[1] = 1;
	for (int i = 0; i < 3; i++)
		uiVal3[i] = 1;
	for (int i = 0; i < 4; i++)
		uiVal4[i] = 1;


	boolVal = 1;
	boolVal2[0] = 1;
	boolVal2[1] = 1;
	for (int i = 0; i < 3; i++)
		boolVal3[i] = 1;
	for (int i = 0; i < 4; i++)
		boolVal4[i] = 1;*/
}
//
//Engine::Graphics::Data::Data(const Data& iData)
//{
//	memcpy(&dmat4, &iData, sizeof(Data));
//	/*floatVal = iData.floatVal;
//	memcpy(&vec2, &iData.vec2, getDataTypeSize(DataTypes::vec2));
//	memcpy(&vec3, &iData.vec3, getDataTypeSize(DataTypes::vec3));
//	memcpy(&vec4, &iData.vec4, getDataTypeSize(DataTypes::vec4));
//
//	iVal = iData.iVal;
//	memcpy(&iVec2, &iData.iVec2, getDataTypeSize(DataTypes::ivec2));
//	memcpy(&iVec3, &iData.iVec3, getDataTypeSize(DataTypes::ivec3));
//	memcpy(&iVec4, &iData.iVec4, getDataTypeSize(DataTypes::ivec4));
//
//	dVal = iData.dVal;
//	memcpy(&dVal2, &iData.dVal2, getDataTypeSize(DataTypes::dvec2));
//	memcpy(&dVal3, &iData.dVal3, getDataTypeSize(DataTypes::dvec3));
//	memcpy(&dVal4, &iData.dVal4, getDataTypeSize(DataTypes::dvec4));
//
//	uiVal = iData.uiVal;
//	memcpy(&uiVal2, &iData.uiVal2, getDataTypeSize(DataTypes::uvec2));
//	memcpy(&uiVal3, &iData.uiVal3, getDataTypeSize(DataTypes::uvec3));
//	memcpy(&uiVal4, &iData.uiVal4, getDataTypeSize(DataTypes::uvec4));
//
//	boolVal = iData.boolVal;
//	memcpy(&boolVal2, &iData.boolVal2, getDataTypeSize(DataTypes::bvec2));
//	memcpy(&boolVal3, &iData.boolVal3, getDataTypeSize(DataTypes::bvec3));
//	memcpy(&boolVal4, &iData.boolVal4, getDataTypeSize(DataTypes::bvec4));
//
//	memcpy(&mat2, &iData.mat2, getDataTypeSize(DataTypes::mat2));
//	memcpy(&mat3, &iData.mat3, getDataTypeSize(DataTypes::mat3));
//	memcpy(&mat4, &iData.mat4, getDataTypeSize(DataTypes::mat4));
//
//	memcpy(&mat2x3, &iData.mat2x3, getDataTypeSize(DataTypes::mat2x3));
//	memcpy(&mat2x4, &iData.mat2x4, getDataTypeSize(DataTypes::mat2x4));
//	memcpy(&mat3x2, &iData.mat3x2, getDataTypeSize(DataTypes::mat3x2));
//
//	memcpy(&mat3x4, &iData.mat3x4, getDataTypeSize(DataTypes::mat3x4));
//	memcpy(&mat4x2, &iData.mat4x2, getDataTypeSize(DataTypes::mat4x2));
//	memcpy(&mat4x3, &iData.mat4x3, getDataTypeSize(DataTypes::mat4x3));
//
//	memcpy(&dmat2, &iData.dmat2, getDataTypeSize(DataTypes::dmat2));
//	memcpy(&dmat3, &iData.dmat3, getDataTypeSize(DataTypes::dmat3));
//	memcpy(&dmat4, &iData.dmat4, getDataTypeSize(DataTypes::dmat4));
//
//	memcpy(&dmat2x3, &iData.dmat2x3, getDataTypeSize(DataTypes::dmat2x3));
//	memcpy(&dmat2x4, &iData.dmat2x4, getDataTypeSize(DataTypes::dmat2x4));
//	memcpy(&dmat3x2, &iData.dmat3x2, getDataTypeSize(DataTypes::dmat3x2));
//	memcpy(&dmat3x4, &iData.dmat3x4, getDataTypeSize(DataTypes::dmat3x4));
//	memcpy(&dmat4x2, &iData.dmat4x2, getDataTypeSize(DataTypes::dmat4x2));
//	memcpy(&dmat4x3, &iData.dmat4x3, getDataTypeSize(DataTypes::dmat4x3));*/
//}

//Engine::Graphics::Data& Engine::Graphics::Data::operator=(Data iData)
//{
//	Data returnData;
//
//	memcpy(&returnData, &iData, sizeof(Data));
//
//	/*returnData.floatVal = iData.floatVal;
//	memcpy(&returnData.vec2, &iData.vec2, getDataTypeSize(DataTypes::vec2));
//	memcpy(&returnData.vec3, &iData.vec3, getDataTypeSize(DataTypes::vec3));
//	memcpy(&returnData.vec4, &iData.vec4, getDataTypeSize(DataTypes::vec4));
//
//	returnData.iVal = iData.iVal;
//	memcpy(&returnData.iVec2, &iData.iVec2, getDataTypeSize(DataTypes::ivec2));
//	memcpy(&returnData.iVec3, &iData.iVec3, getDataTypeSize(DataTypes::ivec3));
//	memcpy(&returnData.iVec4, &iData.iVec4, getDataTypeSize(DataTypes::ivec4));
//
//	returnData.dVal = iData.dVal;
//	memcpy(&returnData.dVal2, &iData.dVal2, getDataTypeSize(DataTypes::dvec2));
//	memcpy(&returnData.dVal3, &iData.dVal3, getDataTypeSize(DataTypes::dvec3));
//	memcpy(&returnData.dVal4, &iData.dVal4, getDataTypeSize(DataTypes::dvec4));
//
//	returnData.uiVal = iData.uiVal;
//	memcpy(&returnData.uiVal2, &iData.uiVal2, getDataTypeSize(DataTypes::uvec2));
//	memcpy(&returnData.uiVal3, &iData.uiVal3, getDataTypeSize(DataTypes::uvec3));
//	memcpy(&returnData.uiVal4, &iData.uiVal4, getDataTypeSize(DataTypes::uvec4));
//
//	returnData.boolVal = iData.boolVal;
//	memcpy(&returnData.boolVal2, &iData.boolVal2, getDataTypeSize(DataTypes::bvec2));
//	memcpy(&returnData.boolVal3, &iData.boolVal3, getDataTypeSize(DataTypes::bvec3));
//	memcpy(&returnData.boolVal4, &iData.boolVal4, getDataTypeSize(DataTypes::bvec4));
//
//	memcpy(&returnData.mat2, &iData.mat2, getDataTypeSize(DataTypes::mat2));
//	memcpy(&returnData.mat3, &iData.mat3, getDataTypeSize(DataTypes::mat3));
//	memcpy(&returnData.mat4, &iData.mat4, getDataTypeSize(DataTypes::mat4));
//
//	memcpy(&returnData.dmat2, &iData.dmat2, getDataTypeSize(DataTypes::dmat2));
//	memcpy(&returnData.dmat3, &iData.dmat3, getDataTypeSize(DataTypes::dmat3));
//	memcpy(&returnData.dmat4, &iData.dmat4, getDataTypeSize(DataTypes::dmat4));
//
//
//	memcpy(&returnData.dmat2x3, &iData.dmat2x3, getDataTypeSize(DataTypes::dmat2x3));
//	memcpy(&returnData.dmat2x4, &iData.dmat2x4, getDataTypeSize(DataTypes::dmat2x4));
//	memcpy(&returnData.dmat3x2, &iData.dmat3x2, getDataTypeSize(DataTypes::dmat3x2));
//	memcpy(&returnData.dmat3x4, &iData.dmat3x4, getDataTypeSize(DataTypes::dmat3x4));
//	memcpy(&returnData.dmat4x2, &iData.dmat4x2, getDataTypeSize(DataTypes::dmat4x2));
//	memcpy(&returnData.dmat4x3, &iData.dmat4x3, getDataTypeSize(DataTypes::dmat4x3));*/
//
//	return returnData;
//}

size_t Engine::Graphics::getDataTypeSize(DataTypes iType)
{
	size_t typeSize = 0;
	switch (iType)
	{
	case DataTypes::glfloat:
		typeSize = sizeof(float);
		break;
	case DataTypes::vec2:
		typeSize = 2 * sizeof(float);
		break;
	case DataTypes::vec3:
		typeSize = 3 * sizeof(float);
		break;
	case DataTypes::vec4:
		typeSize = 4 * sizeof(float);
		break;
	case DataTypes::glDouble:
		typeSize = sizeof(double);
		break;
	case DataTypes::dvec2:
		typeSize = 2 * sizeof(double);
		break;
	case DataTypes::dvec3:
		typeSize = 3 * sizeof(double);
		break;
	case DataTypes::dvec4:
		typeSize = 4 * sizeof(double);
		break;
	case DataTypes::glInt:
		typeSize = sizeof(int);
		break;
	case DataTypes::ivec2:
		typeSize = 2 * sizeof(int);
		break;
	case DataTypes::ivec3:
		typeSize = 3 * sizeof(int);
		break;
	case DataTypes::ivec4:
		typeSize = 4 * sizeof(int);
		break;
	case DataTypes::unsignedint:
		typeSize = sizeof(unsigned int);
		break;
	case DataTypes::uvec2:
		typeSize = 2 * sizeof(unsigned int);
		break;
	case DataTypes::uvec3:
		typeSize = 3 * sizeof(unsigned int);
		break;
	case DataTypes::uvec4:
		typeSize = 4 * sizeof(unsigned int);
		break;
	case DataTypes::glBool:
		typeSize = sizeof(bool);
		break;
	case DataTypes::bvec2:
		typeSize = 2 * sizeof(bool);
		break;
	case DataTypes::bvec3:
		typeSize = 3 * sizeof(bool);
		break;
	case DataTypes::bvec4:
		typeSize = 4 * sizeof(bool);
		break;
	case DataTypes::mat2:
		typeSize = 4 * sizeof(float);
		break;
	case DataTypes::mat3:
		typeSize = 9 * sizeof(float);
		break;
	case DataTypes::mat4:
		typeSize = 16 * sizeof(float);
		break;
	case DataTypes::mat2x3:
		typeSize = 6 * sizeof(float);
		break;
	case DataTypes::mat2x4:
		typeSize = 8 * sizeof(float);
		break;
	case DataTypes::mat3x2:
		typeSize = 6 * sizeof(float);
		break;
	case DataTypes::mat3x4:
		typeSize = 12 * sizeof(float);
		break;
	case DataTypes::mat4x2:
		typeSize = 8 * sizeof(float);
		break;
	case DataTypes::mat4x3:
		typeSize = 12 * sizeof(float);
		break;
	case DataTypes::dmat2:
		typeSize = 4 * sizeof(double);
		break;
	case DataTypes::dmat3:
		typeSize = 9 * sizeof(double);
		break;
	case DataTypes::dmat4:
		typeSize = 16 * sizeof(double);
		break;
	case DataTypes::dmat2x3:
		typeSize = 6 * sizeof(double);
		break;
	case DataTypes::dmat2x4:
		typeSize = 8 * sizeof(double);
		break;
	case DataTypes::dmat3x2:
		typeSize = 6 * sizeof(double);
		break;
	case DataTypes::dmat3x4:
		typeSize = 12 * sizeof(double);
		break;
	case DataTypes::dmat4x2:
		typeSize = 8 * sizeof(double);
		break;
	case DataTypes::dmat4x3:
		typeSize = 12 * sizeof(double);
		break;	
	default:
		break;

	}
	return typeSize;
}

Engine::Graphics::DataTypes Engine::Graphics::getDataType(int iType)
{
	DataTypes type = DataTypes::glUnknown;
	switch (iType)
	{
	case GL_FLOAT:
		type = DataTypes::glfloat;
		break;
	case GL_FLOAT_VEC2:
		type = DataTypes::vec2;
		break;
	case GL_FLOAT_VEC3:
		type = DataTypes::vec3;
		break;
	case GL_FLOAT_VEC4:
		type = DataTypes::vec4;
		break;
	case GL_DOUBLE:
		type = DataTypes::glDouble;
		break;
	case GL_DOUBLE_VEC2:
		type = DataTypes::dvec2;
		break;
	case GL_DOUBLE_VEC3:
		type = DataTypes::dvec3;
		break;
	case GL_DOUBLE_VEC4:
		type = DataTypes::dvec4;
		break;
	case GL_INT:
		type = DataTypes::glInt;
		break;
	case GL_INT_VEC2:
		type = DataTypes::ivec2;
		break;
	case GL_INT_VEC3:
		type = DataTypes::ivec3;
		break;
	case GL_INT_VEC4:
		type = DataTypes::ivec4;
		break;
	case GL_UNSIGNED_INT:
		type = DataTypes::unsignedint;
		break;
	case GL_UNSIGNED_INT_VEC2:
		type = DataTypes::uvec2;
		break;
	case GL_UNSIGNED_INT_VEC3:
		type = DataTypes::uvec3;
		break;
	case GL_UNSIGNED_INT_VEC4:
		type = DataTypes::uvec4;
		break;
	case GL_BOOL:
		type = DataTypes::glBool;
		break;
	case GL_BOOL_VEC2:
		type = DataTypes::bvec2;
		break;
	case GL_BOOL_VEC3:
		type = DataTypes::bvec3;
		break;
	case GL_BOOL_VEC4:
		type = DataTypes::bvec4;
		break;
	case GL_FLOAT_MAT2:
		type = DataTypes::mat2;
		break;
	case GL_FLOAT_MAT3:
		type = DataTypes::mat3;
		break;
	case GL_FLOAT_MAT4:
		type = DataTypes::mat4;
		break;
	case GL_FLOAT_MAT2x3:
		type = DataTypes::mat2x3;
		break;
	case GL_FLOAT_MAT2x4:
		type = DataTypes::mat2x4;
		break;
	case GL_FLOAT_MAT3x2:
		type = DataTypes::mat3x2;
		break;
	case GL_FLOAT_MAT3x4:
		type = DataTypes::mat3x4;
		break;
	case GL_FLOAT_MAT4x2:
		type = DataTypes::mat4x2;
		break;
	case GL_FLOAT_MAT4x3:
		type = DataTypes::mat4x3;
		break;
	case GL_DOUBLE_MAT2:
		type = DataTypes::dmat2;
		break;
	case GL_DOUBLE_MAT3:
		type = DataTypes::dmat3;
		break;
	case GL_DOUBLE_MAT4:
		type = DataTypes::dmat4;
		break;
	case GL_DOUBLE_MAT2x3:
		type = DataTypes::dmat2x3;
		break;
	case GL_DOUBLE_MAT2x4:
		type = DataTypes::dmat2x4;
		break;
	case GL_DOUBLE_MAT3x2:
		type = DataTypes::dmat3x2;
		break;
	case GL_DOUBLE_MAT3x4:
		type = DataTypes::dmat3x4;
		break;
	case GL_DOUBLE_MAT4x2:
		type = DataTypes::dmat4x2;
		break;
	case GL_DOUBLE_MAT4x3:
		type = DataTypes::dmat4x3;
		break;	
	default:
		break;

	}
	return type;
}

void Engine::Graphics::Data::assignData(DataTypes iDataType, Data iData)
{	
	switch (iDataType)
	{
	case DataTypes::glfloat:
		floatVal = iData.floatVal;
		break;
	case DataTypes::vec2:
		memcpy(&vec2, &iData.vec2, getDataTypeSize(DataTypes::vec2));		
		break;
	case DataTypes::vec3:
		memcpy(&vec3, &iData.vec3, getDataTypeSize(DataTypes::vec3));
		break;
	case DataTypes::vec4:
		memcpy(&vec4, &iData.vec4, getDataTypeSize(DataTypes::vec4));
		break;
	case DataTypes::glDouble:
		dVal = iData.dVal;
		break;
	case DataTypes::dvec2:
		memcpy(&dVal2, &iData.dVal2, getDataTypeSize(DataTypes::dvec2));
		break;
	case DataTypes::dvec3:
		memcpy(&dVal3, &iData.dVal3, getDataTypeSize(DataTypes::dvec3));
		break;
	case DataTypes::dvec4:
		memcpy(&dVal4, &iData.dVal4, getDataTypeSize(DataTypes::dvec4));
		break;
	case DataTypes::glInt:
		iVal = iData.iVal;
		break;
	case DataTypes::ivec2:
		memcpy(&iVec2, &iData.iVec2, getDataTypeSize(DataTypes::ivec2));
		break;
	case DataTypes::ivec3:
		memcpy(&iVec3, &iData.iVec3, getDataTypeSize(DataTypes::ivec3));
		break;
	case DataTypes::ivec4:
		memcpy(&iVec4, &iData.iVec4, getDataTypeSize(DataTypes::ivec4));
		break;
	case DataTypes::unsignedint:
		uiVal = iData.uiVal;		
		break;
	case DataTypes::uvec2:
		memcpy(&uiVal2, &iData.uiVal2, getDataTypeSize(DataTypes::uvec2));
		break;
	case DataTypes::uvec3:
		memcpy(&uiVal3, &iData.uiVal3, getDataTypeSize(DataTypes::uvec3));
		break;
	case DataTypes::uvec4:
		memcpy(&uiVal4, &iData.uiVal4, getDataTypeSize(DataTypes::uvec4));
		break;
	case DataTypes::glBool:
		boolVal = iData.boolVal;
		break;
	case DataTypes::bvec2:
		memcpy(&boolVal2, &iData.boolVal2, getDataTypeSize(DataTypes::bvec2));
		break;
	case DataTypes::bvec3:
		memcpy(&boolVal3, &iData.boolVal3, getDataTypeSize(DataTypes::bvec3));
		break;
	case DataTypes::bvec4:
		memcpy(&boolVal4, &iData.boolVal4, getDataTypeSize(DataTypes::bvec4));
		break;
	case DataTypes::mat2:
		memcpy(&mat2, &iData.mat2, getDataTypeSize(DataTypes::mat2));
		break;
	case DataTypes::mat3:
		memcpy(&mat3, &iData.mat3, getDataTypeSize(DataTypes::mat3));
		break;
	case DataTypes::mat4:
		memcpy(&mat4, &iData.mat4, getDataTypeSize(DataTypes::mat4));
		break;
	case DataTypes::mat2x3:
		memcpy(&mat2x3, &iData.mat2x3, getDataTypeSize(DataTypes::mat2x3));				
		break;
	case DataTypes::mat2x4:
		memcpy(&mat2x4, &iData.mat2x4, getDataTypeSize(DataTypes::mat2x4));		
		break;
	case DataTypes::mat3x2:
		memcpy(&mat3x2, &iData.mat3x2, getDataTypeSize(DataTypes::mat3x2));		
		break;
	case DataTypes::mat3x4:
		memcpy(&mat3x4, &iData.mat3x4, getDataTypeSize(DataTypes::mat3x4));		
		break;
	case DataTypes::mat4x2:
		memcpy(&mat4x2, &iData.mat4x2, getDataTypeSize(DataTypes::mat4x2));		
		break;
	case DataTypes::mat4x3:
		memcpy(&mat4x3, &iData.mat4x3, getDataTypeSize(DataTypes::mat4x3));		
		break;
	case DataTypes::dmat2:
		memcpy(&dmat2, &iData.dmat2, getDataTypeSize(DataTypes::dmat2));
		break;
	case DataTypes::dmat3:
		memcpy(&dmat3, &iData.dmat3, getDataTypeSize(DataTypes::dmat3));
		break;
	case DataTypes::dmat4:
		memcpy(&dmat4, &iData.dmat4, getDataTypeSize(DataTypes::dmat4));
		break;
	case DataTypes::dmat2x3:
		memcpy(&dmat2x3, &iData.dmat2x3, getDataTypeSize(DataTypes::dmat2x3));
		break;
	case DataTypes::dmat2x4:
		memcpy(&dmat2x4, &iData.dmat2x4, getDataTypeSize(DataTypes::dmat2x4));
		break;
	case DataTypes::dmat3x2:
		memcpy(&dmat3x2, &iData.dmat3x2, getDataTypeSize(DataTypes::dmat3x2));
		break;
	case DataTypes::dmat3x4:
		memcpy(&dmat3x4, &iData.dmat3x4, getDataTypeSize(DataTypes::dmat3x4));
		break;
	case DataTypes::dmat4x2:
		memcpy(&dmat4x2, &iData.dmat4x2, getDataTypeSize(DataTypes::dmat4x2));
		break;
	case DataTypes::dmat4x3:
		memcpy(&dmat4x3, &iData.dmat4x3, getDataTypeSize(DataTypes::dmat4x3));
		break;
	default:
		break;
	}
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







