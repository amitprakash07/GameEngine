#include "Material.h"
#include "../../Externals/Lua/Includes.h"
#include "../../Externals/LuaHelper/LuaHelper.h"
#include <iostream>
#include <Windows.h>


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
	//std::cerr << "Successfully Loaded";
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
	
	/*****************************Uniforms******************************/
	{
		lua_pushstring(mLuaState, "uniforms");
		lua_gettable(mLuaState, -2);
		size_t count = luaL_len(mLuaState, -1);
		std::cerr << "\nVAl Count is " << count << std::endl;
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
					std::cerr << "\nname is " << tempString << std::endl;
				}

				{
					lua_pushstring(mLuaState, "shader");
					lua_gettable(mLuaState, -2);
					const char *tempString = lua_tostring(mLuaState, -1);
					size_t length = strlen(tempString);
					if (strcmp(tempString, "fragment") == 0)
						materialUniforms[i - 1].type = ShaderType::Fragment;
					else if (strcmp(tempString, "vertex") == 0)
						materialUniforms[i - 1].type = ShaderType::Vertex;
					lua_pop(mLuaState, 1); //Popping out the shader type
					std::cerr << "\nshader Type is " << tempString << std::endl;
				}
					
				{
					lua_pushstring(mLuaState, "valtype");
					lua_gettable(mLuaState, -2);
					if (strcmp(lua_tostring(mLuaState, -1), "Matrix") == 0)
						materialUniforms[i - 1].valType = MATRIX;
					else
						materialUniforms[i - 1].valType = FLOAT;						
					lua_pop(mLuaState, 1);
				}

					
				{
					lua_pushstring(mLuaState, "value");
					lua_gettable(mLuaState, -2);
					/*std::cerr << "value type" << luaL_typename(mLuaState, -1) << std::endl;*/
					if (lua_istable(mLuaState,-1))
					{
						//std::cerr << "value type" << luaL_typename(mLuaState, -1)<<std::endl;
						size_t valCount = luaL_len(mLuaState, -1);
						//std::cerr << "\nVAl Count is " << valCount << std::endl;
						materialUniforms[i - 1].setValCount(static_cast<int>(valCount));
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
						materialUniforms[i - 1].setValCount(0);

					lua_pop(mLuaState, 1);//Popping out the values						
				}
				lua_pop(mLuaState, 1); //Popping out the uniform index
			}
		}
		else
		{
			errormessage << "No Uniform in the Lua file \n.";
			LuaHelper::OutputErrorMessage(errormessage.str().c_str(), __FILE__);
			LuaHelper::exitAndShutdownLua(mLuaState);
			return false;
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
	uniformCount = Zero;
}

Tools::AssetBuilder::Material::Material(char* i_materialName)
{
	effectFile = nullptr;
	materialUniforms = nullptr;
	uniformCount = Zero;
	size_t length = strlen(i_materialName);
	materialName = new char[length + 1];
	memcpy(materialName, i_materialName, sizeof(char)* length);
	materialName[length + 1] = '\0';
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
	if (effectFile)
		delete effectFile;
	if (materialUniforms)
		delete materialUniforms;
	if (materialName)
		delete materialName;
	
	effectFile = nullptr;
	materialUniforms = nullptr;
	materialName = nullptr;
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
	for (size_t i = 0; i < uniformCount; ++i)
	{
		std::cerr << "Information about " << i << "th uniform is as below\n";
		std::cerr << "Uniform name is" << materialUniformNames[i] << std::endl;
		std::cerr << "Shader Type :" << materialUniforms[i].type << std::endl;
		std::cerr << "Value Type : " << materialUniforms[i].valType << std::endl;
		if (materialUniforms[i].valCount > 0)
		{
			std::cerr << "Values are";
			for (size_t j = 0; j < materialUniforms[i].valCount; ++j)
			{
				std::cerr << "(" << materialUniforms[i].values[j] << ",";
			}
			std::cerr << ")\n\n\n";
		}
		
	}
}












