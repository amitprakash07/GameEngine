#include "EffectBuilder.h"
#include "../../Externals/LuaHelper/LuaHelper.h"
#include <fstream>
#include <iostream>

bool Tools::AssetBuilder::EffectBuilder::Build(const std::vector<std::string>& i_arguments)
{
	if (LoadEffectFile())
	{
		std::ofstream writeTofile;
		writeTofile.open(m_path_target, std::ofstream::binary);
		writeTofile.write(vertexName.c_str(), sizeof(char)*vertexName.size());
		writeTofile.write("\0", sizeof(char));
		writeTofile.write(fragmentName.c_str(), sizeof(char)* fragmentName.size());
		writeTofile.write("\0", sizeof(char));
		writeTofile.close();
		return true;
	}
	return false;
}


bool Tools::AssetBuilder::EffectBuilder::LoadEffectFile()
{
	lua_State *mLuaState = nullptr;
	std::stringstream errorMessage;
	mLuaState = luaL_newstate();

	if(!mLuaState)
	{
		errorMessage << "Failed to create a new Lua state \n";
		LuaHelper::OutputErrorMessage(errorMessage.str().c_str(), __FILE__);
		LuaHelper::exitAndShutdownLua(mLuaState);
		return false;
	}

	std::cerr << "Passed creating LuaState"<<std::endl;

	if(m_path_source == nullptr)
	{
		errorMessage << "Source Path is empty";
		LuaHelper::OutputErrorMessage(errorMessage.str().c_str(), __FILE__);
		LuaHelper::exitAndShutdownLua(mLuaState);
		return false;
	}

	std::cerr << "Passed checking file name"<<m_path_source << std::endl;

	int luaResult = 20;
	luaResult = luaL_loadfile(mLuaState, m_path_source);
	//std::cerr << "Printing Lua result" << luaResult << std::endl;
	
	if(luaResult != LUA_OK)
	{
		errorMessage << "Lua is unable to parse the file. Please check the file" << m_path_source<<" Error found "<<lua_tostring(mLuaState,1);
		lua_pop(mLuaState, 1);//Popping out the error message
		LuaHelper::OutputErrorMessage(errorMessage.str().c_str(), __FILE__);
		LuaHelper::exitAndShutdownLua(mLuaState);
		return false;
	}

	int returnCount = LUA_MULTRET; //Returns everything in one go
	int argument = 0;
	int noMessageHandler = 0;

	luaResult = lua_pcall(mLuaState, argument, returnCount, noMessageHandler);

	if(!LuaHelper::isLuaResultOkay(mLuaState, luaResult) || returnCount>1 || !LuaHelper::isTable(mLuaState))
	{
		errorMessage << "Something went wrong. Please check the " << m_path_source << " file";
		LuaHelper::OutputErrorMessage(errorMessage.str().c_str(), __FILE__);
		LuaHelper::exitAndShutdownLua(mLuaState);
		return false;
	}

	//lua_pushstring(mLuaState, "name");
	//lua_gettable(mLuaState, -2);
	//effectName = lua_tostring(mLuaState, -1);
	//lua_pop(mLuaState, 1); //Popping out the effect name

	lua_pushstring(mLuaState, "vertex");
	lua_gettable(mLuaState, -2);
	vertexName = lua_tostring(mLuaState, -1);
	lua_pop(mLuaState, 1);//Popping out the vertex shader file name

	lua_pushstring(mLuaState, "fragment");
	lua_gettable(mLuaState, -2);
	fragmentName = lua_tostring(mLuaState, -1);
	lua_pop(mLuaState, 1);//Popping out the fragment shader file name

	lua_pop(mLuaState, 1);//Popping out the whole table
	LuaHelper::exitAndShutdownLua(mLuaState);

#if _DEBUG
	//std::cerr << effectName.c_str()<<fragmentName.c_str()<<vertexName.c_str();
#endif

	return true;
}
