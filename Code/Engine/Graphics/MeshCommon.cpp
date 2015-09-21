#include "Mesh.h"
#include "../../Externals/Lua/Includes.h"
#include "../Windows/WindowsFunctions.h"
#include <sstream>
#include <assert.h>

#define MESHFILE_PATH "data/Mesh.lua"

Engine::Graphics::vertex* Engine::Graphics::Mesh::mVertex = nullptr;
Engine::Graphics::triangleIndex* Engine::Graphics::Mesh::mIndices = nullptr;
Engine::Graphics::winding Engine::Graphics::Mesh::mWinding = Engine::Graphics::RIGHT;

//Error Check Helper Functions
bool isString(lua_State*);
bool isTable(lua_State*);
bool isValueNil(lua_State*);
bool isValueNumber(lua_State*);
bool isLuaResultOkay(lua_State*, int);

//Lua Loading Helper Functions
bool LuaLoadVertex(lua_State*);
bool LuaLoadTriangleIndex(lua_State*);
bool exitAndShutdownLua(lua_State *);

Engine::Graphics::vertex* Engine::Graphics::Mesh::getVertex()
{
	if (mVertex)
		return mVertex;
	return nullptr;
}

uint32_t* Engine::Graphics::Mesh::getIndices()
{
	if (mIndices)
	{
		uint32_t* indices = new uint32_t[6];
		indices[0] = mIndices[0].first;
		indices[1] = mIndices[0].second;
		indices[2] = mIndices[0].third;
		indices[3] = mIndices[1].first;
		indices[4] = mIndices[1].second;
		indices[5] = mIndices[1].third;
		return indices;
	}
	return nullptr;
}

void Engine::Graphics::Mesh::setWinding(winding i_winding)
{
	mWinding = i_winding;
}

Engine::Graphics::winding Engine::Graphics::Mesh::getWinding()
{
	return mWinding;
}

Engine::Graphics::triangleIndex* Engine::Graphics::Mesh::getTriangleIndicesList()
{
	if (mIndices)
		return mIndices;
	return nullptr;
}

bool Engine::Graphics::Mesh::LoadMesh()
{
	lua_State *mLuaState = nullptr;
	std::stringstream errormessage;
	mLuaState = luaL_newstate();

	//Creating Lua State
	if (!mLuaState)
	{
		errormessage << "Failed to create a new Lua state \n";
		WindowsUtil::Print(errormessage.str());
		exitAndShutdownLua(mLuaState);
		return false;
	}

	//Loading the lua file
	int luaResult = luaL_loadfile(mLuaState, MESHFILE_PATH);

	//Checking the was successful or not
	if (luaResult != LUA_OK)
	{
		errormessage << "Unable to load the file. \n" << lua_tostring(mLuaState, 1);

		//Popping out the error message
		lua_pop(mLuaState, 1);
		WindowsUtil::Print(errormessage.str());
		exitAndShutdownLua(mLuaState);
		return false;
	}

	//Extracting the table at once in a single return
	int returnCount = LUA_MULTRET; // Return _everything_ that the file returns
	int argumentCount = 0;
	int noMessageHandler = 0;

	luaResult = lua_pcall(mLuaState, argumentCount, returnCount, noMessageHandler);
	if (!isLuaResultOkay(mLuaState, luaResult) || returnCount > 1 || !isTable(mLuaState))
	{
		exitAndShutdownLua(mLuaState);
		return false;
	}

	const char* vertices = "vertices";
	lua_pushstring(mLuaState, vertices);
	lua_gettable(mLuaState, -2);

	if (isTable(mLuaState)) //Vertices Table
	{
		const int VerticesCount = luaL_len(mLuaState, -1);
		if (VerticesCount > 0)
		{
			mVertex = new vertex[VerticesCount];
			if (!LuaLoadVertex(mLuaState))
				return false;
		}
		else
		{
			errormessage << "No Vertices in the Lua file \n.";
			WindowsUtil::Print(errormessage.str());
			exitAndShutdownLua(mLuaState);
			return false;
		}

	}
	lua_pop(mLuaState, 1); //Popping out the vertices Table


	const char* indices = "indices";
	lua_pushstring(mLuaState, indices);
	lua_gettable(mLuaState, -2);
	if (isTable(mLuaState)) //indices Table
	{

		int traingleCount;
		lua_pushstring(mLuaState, "nooftriangles");
		lua_gettable(mLuaState, -2);
		traingleCount = static_cast<int>(lua_tonumber(mLuaState, -1));
		lua_pop(mLuaState, 1);// Popping out the nooftriangles

		if (traingleCount > 0)
		{
			mIndices = new triangleIndex[traingleCount];
			if (!LuaLoadTriangleIndex(mLuaState))
				return false;
		}
	}

	lua_pop(mLuaState, 1); //Popping out the indices table

	lua_pop(mLuaState, 1); //Popping out complete table
	exitAndShutdownLua(mLuaState);
	return true;
}

bool LuaLoadVertex(lua_State* i_luaState)
{
	int vertexCount = luaL_len(i_luaState, -1);

	Engine::Graphics::vertex* tempVertex = Engine::Graphics::Mesh::getVertex();
	if (!tempVertex)
		return false;

	for (int i = 1; i <= vertexCount; i++)
	{
		int vertexIndex;
		lua_pushinteger(i_luaState, i);
		lua_gettable(i_luaState, -2);

		lua_pushstring(i_luaState, "index");
		lua_gettable(i_luaState, -2);
		vertexIndex = static_cast<int>(lua_tonumber(i_luaState, -1));
		lua_pop(i_luaState, 1); //popping out index


		//Retrieving the positions of the vertex
		lua_pushstring(i_luaState, "position");
		lua_gettable(i_luaState, -2); //Lua Stack contains position table at -2


		int counts = luaL_len(i_luaState, -1);
		if(counts < 2 )
		{
			std::stringstream errormessage;
			errormessage << "Atleast x and y coordinates are required for a vertex. found " << counts << "\n";
			WindowsUtil::Print(errormessage.str());
			return false;
		}
		for (int i = 1; i <= counts; i++)
		{
			//traversing in the position array by pushing index
			lua_pushinteger(i_luaState, i);
			lua_gettable(i_luaState, -2);
			switch (i - 1)
			{
			case 0:
				tempVertex[vertexIndex].X = static_cast<float>(lua_tonumber(i_luaState, -1));
				break;
			case 1:
				tempVertex[vertexIndex].Y = static_cast<float>(lua_tonumber(i_luaState, -1));
				break;
			/*case 3:
				tempVertex[vertexIndex].Z = static_cast<float>(lua_tonumber(i_luaState, -1));*/
			}
			lua_pop(i_luaState, 1);//Popping out the previous position value
		}

		lua_pop(i_luaState, 1); //Popping out the position table


		//Retrieving the color of the vertex
		lua_pushstring(i_luaState, "color");
		lua_gettable(i_luaState, -2);
		int countColorChannels = luaL_len(i_luaState, -1);
		if(countColorChannels <3)
		{
			std::stringstream errormessage;
			errormessage << "Atleast 3 color channels are required to color the vertex. Found " << countColorChannels << "\n";
			WindowsUtil::Print(errormessage.str());
			return false;
		}

		for (int i = 1; i <= countColorChannels; i++)
		{
			//traversing in the color field array by pushing the index
			lua_pushinteger(i_luaState, i);
			lua_gettable(i_luaState, -2);
			switch (i - 1)
			{
			case 0:
				tempVertex[vertexIndex].R = static_cast<uint8_t>(lua_tonumber(i_luaState, -1) * 255);
				break;
			case 1:
				tempVertex[vertexIndex].G = static_cast<uint8_t>(lua_tonumber(i_luaState, -1) * 255);
				break;
			case 2:
				tempVertex[vertexIndex].B = static_cast<uint8_t>(lua_tonumber(i_luaState, -1) * 255);
				break;
			case 3:
				tempVertex[vertexIndex].A = static_cast<uint8_t>(lua_tonumber(i_luaState, -1) * 255);
				break;
			}
			lua_pop(i_luaState, 1);//Popping out the previous color value
		}

		lua_pop(i_luaState, 1); //Popping out the color table

		lua_pop(i_luaState, 1); //Popping out the pushed vertex data
	}
	return true;
}

bool LuaLoadTriangleIndex(lua_State* i_luaState)
{
	int indicesCount;
	Engine::Graphics::triangleIndex* tempIndices = Engine::Graphics::Mesh::getTriangleIndicesList();
	Engine::Graphics::winding defaultWinding;
	lua_pushstring(i_luaState, "winding");
	lua_gettable(i_luaState, -2);

	std::string windingValue = lua_tostring(i_luaState, -1);
	if (strcmp(windingValue.c_str(), "right") == 0)
		defaultWinding = Engine::Graphics::RIGHT;
	else
		defaultWinding = Engine::Graphics::LEFT;

	Engine::Graphics::Mesh::setWinding(defaultWinding);

	lua_pop(i_luaState, 1); //Popping out the winding table

	indicesCount = luaL_len(i_luaState, -1);
	for (int i = 1; i <= indicesCount; i++)
	{
		lua_pushinteger(i_luaState, i);
		lua_gettable(i_luaState, -2);

		if (!tempIndices)
			return false;

		int indices = luaL_len(i_luaState, -1);
		for (int j = 1; j <= indices; j++)
		{
			lua_pushinteger(i_luaState, j);
			lua_gettable(i_luaState, -2);
			switch (j - 1)
			{
			case 0:
				tempIndices[i - 1].first = static_cast<uint8_t>(lua_tointeger(i_luaState, -1));
				break;
			case 1:
				tempIndices[i - 1].second = static_cast<uint8_t>(lua_tointeger(i_luaState, -1));
				break;
			case 2:
				tempIndices[i - 1].third = static_cast<uint8_t>(lua_tointeger(i_luaState, -1));
				break;
			}
			
			lua_pop(i_luaState, 1); //Popping out the every index order data


		}
#ifdef PLATFORM_D3D
		if (Engine::Graphics::Mesh::getWinding() == Engine::Graphics::RIGHT)
		{
			int temp = tempIndices[i - 1].second;
			tempIndices[i - 1].second = tempIndices[i - 1].third;
			tempIndices[i - 1].third = temp;
		}
#endif

#ifdef PLATFORM_OPEN_GL
		if (Engine::Graphics::Mesh::getWinding() == Engine::Graphics::LEFT)
		{
			int temp = tempIndices[i - 1].second;
			tempIndices[i - 1].second = tempIndices[i - 1].third;
			tempIndices[i - 1].third = temp;
		}
#endif
		lua_pop(i_luaState, 1); //Popping out the indices array
	}

	return true;
}


/**********************************************Lua Error Check Helper Functions*******************************************/
bool isString(lua_State * luaState)
{
	if (lua_type(luaState, -1) != LUA_TSTRING)
	{
		std::stringstream errorMessage;
		errorMessage << "The value for  must be a string  (instead of a " << luaL_typename(luaState, -1) << ")\n";
		WindowsUtil::Print(errorMessage.str());
		return false;
	}
	return true;
}

bool isTable(lua_State* luaState)
{
	if (!lua_istable(luaState, -1))
	{
		std::stringstream errorMessage;
		errorMessage << "Asset files must return a table (instead of a " << luaL_typename(luaState, -1) << ")\n";
		WindowsUtil::Print(errorMessage.str());
		return false;
	}
	return true;
}

bool isValueNil(lua_State * luaState)
{

	if (lua_isnil(luaState, -1))
	{
		std::stringstream errorMessage;
		errorMessage << "No value for the given key  was found in the asset table \n";
		WindowsUtil::Print(errorMessage.str());
		return true;
	}
	return false;
}

bool isValueNumber(lua_State* luaState)
{
	if (lua_type(luaState, -1) != LUA_TNUMBER)
	{
		std::stringstream errorMessage;
		errorMessage << "The Value for the key is not a double \n";
		WindowsUtil::Print(errorMessage.str());
		return false;
	}
	return true;
}

bool exitAndShutdownLua(lua_State *i_luaState)
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
	WindowsUtil::Print(errormessage.str());
	return true;
}

bool isLuaResultOkay(lua_State *i_luaState, int result)
{
	if (result != LUA_OK)
	{
		std::stringstream errormessage;
		errormessage << "Unable to load the file. \n" << lua_tostring(i_luaState, 1);

		//Popping out the error message
		lua_pop(i_luaState, 1);
		WindowsUtil::Print(errormessage.str());
		exitAndShutdownLua(i_luaState);
		return false;
	}
	return true;
}
/*************************************************************************************************************************************/