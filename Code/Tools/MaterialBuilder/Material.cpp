#include "Material.h"
#include "../../Externals/Lua/Includes.h"
#include "../../Externals/LuaHelper/LuaHelper.h"
#include <iostream>
#include <Windows.h>
#include "../../Engine/Graphics/Includes.h"


#define GARBAGE 0xCDED

#ifdef PLATFORM_D3D
#define INITIAL_VAL nullptr
#define DELETE_HANDLE(X) (X = nullptr)
#elif PLATFORM_OPEN_GL
#define INITIAL_VAL 255
#define DELETE_HANDLE(X) (X = 0)
#endif

Tools::AssetBuilder::MaterialUniform::MaterialUniform()
{
	Handle = INITIAL_VAL;
	values[0] = GARBAGE;
	values[1] = GARBAGE;
	values[2] = GARBAGE;
	values[3] = GARBAGE;
	type = Engine::Graphics::Unknown;
	valCount = 0;
	valType = Engine::Graphics::Float;
}



Tools::AssetBuilder::Map* Tools::AssetBuilder::Material::getMap()
{
	return maps;
}

int Tools::AssetBuilder::Material::getMapCount()
{
	return mapCount;
}

bool Tools::AssetBuilder::Material::loadMaterial()
{
	//MessageBox(nullptr, "Hello", "Debug", MB_OK);
	lua_State *mLuaState = nullptr;
	std::stringstream errormessage;
	mLuaState = luaL_newstate();
	//Creating Lua State
	if (!mLuaState)
	{
		errormessage << "Failed to create a new Lua state \n";
		LuaHelper::OutputErrorMessage(errormessage.str().c_str(), __FILE__);
		LuaHelper::exitAndShutdownLua(mLuaState);
		return false;
	}

	//Loading the lua file
	if (strlen(materialName) <= 1)
	{
		errormessage << "No File Name for the mesh. Call setMeshFileName(char*) before calling LoadMesh()";
		LuaHelper::OutputErrorMessage(errormessage.str().c_str(), __FILE__);
		LuaHelper::exitAndShutdownLua(mLuaState);
		return false;
	}


	int luaResult = luaL_loadfile(mLuaState, materialName);
	//Checking the load was successful or not
	if (luaResult != LUA_OK)
	{
		errormessage << "Unable to load the file. \n" << lua_tostring(mLuaState, 1);

		//Popping out the error message
		lua_pop(mLuaState, 1);
		LuaHelper::OutputErrorMessage(errormessage.str().c_str(), __FILE__);
		LuaHelper::exitAndShutdownLua(mLuaState);
		return false;
	}

	//Extracting the table at once in a single return
	int returnCount = LUA_MULTRET; // Return _everything_ that the file returns
	int argumentCount = 0;
	int noMessageHandler = 0;

	luaResult = lua_pcall(mLuaState, argumentCount, returnCount, noMessageHandler);
	if (!LuaHelper::isLuaResultOkay(mLuaState, luaResult) || returnCount > 1 || !LuaHelper::isTable(mLuaState))
	{
		LuaHelper::exitAndShutdownLua(mLuaState);
		return false;
	}

	//std::cerr << "Successfully Loaded";
	//std::cerr << "\nVAl Count is " /*<< valCount */<< std::endl;
	//********************Effect File Name*****************************
	{

		lua_pushstring(mLuaState, "effect");
		lua_gettable(mLuaState, -2);
		const char* tempEffect = lua_tostring(mLuaState, -1);
		size_t length = strlen(tempEffect);
		effectFile = new char[length];
		memcpy(effectFile, tempEffect, sizeof(char)*length);
		effectFile[length] = '\0';
		lua_pop(mLuaState, 1); //Popping ou the effect file name


	}
	/********************************************************************/

	/****************************Maps**********************************/
	{
		lua_pushstring(mLuaState, "map");
		lua_gettable(mLuaState, -2);
		if (LuaHelper::isTable(mLuaState))
		{
			mapCount = luaL_len(mLuaState, -1);
			if (mapCount > 0)
			{
				maps = new Map[mapCount];
				for (int i = 1; i <= mapCount; ++i)
				{
					lua_pushinteger(mLuaState, i);
					lua_gettable(mLuaState, -2);
					{
						{
							lua_pushstring(mLuaState, "path");
							lua_gettable(mLuaState, -2);
							const char* path = lua_tostring(mLuaState, -1);
							size_t pathLength = strlen(path);
							maps[i - 1].file = new char[pathLength];
							memcpy(maps[i - 1].file, path, pathLength);
							maps[i - 1].file[pathLength] = '\0';
							lua_pop(mLuaState, 1); //Popping path
						}

						{
							lua_pushstring(mLuaState, "uniformName");
							lua_gettable(mLuaState, -2);
							const char* uniformName = lua_tostring(mLuaState, -1);
							size_t uniformLength = strlen(uniformName);
							maps[i - 1].uniform = new char[uniformLength];
							memcpy(maps[i - 1].uniform, uniformName, uniformLength);
							maps[i - 1].uniform[uniformLength] = '\0';
							lua_pop(mLuaState, 1); //Popping path
						}

						{
							lua_pushstring(mLuaState, "shader");
							lua_gettable(mLuaState, -2);
							const char* shaderType = lua_tostring(mLuaState, -1);
							if (strcmp(shaderType, "Fragment") == 0)
								maps[i - 1].shaderType = Engine::Graphics::Fragment;
							else
								maps[i - 1].shaderType = Engine::Graphics::Vertex;
							lua_pop(mLuaState, 1);
						}

						{
							lua_pushstring(mLuaState, "mapType");
							lua_gettable(mLuaState, -2);
							const char* mapType = lua_tostring(mLuaState, -1);
							if (strcmp(mapType, "albedo") == 0)
								maps[i - 1].mapType = ALBEDO;
							if (strcmp(mapType, "normal") == 0)
								maps[i - 1].mapType = NORMAL;
							if (strcmp(mapType, "specular") == 0)
								maps[i - 1].mapType = SPECULAR;
							if (strcmp(mapType, "bump") == 0)
								maps[i - 1].mapType = BUMP;
							if (strcmp(mapType, "shadow") == 0)
								maps[i - 1].mapType = SHADOW;

							lua_pop(mLuaState, 1); //Popping MapType
						}
					}
					lua_pop(mLuaState, 1); //popping index
				}
			}
		}
		lua_pop(mLuaState, 1); //popping "Map"
	}
	/********************************************************************/

	/*****************************Uniforms******************************/
	{
		lua_pushstring(mLuaState, "uniforms");
		lua_gettable(mLuaState, -2);
		if (LuaHelper::isTable(mLuaState))
		{
			size_t count = luaL_len(mLuaState, -1);
			//std::cerr << "\nVAl Count is " << count << std::endl;
			if (count > 0)
			{
				setuniformCount(static_cast<int>(count));
				materialUniforms = new MaterialUniform[count];
				materialUniformNames = new char*[count];
				for (size_t i = 1; i <= count; ++i)
				{
					lua_pushinteger(mLuaState, i);
					lua_gettable(mLuaState, -2);
					{
						lua_pushstring(mLuaState, "name");
						lua_gettable(mLuaState, -2);
						const char *tempString = lua_tostring(mLuaState, -1);
						size_t length = strlen(tempString);
						materialUniformNames[i - 1] = new char[length];
						memcpy(materialUniformNames[i - 1], tempString, sizeof(char)*length);
						materialUniformNames[i - 1][length] = '\0';
						//std::cerr << "\nUniform Count is = " << count << std::endl;
						lua_pop(mLuaState, 1); //Popping out the uniform name
											   //std::cerr << "\nname is " << tempString << std::endl;
					}

					{
						lua_pushstring(mLuaState, "shader");
						lua_gettable(mLuaState, -2);
						const char *tempString = lua_tostring(mLuaState, -1);
						size_t length = strlen(tempString);
						if (strcmp(tempString, "fragment") == 0)
							materialUniforms[i - 1].type = Engine::Graphics::ShaderType::Fragment;
						else if (strcmp(tempString, "vertex") == 0)
							materialUniforms[i - 1].type = Engine::Graphics::ShaderType::Vertex;
						lua_pop(mLuaState, 1); //Popping out the shader type
											   //std::cerr << "\nshader Type is " << tempString << std::endl;
					}

					{
						lua_pushstring(mLuaState, "valtype");
						lua_gettable(mLuaState, -2);
						if (strcmp(lua_tostring(mLuaState, -1), "Matrix") == 0)
							materialUniforms[i - 1].valType = Engine::Graphics::Matrix;
						else
							materialUniforms[i - 1].valType = Engine::Graphics::Float;
						lua_pop(mLuaState, 1);
					}


					{
						lua_pushstring(mLuaState, "value");
						lua_gettable(mLuaState, -2);
						/*std::cerr << "value type" << luaL_typename(mLuaState, -1) << std::endl;*/
						if (lua_istable(mLuaState, -1))
						{
							//std::cerr << "value type" << luaL_typename(mLuaState, -1)<<std::endl;
							size_t valCount = luaL_len(mLuaState, -1);
							//std::cerr << "\nVAl Count is " << valCount << std::endl;
							materialUniforms[i - 1].valCount = static_cast<uint8_t>(valCount);
							//materialUniforms[i - 1].values = new float[valCount];
							for (size_t k = 1; k <= valCount; ++k)
							{
								lua_pushinteger(mLuaState, k);
								lua_gettable(mLuaState, -2);
								materialUniforms[i - 1].values[k - 1] = static_cast<float>(lua_tonumber(mLuaState, -1));
								lua_pop(mLuaState, 1); //Popping out the index of the uniform values
							}
						}
						else
							materialUniforms[i - 1].valCount = 0;

						lua_pop(mLuaState, 1);//Popping out the values						
					}
					lua_pop(mLuaState, 1); //Popping out the uniform index
				}
			}
		}
		lua_pop(mLuaState, 1); //Popping out the uniform Table
	}
	/*******************************************************************/

	lua_pop(mLuaState, 1); //Popping out the entire table
	LuaHelper::exitAndShutdownLua(mLuaState);//shutting down the Lua API
	return true;
}


void Tools::AssetBuilder::Material::setuniformCount(int i_count)
{
	uniformCount = i_count;
}


Tools::AssetBuilder::Material::Material()
{
	effectFile = nullptr;
	materialUniforms = nullptr;
	materialName = nullptr;
	materialUniforms = nullptr;
	materialUniformNames = nullptr;
	maps = nullptr;
	mapCount = 0;
	uniformCount = 0;
}

Tools::AssetBuilder::Material::Material(char* i_materialName)
{
	effectFile = nullptr;
	materialUniforms = nullptr;
	materialUniformNames = nullptr;
	maps = nullptr;
	mapCount = 0;
	uniformCount = 0;
	size_t length = strlen(i_materialName);
	materialName = new char[length];
	memcpy(materialName, i_materialName, sizeof(char)* length);
	materialName[length] = '\0';
}

char* Tools::AssetBuilder::Material::getMaterialName()
{
	return materialName;
}

void Tools::AssetBuilder::Material::setMaterialName(const char* i_materialName)
{
	size_t length = strlen(i_materialName);
	//std::cerr << "Length of the material file " << length << std::endl;
	materialName = new char[length];
	memcpy(materialName, i_materialName, sizeof(char)* length);
	materialName[length] = '\0';

}


Tools::AssetBuilder::Material::~Material()
{
	/*if (effectFile)
	delete effectFile;
	if (materialUniforms)
	delete materialUniforms;
	if (materialName)
	delete materialName;
	if (maps)
	delete maps;
	if(materialUniformNames)
	{
	for (int i = 0; i < uniformCount; ++i)
	delete materialUniformNames[i];
	}
	delete materialUniformNames;

	effectFile = nullptr;
	materialUniforms = nullptr;
	materialName = nullptr;
	maps = nullptr;
	materialUniformNames = nullptr;*/
}


char* Tools::AssetBuilder::Material::getEffectName()
{
	return effectFile;
}


Tools::AssetBuilder::MaterialUniform* Tools::AssetBuilder::Material::getAllMaterialUniform()
{
	return materialUniforms;
}

char** Tools::AssetBuilder::Material::getAllUniformName()
{
	return materialUniformNames;
}


int Tools::AssetBuilder::Material::getUniformCount()
{
	return uniformCount;
}

void Tools::AssetBuilder::Material::displayMaterial()
{
	std::cerr << "Material Name is " << materialName << std::endl;
	std::cerr << "Effect File Name for the Material is " << effectFile << std::endl;
	std::cerr << "Printing Map Values\n";
	for (int i = 0; i < mapCount; ++i)
	{
		std::cerr << "File Name = " << maps[i].file << std::endl;
		std::cerr << "Uniform Name = " << maps[i].uniform << std::endl;
		std::cerr << "Shader Type = " << maps[i].shaderType << std::endl;
		std::cerr << "Map Type = " << maps[i].mapType << std::endl;
	}
	for (int i = 0; i < uniformCount; ++i)
	{
		std::cerr << "Information about " << i << "th uniform is as below\n";
		std::cerr << "Uniform name is" << materialUniformNames[i] << std::endl;
		std::cerr << "Shader Type :" << materialUniforms[i].type << std::endl;
		std::cerr << "Value Type : " << materialUniforms[i].valType << std::endl;
		if (materialUniforms[i].valCount > 0)
		{
			std::cerr << "Values are";
			for (int j = 0; j < materialUniforms[i].valCount; ++j)
			{
				std::cerr << "(" << materialUniforms[i].values[j] << ",";
			}
			std::cerr << ")\n\n\n";
		}

	}
}












