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
		no of maps
		for each map - wrote one by one
		{
			pathName\0
			uniformName\0
			shaderType
			mapType
		}
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

		{//effectName
			size_t length = strlen(m->getEffectName());
			byte = new BYTES[length];
			memcpy(byte, m->getEffectName(), sizeof(char)*length);
			writeToMaterialFile.write(byte, sizeof(char)*length);
			writeToMaterialFile.write("\0", sizeof(char));
			delete byte;
		}//effectName

		//Let's write map one by one
		{
			if (m->getMapCount() > 0)
			{
				{//Writing MapCount
					int* mapCount = new int;
					*mapCount = m->getMapCount();
					//std::cerr << "Uniform Count " << m->getUniformCount();
					byte = new BYTES[sizeof(int)];
					memcpy(byte, mapCount, sizeof(int));
					writeToMaterialFile.write(byte, sizeof(int));
					delete byte;
				}

				{//Writing Maps
					Map * tempMap = m->getMap();
					for (int i = 0; i < m->getMapCount(); ++i)
					{
							{//map Path Name
								size_t length = strlen(tempMap[i].file);
								byte = new BYTES[length];
								memcpy(byte, tempMap[i].file, sizeof(char)*length);
								writeToMaterialFile.write(byte, sizeof(char)*length);
								writeToMaterialFile.write("\0", sizeof(char));
								delete byte;
							}//map Path Name

							{//UniformName
								size_t length = strlen(tempMap[i].uniform);
								byte = new BYTES[length];
								memcpy(byte, tempMap[i].uniform, sizeof(char)*length);
								writeToMaterialFile.write(byte, sizeof(char)*length);
								writeToMaterialFile.write("\0", sizeof(char));
								delete byte;
							}//UniformName
							
							{//shaderType
								ShaderType *tempShaderType = new ShaderType;
								*tempShaderType = tempMap[i].shaderType;
								std::cerr << "\nShaderType is " << *tempShaderType << std::endl;
								byte = new BYTES[sizeof(ShaderType)];
								memcpy(byte, tempShaderType, sizeof(ShaderType));
								writeToMaterialFile.write(byte, sizeof(ShaderType));
								delete tempShaderType;
								delete byte;
							}//shaderType
							
							{//MapType
								
								MapType *tempMapType = new MapType;
								*tempMapType = tempMap[i].mapType;
								std::cerr << "\nMapType is " << *tempMapType << std::endl;
								byte = new BYTES[sizeof(MapType)];
								memcpy(byte, tempMapType, sizeof(MapType));
								writeToMaterialFile.write(byte, sizeof(MapType));
								delete tempMapType;
								delete byte;
							}//MapType
					}//for
				}//Maps
			}//if
		}//Map-Data
		
		
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