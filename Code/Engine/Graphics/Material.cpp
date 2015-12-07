#include "Material.h"
#include <iostream>
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
	if(i_materialName)
	{
		if (isMaterialExist(i_materialName))
			return true;
		else
		{
			Engine::SharedPointer<Engine::Graphics::Material> material(new Material(),"Engine::Graphics::Material");
			if (!material.isNull())
			{
				material->setMaterialName(i_materialName);
				if(material->loadMaterial())
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
	No of Uniforms
	Uniforms
	{
		handle,type, valType, valueCount, values
	}
	*/

	BYTES* currentPosition = buffer;
	{		
		size_t tempSize = strlen(currentPosition);
		std::string tempName = Engine::EngineCore::getEffectFolderPath();
		char* effectFolderName = const_cast<char*>(tempName.c_str());
		size_t folderLength = strlen(effectFolderName);
		effectFile = new char[tempSize + folderLength];
		memcpy(effectFile, effectFolderName, folderLength);
		memcpy(effectFile+folderLength, currentPosition, tempSize);
		effectFile[tempSize+folderLength] = '\0';
		currentPosition += tempSize + 1;
	}	

	//Loading Effect
	
	if(!Effect::addEffectToList(effectFile))
	{
		std::stringstream errorMessage;
		errorMessage << "Unable to Load the effect. Please check shader files.\n";
		WindowsUtil::Print(errorMessage.str().c_str());
		return false;
	}

	SharedPointer<Effect> tempEffect = Effect::getEffect(effectFile);
	
	
	int uniformCount = *reinterpret_cast<int*>(currentPosition);
	currentPosition += sizeof(int);
	//tempEffect->createMaterialUniforms(uniformCount);
	materialUniformCount = uniformCount;
	materialUniforms = new MaterialUniform[materialUniformCount];
	materialUniformNames = new char*[materialUniformCount];

	for (int i = 0; i < uniformCount;++i)
	{
		size_t nameSize = strlen(currentPosition);
		materialUniformNames[i] = new char[nameSize];
		memcpy(materialUniformNames[i], currentPosition, sizeof(char)* nameSize);
		materialUniformNames[i][nameSize] = '\0';
		currentPosition += strlen(materialUniformNames[i]) + 1;
	}

	/*MaterialUniform* test = reinterpret_cast<MaterialUniform*>(currentPosition);*/
	size_t uniform_length = sizeof(MaterialUniform);
	memcpy(materialUniforms, currentPosition, sizeof(MaterialUniform)*materialUniformCount);
	/*currentPosition += sizeof(MaterialUniform);
	if(materialUniformCount>1)
		memcpy(materialUniforms+1, currentPosition, sizeof(MaterialUniform));*/
	//tempEffect->setMaterialUniforms(reinterpret_cast<MaterialUniform*>(currentPosition));
	
	/*for(int i = 0; i < uniformCount; ++i)
	{
		if (!tempEffect->setMaterialUniformHandle(uniformNames[i], i))
			return false;
	}*/
	
	delete buffer;
	currentPosition = nullptr;
	buffer = nullptr;
	return true;
}

Engine::Graphics::Material::Material()
{
	effectFile = nullptr;
	materialName = nullptr;
}

void Engine::Graphics::Material::setMaterialUniformParameters()
{
	std::string effectFileName = effectFile;
	SharedPointer<Engine::Graphics::Effect> tempEffect = Engine::Graphics::Effect::getEffect(effectFileName);
	for (int i = 0; i < materialUniformCount; ++i)
	{
		tempEffect->setMaterialUniformValue(materialUniformNames[i], materialUniforms[i]);
	}
}


Engine::Graphics::Material::Material(char* i_materialName)
{
	size_t length = strlen(i_materialName);
	materialName = new char[length + 1];
	memcpy(materialName, i_materialName, sizeof(char)* length);
	materialName[length + 1] = '\0';
	effectFile = nullptr;
}

const char* Engine::Graphics::Material::getMaterialName()
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

	effectFile = nullptr;
	materialName = nullptr;
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


const char* Engine::Graphics::Material::getEffectName()
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



