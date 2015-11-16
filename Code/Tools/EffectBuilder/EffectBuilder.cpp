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
		/*std::cerr << "Vertex Length" << strlen(vertexName);
		std::cerr << std::endl<<vertexName;*/
		writeTofile.write(vertexName, sizeof(char)*strlen(vertexName));
		writeTofile.write("\0", sizeof(char));
		writeTofile.write(fragmentName, sizeof(char)* strlen(fragmentName));
		writeTofile.write("\0", sizeof(char));
		writeTofile.write(reinterpret_cast<const char*>(renderSate), sizeof(uint8_t));
		writeTofile.close();
		return true;
	}
	return false;
}

Tools::AssetBuilder::EffectBuilder::EffectBuilder()
{
	vertexName = nullptr;
	fragmentName = nullptr;
	renderSate = new uint8_t;
	*renderSate = 0;
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

	if(m_path_source == nullptr)
	{
		errorMessage << "Source Path is empty";
		LuaHelper::OutputErrorMessage(errorMessage.str().c_str(), __FILE__);
		LuaHelper::exitAndShutdownLua(mLuaState);
		return false;
	}

	int luaResult = 20;
	luaResult = luaL_loadfile(mLuaState, m_path_source);
	
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

	lua_pushstring(mLuaState, "vertex");
	lua_gettable(mLuaState, -2);
	size_t length = strlen(lua_tostring(mLuaState, -1)) + 1;
	//std::cerr << "Vertex Shader Length" << length;
	vertexName = new char[length];
	memcpy(vertexName,lua_tostring(mLuaState, -1), length);
	std::cerr << "Vertex Shader Name before null "<<vertexName;
	vertexName[length] = '\0';
	std::cerr << "Vertex Shader Name After adding null " << vertexName;
	//std::cerr << "Vertex Shader Name"<<vertexName;
	lua_pop(mLuaState, 1);//Popping out the vertex shader file name
	
	char * something = "something\0";
	std::cerr << "Printing something and it length" << something << strlen(something);

	lua_pushstring(mLuaState, "fragment");
	lua_gettable(mLuaState, -2);
	length = strlen(lua_tostring(mLuaState, -1)) + 1;
	fragmentName = new char[length];
	memcpy(fragmentName, lua_tostring(mLuaState, -1), length);
	fragmentName[length] = '\0';
	lua_pop(mLuaState, 1);//Popping out the fragment shader file name
	
	std::string status="";
	std::string temp = "";
	renderSate = new uint8_t;
	*renderSate = 0;
	
	/*std::cerr << "Let's Print "<<std::endl<<ALPHA_BLENDING << std::endl 
		<< DEPTH_TESTING << std::endl 
		<< DEPTH_WRITING << std::endl
		<< FACE_CULLING;*/

	lua_pushstring(mLuaState, "AlphaTransparency");
	lua_gettable(mLuaState, -2);
	status = lua_tostring(mLuaState, -1);
	if (status.compare("True") == 0)
		*renderSate |= ALPHA_BLENDING;
	
	lua_pop(mLuaState, 1);//Popping out the AlphaTransparency
	
	lua_pushstring(mLuaState, "DepthTesting");
	lua_gettable(mLuaState, -2);
	status = lua_tostring(mLuaState, -1);
	lua_pop(mLuaState, 1);//Popping out the DepthTesting
	if (status.compare("True") == 0)
		*renderSate |= DEPTH_TESTING;
		
	lua_pushstring(mLuaState, "DepthWriting");
	lua_gettable(mLuaState, -2);
	status = lua_tostring(mLuaState, -1);
	lua_pop(mLuaState, 1);//Popping out the DepthWriting
	if (status.compare("True") == 0)
		*renderSate |= DEPTH_WRITING;
			
	lua_pushstring(mLuaState, "FaceCulling");
	lua_gettable(mLuaState, -2);
	status = lua_tostring(mLuaState, -1);
	lua_pop(mLuaState, 1);//Popping out the FaceCulling
	if (status.compare("True") == 0)
		*renderSate |= FACE_CULLING;
		
	lua_pop(mLuaState, 1);//Popping out the whole table
	LuaHelper::exitAndShutdownLua(mLuaState);
	
#if _DEBUG
	//std::cerr << effectName.c_str()<<fragmentName.c_str()<<vertexName.c_str();
#endif

	return true;
}
