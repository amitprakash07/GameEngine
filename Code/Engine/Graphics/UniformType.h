#include "typedefs.h"
#include "../Core/Maths/cMatrix_transformation.h"

namespace Engine
{
	namespace Graphics
	{
		enum ValueType:uint8_t
		{
			UNKOWN = 0,
			FLOAT = 1,
			MATRIX = 2,
		};
		enum TypeCount:uint8_t
		{
			Zero = 0,
			One = 1,
			Two = 2,
			Three = 3,
			Four = 4
		};
		enum ShaderType:uint8_t
		{
			Unknown = 0,
			Vertex = 1,
			Fragment = 2
		};

		enum MapType :uint8_t
		{
			ALBEDO = 0,
			NORMAL = 1,
			SPECULAR = 2,
			BUMP = 3,
			SHADOW = 4
		};

	}
}