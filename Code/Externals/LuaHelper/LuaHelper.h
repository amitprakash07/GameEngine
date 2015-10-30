#ifndef __LUA_HELPER_H
#define __LUA_HELPER_H

#include "../Lua/Includes.h"
#include <sstream>

namespace LuaHelper
{
	//Error Check Helper Functions
	bool isString(lua_State*);
	bool isTable(lua_State*);
	bool isValueNil(lua_State*);
	bool isValueNumber(lua_State*);
	bool isLuaResultOkay(lua_State*, int);
	bool exitAndShutdownLua(lua_State *);
	void OutputErrorMessage(const char* const i_errorMessage, const char* const i_optionalFileName = nullptr);
}

#endif