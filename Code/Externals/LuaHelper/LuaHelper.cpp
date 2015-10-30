#include "LuaHelper.h"
#include  <sstream>
#include <assert.h>
#include <iostream>

/**********************************************Lua Error Check Helper Functions*******************************************/
bool LuaHelper::isString(lua_State * luaState)
{
	if (lua_type(luaState, -1) != LUA_TSTRING)
	{
		std::stringstream errorMessage;
		errorMessage << "The value for  must be a string  (instead of a " << luaL_typename(luaState, -1) << ")\n";
		OutputErrorMessage(errorMessage.str().c_str());
		return false;
	}
	return true;
}


bool LuaHelper::isTable(lua_State* luaState)
{
	if (!lua_istable(luaState, -1))
	{
		std::stringstream errorMessage;
		errorMessage << "Asset files must return a table (instead of a " << luaL_typename(luaState, -1) << ")\n";
		OutputErrorMessage(errorMessage.str().c_str());
		return false;
	}
	return true;
}


bool LuaHelper::isValueNil(lua_State * luaState)
{

	if (lua_isnil(luaState, -1))
	{
		std::stringstream errorMessage;
		errorMessage << "No value for the given key  was found in the asset table \n";
		OutputErrorMessage(errorMessage.str().c_str());
		return true;
	}
	return false;
}


bool LuaHelper::isValueNumber(lua_State* luaState)
{
	if (lua_type(luaState, -1) != LUA_TNUMBER)
	{
		std::stringstream errorMessage;
		errorMessage << "The Value for the key is not a double \n";
		OutputErrorMessage(errorMessage.str().c_str());
		return false;
	}
	return true;
}


bool LuaHelper::exitAndShutdownLua(lua_State *i_luaState)
{
	if (i_luaState)
	{
		assert(lua_gettop(i_luaState) == 0);
		lua_close((i_luaState));
		i_luaState = nullptr;
		return true;
	}
	std::stringstream errormessage;
	errormessage << "Lua state is already NULL. No need to shutdown again\n";
	OutputErrorMessage(errormessage.str().c_str());
	return true;
}

bool LuaHelper::isLuaResultOkay(lua_State *i_luaState, int result)
{
	if (result != LUA_OK)
	{
		std::stringstream errormessage;
		errormessage << "Unable to load the file. \n" << lua_tostring(i_luaState, 1);

		//Popping out the error message
		lua_pop(i_luaState, 1);
		OutputErrorMessage(errormessage.str().c_str());
		exitAndShutdownLua(i_luaState);
		return false;
	}
	return true;
}


void LuaHelper::OutputErrorMessage(const char* const i_errorMessage, const char* const i_optionalFileName)
{
	// This formatting causes the errors to show up in Visual Studio's "Error List" tab
	std::stringstream errormessage;
	errormessage << (i_optionalFileName ? i_optionalFileName : "Asset Build") << ": error: " <<
		i_errorMessage << "\n";
	std::cerr << errormessage.str().c_str();
}
/*************************************************************************************************************************************/