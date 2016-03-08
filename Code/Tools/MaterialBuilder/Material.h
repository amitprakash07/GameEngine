#ifndef __MATERIAL_H
#define __MATERIAL_H

#include <stdint.h>
#include "../../Engine/Graphics/uniformdefs.h"

namespace Tools
{
	namespace AssetBuilder
	{
		enum MapType:uint8_t
		{
			ALBEDO =0,
			NORMAL = 1,
			SPECULAR = 2,
			BUMP = 3,
			SHADOW = 4
		};


		struct MaterialUniform
		{
			Engine::Graphics::UniformHandle Handle; //8 or 4
			Engine::Graphics::ShaderType type; //1
			Engine::Graphics::UniformDataType valType; //1
			uint8_t valCount; //1
			float values[4]; //16

			MaterialUniform();			
		};

		struct Map
		{
			char *file;
			char *uniform;
			Engine::Graphics::ShaderType shaderType;
			MapType mapType;
		};	

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
			int getMapCount();
			Map* getMap();
			char** getAllUniformName();
			MaterialUniform* getAllMaterialUniform();
			void displayMaterial();
			~Material();
		private:
			char * materialName;
			char *effectFile;
			Map *maps;
			int mapCount;
			int uniformCount;
			char** materialUniformNames;
			MaterialUniform* materialUniforms;
		};
	}
}
#endif