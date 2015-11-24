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
			const char *getMaterialName();
			const char* getEffectName();
			/*MaterialUniform* getMaterialUniform();
			void setMaterialUniforms(MaterialUniform*);
			void createMaterialUniforms(size_t);
			bool setMaterialUniformHandle(char*, int);
			void setMaterialUniformValue();*/
			void setMaterialUniformParameters();
			/*void setuniformCount(int);
			size_t getUniformCount();
			Uniform* getAllMaterialUniform();
			void displayMaterial();*/
			~Material();
		private:
			static std::map<std::string, Engine::SharedPointer<Material>> mMaterialList;
			char * materialName;
			char *effectFile;
			size_t materialUniformCount;
			char** materialUniformNames;
			MaterialUniform * materialUniforms;
			Material();
			Material(char*);
			bool loadMaterial();
			
			/*size_t uniformCount;
			Uniform* materialUniforms;*/
		};
	}
}

#endif