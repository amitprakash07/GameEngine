// Header Files
//=============

#include "AssetBuilder.h"

#include <iostream>
#include <string>
#include "../../Engine/Windows/WindowsFunctions.h"
#include "../../Externals/Lua/Includes.h"


		//int luaCopyFile(lua_State * i_lua_state);
lua_State* Tools::AssetBuilder::AssetBuilderUsingLua::mLuaState = nullptr;

bool Tools::AssetBuilder::AssetBuilderUsingLua::Initialize()
{
	// Create a new Lua state
	if (!mLuaState)
	{
		mLuaState = luaL_newstate();
		if (!mLuaState)
		{
			OutputErrorMessage("Memory allocation error creating Lua state", __FILE__);
			return false;
		}
	}

	// Open the standard libraries
	luaL_openlibs(mLuaState);

	// Register custom functions
	lua_register(mLuaState, "CopyFile", luaCopyFile);
	lua_register(mLuaState, "CreateDirectoryIfNecessary", luaCreateDirectoryIfNecessary);
	lua_register(mLuaState, "DoesFileExist", luaDoesFileExist);
	lua_register(mLuaState, "GetEnvironmentVariable", luaGetEnvironmentVariable);
	lua_register(mLuaState, "GetLastWriteTime", luaGetLastWriteTime);
	lua_register(mLuaState, "OutputErrorMessage", luaOutputErrorMessage);

	return true;
}


bool Tools::AssetBuilder::AssetBuilderUsingLua::BuildAssets()
{
	bool wereThereErrors = false;
	std::string errormessage;
	std::string scriptDir;
	//Getting ScriptDir path
	if(!WindowsUtil::GetEnvironmentVariableA("ScriptDir", scriptDir, &errormessage))
	{
		wereThereErrors = true;
		OutputErrorMessage(errormessage.c_str(), __FILE__);
		return !wereThereErrors;
	}

	//Loading BuildAssets.lua
	const std::string buildScript = scriptDir + "BuildAssets.lua";
	const int loadResult = luaL_loadfile(mLuaState, buildScript.c_str());

	if(loadResult == LUA_OK)
	{
		const int argumentCount = 1;
		const std::string assetToBuildListPath = scriptDir + "AssetsToBuild.lua";
		const int returnValueCount = 1;
		const int noMessagehandler = 0;
		lua_pushstring(mLuaState, assetToBuildListPath.c_str());
		const int buildAssetResult = lua_pcall(mLuaState, argumentCount, returnValueCount, noMessagehandler);
		
		if(buildAssetResult == LUA_OK)
		{
			wereThereErrors = !lua_toboolean(mLuaState, -1);
			lua_pop(mLuaState, returnValueCount);
		}
		else
		{
			wereThereErrors = true;
			errormessage = lua_tostring(mLuaState, -1);
			OutputErrorMessage(errormessage.c_str(), "BuildAssets.lua");
			lua_pop(mLuaState, 1);
			return !wereThereErrors;
		}
	}
	else
	{
		wereThereErrors = true;
		std::stringstream othererrormessage;
		othererrormessage << "Something wrong with your script file" << buildScript.c_str();
		OutputErrorMessage(othererrormessage.str().c_str());
	}
	return !wereThereErrors;
}
		
bool Tools::AssetBuilder::AssetBuilderUsingLua::ShutDown()
{
	bool wereThereErrors = false;
	if (mLuaState)
	{
		lua_close(mLuaState);
		mLuaState = nullptr;
	}
	return !wereThereErrors;
}

		// Helper Function Definitions
		//============================

void Tools::AssetBuilder::AssetBuilderUsingLua::OutputErrorMessage(const char* const i_errorMessage, const char* const i_optionalFileName)
{
	// This formatting causes the errors to show up in Visual Studio's "Error List" tab
	std::stringstream errormessage;
	errormessage << (i_optionalFileName ? i_optionalFileName : "Asset Build") << ": error: " <<
		i_errorMessage << "\n";
	WindowsUtil::Print(errormessage.str());
}

		// Lua Wrapper Functions
		//----------------------

int Tools::AssetBuilder::AssetBuilderUsingLua::luaCopyFile(lua_State * i_luaState)
{
	// Argument #1: The source path
	const char* i_path_source = lua_tostring(i_luaState, 1);
	//EAE6320_TODO	// How do you get the source path from the Lua state?
					// Argument #2: The target path
	const char* i_path_target = lua_tostring(i_luaState, 2);
	//EAE6320_TODO	// How do you get the target path from the Lua state?

					// Copy the file
	std::string errorMessage;
	// There are many reasons that a source should be rebuilt,
	// and so even if the target already exists it should just be written over
	const bool noErrorIfTargetAlreadyExists = false;
	// Since we rely on timestamps to determine when a target was built
	// its file time should be updated when the source gets copied
	const bool updateTheTargetFileTime = true;
	if (WindowsUtil::CopyFile(i_path_source, i_path_target, noErrorIfTargetAlreadyExists, updateTheTargetFileTime, &errorMessage))
	{
		lua_pushboolean(i_luaState, true);
		lua_pushstring(i_luaState, "Success");
		//EAE6320_TODO	// Return a boolean [true]
	}
	else
	{
		lua_pushboolean(i_luaState, false);
		lua_pushstring(i_luaState, "Failed");
		//EAE6320_TODO	// On failure return two values: a boolean [false] and the error message
	}
	return 2;
}

int Tools::AssetBuilder::AssetBuilderUsingLua::luaCreateDirectoryIfNecessary(lua_State * i_luaState)
{
	// Argument #1: The path
	const char* i_path = lua_tostring(i_luaState, 1);

	std::string errorMessage;
	if (WindowsUtil::CreateDirectoryIfNecessary(i_path, &errorMessage))
	{
		return 0;
		//EAE6320_TODO	// Return nothing
	}
	else
	{
		//EAE6320_TODO	// Throw a Lua error with the error message
		lua_pushstring(i_luaState, "Something Went wrong");
		return 1;
	}

}

int Tools::AssetBuilder::AssetBuilderUsingLua::luaDoesFileExist(lua_State * i_luaState)
{
	// Argument #1: The path
	const char* i_path = lua_tostring(i_luaState, 1);
	if (lua_isstring(mLuaState, 1))
	{
		i_path = lua_tostring(mLuaState, 1);
	}
	else
	{
		return luaL_error(mLuaState,
			"Argument #1 must be a string (instead of a %s)",
			luaL_typename(mLuaState, 1));
	}

	DWORD errorCode;
	std::string errorMessage;
	if (WindowsUtil::DoesFileExist(i_path, &errorMessage, &errorCode))
	{
		lua_pushboolean(i_luaState, true);
		const int returnValueCount = 1;
		return returnValueCount;
	}
	else
	{
		// If DoesFileExist() returns false because the file doesn't exist
		// (i.e. the common case)
		// then the Lua function should also return false
		// (the "error message" will also be returned, although it's implied by the return value)
		if ((errorCode == ERROR_FILE_NOT_FOUND) || (errorCode == ERROR_PATH_NOT_FOUND))
		{
			lua_pushboolean(i_luaState, false);
			lua_pushstring(i_luaState, errorMessage.c_str());
			const int returnValueCount = 2;
			return returnValueCount;
		}
		else
		{
			// If DoesFileExist() fails for a non-standard error, though,
			// then the Lua function will throw an error
			return luaL_error(i_luaState, errorMessage.c_str());
		}
	}
}

int Tools::AssetBuilder::AssetBuilderUsingLua::luaGetEnvironmentVariable(lua_State * i_luaState)
{
	// Argument #1: The key
	const char* i_key = lua_tostring(i_luaState, 1);
	// How do you get the key from the Lua state?
	std::string value;
	std::string errorMessage;
	if (WindowsUtil::GetEnvironmentVariable(i_key, value))
	{
		lua_pushstring(i_luaState, value.c_str());
		lua_pushstring(i_luaState, errorMessage.c_str());
	}
	else
	{
		lua_pushstring(i_luaState, "nil");
		lua_pushstring(i_luaState, errorMessage.c_str());
	}
	return 2;
}

int Tools::AssetBuilder::AssetBuilderUsingLua::luaGetLastWriteTime(lua_State * i_luaState)
{
	// Argument #1: The path
	const char* i_path = lua_tostring(i_luaState, 1);

	// Get the last time that the file was written to
	uint64_t lastWriteTime;
	std::string errorMessage;
	std::stringstream other_message;
	if (WindowsUtil::GetLastWriteTime(i_path, lastWriteTime, &errorMessage))
	{
		const lua_Number lastWriteTime_asNumber = static_cast<lua_Number>(lastWriteTime);
		other_message << lastWriteTime_asNumber << " Before conversion " << lastWriteTime;
		lua_pushnumber(i_luaState, lastWriteTime_asNumber);
		return 1;
	}
	else
	{
		lua_pushnumber(i_luaState, 1);
		lua_pushstring(i_luaState, errorMessage.c_str());
		return 2; 
	}

}

int Tools::AssetBuilder::AssetBuilderUsingLua::luaOutputErrorMessage(lua_State * i_luaState)
{
	// Argument #1: The error message
	const char* i_errorMessage = lua_tostring(i_luaState, 1);


	// Argument #2: An optional file name
	const char* i_optionalFileName = nullptr;

	if (!lua_isnil(mLuaState, 2))
	{
		// How do you get the file name from the Lua state?
		i_optionalFileName = lua_tostring(i_luaState, 2);
	}

	// Output the error message
	OutputErrorMessage(i_errorMessage, i_optionalFileName);

	// Return nothing
	return 0;
}

