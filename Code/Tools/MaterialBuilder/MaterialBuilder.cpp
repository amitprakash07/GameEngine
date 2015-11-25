#include "MaterialBuilder.h"
#include "Material.h"
#include <fstream>
#include <sstream>
#include <iostream>

typedef char BYTES;

bool Tools::AssetBuilder::MaterialBuilder::Build(const std::vector<std::string>&)
{
	Material *m = new Material();
	//std::cerr << std::endl<< m_path_source << " And length is " << strlen(m_path_source)<<std::endl;
	m->setMaterialName(m_path_source);
	if (m->loadMaterial())
	{
		m->displayMaterial();
		std::ofstream writeToMaterialFile;
		writeToMaterialFile.open(m_path_target, std::ofstream::binary);

		/*Binary Format
		Effect File Name
		No of Uniforms
		uniform names
		Uniforms
		{
			Handle,
			shadertype,
			valType,
			valueCount,
			values
		}
		*/
		
		BYTES * byte = nullptr;
		//Let's write one by one
		
		{
			size_t length = strlen(m->getEffectName());
			byte = new BYTES[length];
			memcpy(byte, m->getEffectName(), sizeof(char)*length);
			writeToMaterialFile.write(byte, sizeof(char)*length);
			writeToMaterialFile.write("\0", sizeof(char));
			delete byte;
		}

		{
			int* uniformCount = new int;
			*uniformCount = m->getUniformCount();
			std::cerr << "Uniform Count " << m->getUniformCount();
			byte = new BYTES[sizeof(int)];
			memcpy(byte, uniformCount, sizeof(int));
			writeToMaterialFile.write(byte, sizeof(int));
			delete byte;
		}

		{
			//std::stringstream uniformNames;
			MaterialUniform* mTemp = m->getAllMaterialUniform();
			char** uniformNames = m->getAllUniformName();
			for (size_t i = 0; i < m->getUniformCount(); ++i)
			{
				size_t length = strlen(uniformNames[i]);
				byte = new BYTES[length];
				memcpy(byte, uniformNames[i], sizeof(char)* length);
				writeToMaterialFile.write(byte, sizeof(char)*length);
				writeToMaterialFile.write("\0", sizeof(char));
				delete byte;
				byte = nullptr;
			}

			byte = new BYTES[sizeof(MaterialUniform)*m->getUniformCount()];
			memcpy(byte, m->getAllMaterialUniform(), sizeof(MaterialUniform)*m->getUniformCount());
			writeToMaterialFile.write(byte, sizeof(MaterialUniform)*m->getUniformCount());

			
		}
				
		writeToMaterialFile.close();
		return true;
	}
	return false;
}