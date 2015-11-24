#include "typedefs.h"
#include "../Core/Maths/cMatrix_transformation.h"

namespace Engine
{
	namespace Graphics
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
		/*union __uniform
		{
			Engine::Math::cMatrix_transformation __matrixUniformName;
			float * __floatUniform;
			__uniform()
			{
				__matrixUniformName = Engine::Math::cMatrix_transformation::getIdentityMatrix();
				__floatUniform = nullptr;
			}
		};
		typedef __uniform UniformValue;

		struct Uniform
		{
#ifdef _DEBUG
			char* name;
#endif
			ShaderType type;
			ValueType valType;
			TypeCount valCount;
			UniformValue values;
			UniformHandle handle;
			
			Uniform()
			{
				name = nullptr;
				type = Unknown;
				valCount = Zero;
				valType = UNKOWN;
				handle = INITIAL_VAL;
			}

			~Uniform()
			{
				if (name)
					delete name;
				name = nullptr;
				if (valType == FLOAT)
				{
					delete values.__floatUniform;
					values.__floatUniform = nullptr;
				}
				DELETE_HANDLE(handle);
			}

			void setValType(int i_type)
			{
				switch (i_type)
				{
				case 1:
					valType = FLOAT;
					break;
				case 2:
					valType = MATRIX;
					break;
				default:
					valType = UNKOWN;
				}
			}

			void setShaderType(int i_type)
			{
				switch (i_type)
				{
				case 1:
					type = Vertex;
					break;
				case 2:
					type = Fragment;
					break;
				default:
					type = Unknown;

				}
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
		};*/
	}
}