#ifndef __UNIFORM_DEFS_H
#define __UNIFORM_DEFS_H

#include "typedefs.h"
#include "../Core/Maths/Matrix4x4.h"
#include <stdint.h>

namespace Engine
{
	namespace Graphics
	{
		struct VectorStruct
		{
			float x;
			float y;
			float z;
			float w;

			VectorStruct()
			{
				x = y= z = w =0.0f;
			}

			VectorStruct(VectorStruct & iVectorStruct)
			{
				x = iVectorStruct.x;
				y = iVectorStruct.y;
				z = iVectorStruct.z;
				w = iVectorStruct.w;
			}
			
		};

		enum UniformDataType :uint8_t
		{
			Bool = 0,
			BoolArray = 1,
			Int = 2,
			IntArray = 3,
			Float = 4,
			FloatArray = 5,
			Matrix = 6,
			MatrixArray = 7,
			Vector = 8,
			VectorArray = 9,
			NotKnown = 10
		};

		enum ShaderType :uint8_t
		{
			Unknown = 0,
			Vertex = 1,
			Fragment = 2,
			Tessalation = 3,
			Geometry = 4,
			Compute = 5
		};

		enum Transform_Matrix_Type :uint8_t
		{
			Unspecified = 0,
			LocalToWorld = 1,
			WorldToView = 2,
			ViewToScreen = 3
		};


		struct MatrixStruct
		{
			Math::Matrix4x4 matrix;
			Transform_Matrix_Type Type;
		};

		union UniformValues
		{
			bool boolValue;
			bool * boolArray;
			int intValue;
			int * intArray;
			float floatValue;
			float* floatArray;
			MatrixStruct matrixValue;
			MatrixStruct *matrixArray;
			VectorStruct vectorValue;
			VectorStruct * vectorArray;
			
			UniformValues()
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
		};

		struct UniformData
		{
			char * uniformName;
			UniformHandle handle;
			UniformDataType valType;
			uint8_t valCount;
			ShaderType shaderType;
			UniformValues value;
			UniformData();
			
			/*UniformData(UniformData &iUniformData)
			{
				value = iUniformData.value;
			}*/
		};

		struct MaterialUniform
		{
			UniformHandle Handle; //8 or 4
			ShaderType type; //1
			UniformDataType valType; //1
			uint8_t valCount; //1
			float values[4]; //16
		};
		enum __renderState
		{
			ALPHA_BLENDING = 1 << 0,
			DEPTH_TESTING = 1 << 1,
			DEPTH_WRITING = 1 << 2,
			FACE_CULLING = 1 << 3
		};

		enum MapType :uint8_t
		{
			ALBEDO = 0,
			NORMAL = 1,
			SPECULAR = 2,
			BUMP = 3,
			SHADOW = 4
		};

		struct Map
		{
			char *file; //Texture File Name
			char *uniform; //Uniform Name			
			ShaderType shaderType;
			MapType mapType;
		};



		


	}
}

#endif
