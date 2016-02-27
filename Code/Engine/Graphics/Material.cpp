#include "Material.h"
#include "Texture.h"
#include <fstream>
#include <sstream>
#include "../Windows/WindowsFunctions.h"
#include "../../Engine/Core/EngineCore/EngineCore.h"

typedef char BYTES;

std::map<std::string, Engine::SharedPointer<Engine::Graphics::Material>> Engine::Graphics::Material::mMaterialList;

bool Engine::Graphics::Material::addMaterialToList(const char* i_materialName)
{
	bool success = false;
	std::stringstream errormessage;
	if (i_materialName)
	{
		if (isMaterialExist(i_materialName))
			return true;
		else
		{
			Engine::SharedPointer<Engine::Graphics::Material> material(new Material(), 
				"Engine::Graphics::Material");
			if (!material.isNull())
			{
				material->setMaterialName(i_materialName);
				if (material->loadMaterial())
				{
					mMaterialList[i_materialName] = material;
					success = true;
				}
				else success = false;
			}
			else success = false;
		}
	}
	else
	{
		errormessage << "\nEmpty Material Name";
		WindowsUtil::Print(errormessage.str());
		success = false;
	}
	return success;
}



bool Engine::Graphics::Material::loadMaterial()
{
	std::stringstream errormessage;
	std::ifstream readFile;

	if (!readFile.is_open())
		readFile.open(materialName, std::ifstream::binary);

	readFile.seekg(0, readFile.end);
	size_t length = static_cast<size_t>(readFile.tellg());
	readFile.seekg(0, readFile.beg);

	BYTES * buffer = new BYTES[length];
	//Lets read evrything from asset binary file
	readFile.read(buffer, length);
	readFile.close();//Closing the file Pointer

					 /*Binary Format
					 Effect File Name
					 no of maps
					 for each map - read one by one
					 {
					 pathName\0
					 uniformName\0
					 shaderType
					 mapType
					 }
					 No of Uniforms
					 uniform names
					 foreach uniform
					 Uniforms
					 {
					 Handle,
					 shadertype,
					 valType,
					 valueCount,
					 values
					 }*/

	BYTES* currentPosition = buffer;
	{
		size_t tempSize = strlen(currentPosition);
		std::string tempName = Engine::EngineCore::getEffectFolderPath();
		size_t folderLength = tempName.size();
		char* effectFolderName = new char[folderLength];
		memcpy(effectFolderName, tempName.c_str(), folderLength);
		effectFile = new char[tempSize + folderLength];
		memcpy(effectFile, effectFolderName, folderLength);
		memcpy(effectFile + folderLength, currentPosition, tempSize);
		effectFile[tempSize + folderLength] = '\0';
		currentPosition += tempSize + 1;
		delete effectFolderName;
	}

	//Loading Effect

	if (!Effect::addEffectToList(effectFile))
	{
		std::stringstream errorMessage;
		errorMessage << "Unable to Load the effect. Please check shader files.\n";
		WindowsUtil::Print(errorMessage.str().c_str());
		return false;
	}

	SharedPointer<Effect> tempEffect = Effect::getEffect(effectFile);

	
	int tempMapCount = 0;
	if ((reinterpret_cast<BYTES*>(currentPosition) - buffer)  < length)
	{
		//Loading Maps
		tempMapCount = *reinterpret_cast<int*>(currentPosition);
		currentPosition += sizeof(int);
	}
	mapCount = tempMapCount;
	if (mapCount > 0)
	{
		mTextureMaps = new Map[mapCount];

		for (size_t i = 0; i < mapCount; ++i)
		{
			//Texture Path and Load Texture
			{
				size_t  texturePathLength = strlen(currentPosition);
				std::string textureFolder = EngineCore::getTextureFolderPath();
				size_t textureFolderLength = textureFolder.size();
				char* textureFolderName = new char[textureFolderLength];
				memcpy(textureFolderName, textureFolder.c_str(), textureFolderLength);
				mTextureMaps[i].file = new char[texturePathLength + textureFolderLength];
				memcpy(mTextureMaps[i].file, textureFolderName, textureFolderLength);
				memcpy(mTextureMaps[i].file + textureFolderLength, currentPosition, texturePathLength);
				mTextureMaps[i].file[textureFolderLength + texturePathLength] = '\0';
				currentPosition += texturePathLength + 1;				
				delete textureFolderName;
			}

			//Texture Uniform Name
			{
				size_t uniformNameLength = strlen(currentPosition);
				mTextureMaps[i].uniform = new char[uniformNameLength];
				memcpy(mTextureMaps[i].uniform, currentPosition, uniformNameLength);
				mTextureMaps[i].uniform[uniformNameLength] = '\0';
				currentPosition += uniformNameLength + 1;
			}

			//ShaderType
			{
				mTextureMaps[i].shaderType = *reinterpret_cast<ShaderType*>(currentPosition);
				currentPosition += sizeof(ShaderType);
			}

			//MapType
			{
				mTextureMaps[i].mapType = *reinterpret_cast<MapType*>(currentPosition);
				currentPosition += sizeof(MapType);
			}

			WindowsUtil::Assert(Texture::addTextureToList(effectFile, //Effect File Name
				mTextureMaps[i].file, //Texture Name
				mTextureMaps[i].uniform, //Sampler Name
				mTextureMaps[i].shaderType //Shader Type
				), "Unable to load the texture");
		}
	}


	int uniformCount = 0;
	if ((reinterpret_cast<BYTES*>(currentPosition) - buffer) < length)
	{
		//Loading Maps
		uniformCount = *reinterpret_cast<int*>(currentPosition);
		currentPosition += sizeof(int);
		materialUniformCount = uniformCount;
		materialUniforms = new MaterialUniform[materialUniformCount];
		materialUniformNames = new char*[materialUniformCount];
	}	

	if (uniformCount > 0)
	{

		for (int i = 0; i < uniformCount; ++i)
		{
			size_t nameSize = strlen(currentPosition);
			materialUniformNames[i] = new char[nameSize];
			memcpy(materialUniformNames[i], currentPosition, sizeof(char)* nameSize);
			materialUniformNames[i][nameSize] = '\0';
			currentPosition += strlen(materialUniformNames[i]) + 1;
		}

		size_t uniform_length = sizeof(MaterialUniform);
		memcpy(materialUniforms, currentPosition, sizeof(MaterialUniform)*materialUniformCount);

		for (int i = 0; i < uniformCount; ++i)
		{
			materialUniforms[i].Handle = tempEffect->getUniformHandle(materialUniformNames[i], materialUniforms[i].type);
		}
	}

	delete buffer;
	currentPosition = nullptr;
	buffer = nullptr;
	return true;
}

Engine::Graphics::Material::Material()
{
	effectFile = nullptr;
	materialName = nullptr;
	materialUniformCount = 0;
	materialUniforms = nullptr;
	materialUniformNames = nullptr;
	mapCount = 0;
	mTextureMaps = nullptr;
}

void Engine::Graphics::Material::setMaterialUniformParameters() const
{
	std::string effectFileName = effectFile;
	SharedPointer<Engine::Graphics::Effect> tempEffect = Engine::Graphics::Effect::getEffect(effectFileName);
	for (size_t i = 0; i < materialUniformCount; ++i)
	{
		tempEffect->setMaterialUniformValue(materialUniformNames[i], materialUniforms[i]);
	}
}

void Engine::Graphics::Material::changeMaterialColor(float i_R, float i_G, float i_B, float i_A) const
{
	for (size_t i = 0; i < materialUniformCount; ++i)
	{
		if (strcmp(materialUniformNames[i], "g_vertexColorModifier") == 0)
		{
			materialUniforms[i].values[0] = i_R;
			materialUniforms[i].values[1] = i_G;
			materialUniforms[i].values[2] = i_B;
			materialUniforms[i].values[3] = i_A;
		}
	}
}


void Engine::Graphics::Material::setTextureUniform() const
{
	for (int i = 0; i < mapCount; ++i)
	{
		SharedPointer<Texture> tempTexture = Engine::Graphics::Texture::getTexture(mTextureMaps[i].file);
		tempTexture->setEffectName(effectFile);
		tempTexture->setTextureInShaderObject(i);
	}
}


Engine::Graphics::Material::Material(char* i_materialName)
{
	size_t length = strlen(i_materialName);
	materialName = new char[length + 1];
	memcpy(materialName, i_materialName, sizeof(char)* length);
	materialName[length + 1] = '\0';
	effectFile = nullptr;
	materialUniformCount = 0;
	materialUniforms = nullptr;
	materialUniformNames = nullptr;
	mapCount = 0;
	mTextureMaps = nullptr;
}

const char* Engine::Graphics::Material::getMaterialName() const
{
	return materialName;
}

void Engine::Graphics::Material::setMaterialName(const char* i_materialName)
{
	size_t length = strlen(i_materialName);
	materialName = new char[length];
	memcpy(materialName, i_materialName, sizeof(char)* length);
	materialName[length] = '\0';
}


Engine::Graphics::Material::~Material()
{
	if (effectFile)
		delete effectFile;

	if (materialName)
		delete materialName;

	if (effectFile)
		effectFile = nullptr;

	if (materialName)
		materialName = nullptr;

	if (materialUniforms)
		delete materialUniforms;

	if (materialUniformNames)
	{
		for (size_t i = 0; i < materialUniformCount; i++)
		{
			delete materialUniformNames[i];
		}
		delete materialUniformNames;
	}

	if (mTextureMaps)
		delete mTextureMaps;
}


Engine::SharedPointer<Engine::Graphics::Material> Engine::Graphics::Material::getMaterial(const char* i_filename)
{
	for (std::map<std::string, SharedPointer<Material>>::iterator i = mMaterialList.begin(); i != mMaterialList.end(); ++i)
	{
		if (strcmp(i->first.c_str(), i_filename) == 0)
			return i->second;
	}
	return SharedPointer<Engine::Graphics::Material>();
}


bool Engine::Graphics::Material::isMaterialExist(const char* i_materialName)
{
	for (std::map<std::string, SharedPointer<Material>>::iterator i = mMaterialList.begin(); i != mMaterialList.end(); ++i)
	{
		if (strcmp(i->first.c_str(), i_materialName) == 0)
			return true;
	}
	return false;
}


const char* Engine::Graphics::Material::getEffectName() const
{
	if (effectFile)
		return effectFile;
	return nullptr;
}

void Engine::Graphics::Material::deleteAll()
{
	for (std::map<std::string, SharedPointer<Material>>::iterator i = mMaterialList.begin(); i != mMaterialList.end(); ++i)
	{
		i->second.deleteObject();
	}
}






