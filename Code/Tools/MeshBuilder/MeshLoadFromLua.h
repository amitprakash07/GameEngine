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

		//Lua Loading Helper Functions
		bool LuaLoadVertex(lua_State*, Tools::AssetBuilder::Mesh*);
		bool LuaLoadTriangleIndex(lua_State*, Tools::AssetBuilder::Mesh*);
		

#endif