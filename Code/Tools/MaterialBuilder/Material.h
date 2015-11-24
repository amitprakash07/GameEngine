#ifndef __MATERIAL_H
#define __MATERIAL_H

#include <stdint.h>

#ifdef PLATFORM_OPEN_GL
typedef	int uniformHandle;
#elif PLATFORM_D3D
typedef	char* uniformHandle;
#endif
			
#ifdef PLATFORM_D3D
#define INITIAL_VAL nullptr
#define DELETE_HANDLE(X) (X = nullptr)
#elif PLATFORM_OPEN_GL
#define INITIAL_VAL 255
#define DELETE_HANDLE(X) (X = 0)
#endif

#define GARBAGE 0xCDED
namespace Tools
{
	namespace AssetBuilder
	{

		enum ValueType
		{
			UNKOWN = 0,
			FLOAT = 1,
			MATRIX = 2,
		};

		enum TypeCount
		{
			Zero = 0,
			One = 1,
			Two = 2,
			Three = 3,
			Four = 4
		};

		enum ShaderType
		{
			Unknown = 0,
			Vertex = 1,
			Fragment = 2
		};

		struct MaterialUniform
		{
			uniformHandle Handle;
			ShaderType type;
			ValueType valType;
			TypeCount valCount;
			float values[4];
			MaterialUniform()
			{
				Handle = INITIAL_VAL;
				values[0] = GARBAGE;
				values[1] = GARBAGE;
				values[2] = GARBAGE;
				values[3] = GARBAGE;
				type = Unknown;
				valCount = Zero;
				valType = FLOAT;
			}
			~MaterialUniform()
			{
				/*if (name)
					delete name;
				name = nullptr;*/
				values[0] = GARBAGE;
				values[1] = GARBAGE;
				values[2] = GARBAGE;
				values[3] = GARBAGE;
			}

			void setValCount(int i_count)
			{
				switch (i_count)
				{
				case 1:
					valCount = One;
					break;
				case 2:
					valCount = Two;
					break;
				case 3:
					valCount = Three;
					break;
				case 4:
					valCount = Four;
					break;
				default:
					valCount = Zero;
				}
			}


		};

		//union uniformType
		//{
		//	float float1;
		//	float float2[2];
		//	float float3[3];
		//	float float4[4];
		//};

		class Material
		{
		public:
			Material();
			Material(char*);
			bool loadMaterial();
			char* getEffectName();
			void setMaterialName(const char*);
			char *getMaterialName();
			void setuniformCount(int);
			int getUniformCount();
			char** getAllUniformName();
			MaterialUniform* getAllMaterialUniform();
			void displayMaterial();
			~Material();
		private:
			char * materialName;
			char *effectFile;
			int uniformCount;
			char** materialUniformNames;
			MaterialUniform* materialUniforms;
		};
	}
}
#endif