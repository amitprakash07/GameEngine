#ifndef __ASSET_BUILDER_H
#define __ASSET_BUILDER_H

#include "../../Externals/Lua/Includes.h"

namespace Tools
{
	namespace AssetBuilder
	{
		class AssetBuilderUsingLua
		{
		public:
			static bool Initialize(); //Initializing Lua
			static bool BuildAsset(const char* const i_relativePath);			
			static bool ShutDown(); //Shutting Down Lua
			static void OutputErrorMessage(const char* const i_errorMessage, const char* const i_optionalFileName = NULL);
		private:
			static lua_State * mLuaState;
			static int luaCopyFile(lua_State * i_luaState = mLuaState);
			static int luaCreateDirectoryIfNecessary(lua_State * i_luaState = mLuaState);
			static int luaDoesFileExist(lua_State * i_luaState = mLuaState);
			static int luaGetEnvironmentVariable(lua_State * i_luaState = mLuaState);
			static int luaGetLastWriteTime(lua_State * i_luaState = mLuaState);
			static int luaOutputErrorMessage(lua_State * i_luaState = mLuaState);
		};

	}
}

#endif