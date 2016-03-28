#ifndef __ENGINE_MATERIAL_H
#define __ENGINE_MATERIAL_H

#include "Effect.h"

namespace Engine
{
	namespace Graphics
	{
		class Material
		{
		public:
			static bool addMaterialToList(const char*);
			static SharedPointer<Material> getMaterial(const char*);
			static bool isMaterialExist(const char*);
			static void deleteAll();			
			void setMaterialName(const char*);
			const char *getMaterialName() const;
			const char* getEffectName() const;
			void setMaterialUniformParameters() const;
			void changeMaterialColor(float i_R, float i_G, float i_b, float i_A = 1.0f) const;
			void setTextureUniform() const;
			std::string getMap(MapType iMapType, ShaderType iShaderType)const ;
			~Material();
		private:
			static std::map<std::string, Engine::SharedPointer<Material>> mMaterialList;
			char * materialName;
			char *effectFile;
			size_t materialUniformCount;
			char** materialUniformNames;
			MaterialUniform * materialUniforms;
			int mapCount;
			Map* mTextureMaps;
			Material();
			Material(char*);
			bool loadMaterial();
		};
	}
}

#endif