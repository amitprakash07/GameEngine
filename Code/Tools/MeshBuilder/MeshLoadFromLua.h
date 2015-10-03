#ifndef __MESHLOAD_FRAOM_LUA_H
#define __MESHLOAD_FRAOM_LUA_H

#include "../../Externals/Lua/Includes.h"

namespace Tools
{
	namespace AssetBuilder
	{
		class Mesh;
	}
}

		//Error Check Helper Functions
		bool isString(lua_State*);
		bool isTable(lua_State*);
		bool isValueNil(lua_State*);
		bool isValueNumber(lua_State*);
		bool isLuaResultOkay(lua_State*, int);

		//Lua Loading Helper Functions
		bool LuaLoadVertex(lua_State*, Tools::AssetBuilder::Mesh*);
		bool LuaLoadTriangleIndex(lua_State*, Tools::AssetBuilder::Mesh*);
		bool exitAndShutdownLua(lua_State *);

#endif