#include "Mesh.h"
#include "../../Engine/Windows/WindowsFunctions.h"
#include "../../Externals/Lua/Includes.h"
#include "MeshLoadFromLua.h"
#include <iostream>

Tools::AssetBuilder::vertex* Tools::AssetBuilder::Mesh::getVertex()
{
	if (mVertex)
		return mVertex;
	return nullptr;
}

uint32_t* Tools::AssetBuilder::Mesh::getIndices()
{
	if (mIndices)
	{
		uint32_t* indices = new uint32_t[triangleCount * 3];
		for (int i = 0; i < triangleCount; i++)
		{
			indices[i * 3 + 0] = mIndices[i].first;
			indices[i * 3 + 1] = mIndices[i].second;
			indices[i * 3 + 2] = mIndices[i].third;
		}
		return indices;
	}
	return nullptr;
}

int Tools::AssetBuilder::Mesh::getVertexCount()
{
	return vertexCount;
}

int Tools::AssetBuilder::Mesh::getTriangleCount()
{
	return triangleCount;
}

void Tools::AssetBuilder::Mesh::setMeshFileName(std::string i_fileName)
{
	if (!i_fileName.empty())
	{
		meshFileName = i_fileName;
		//memcpy(meshFileName, i_fileName, sizeof(char)*strlen(i_fileName));
	}
}

std::string Tools::AssetBuilder::Mesh::getMeshFileName()
{
	if (!meshFileName.empty())
		return meshFileName;
	return nullptr;
}

void Tools::AssetBuilder::Mesh::setWinding(winding i_winding)
{
	mWinding = i_winding;
}

Tools::AssetBuilder::winding Tools::AssetBuilder::Mesh::getWinding()
{
	return mWinding;
}

Tools::AssetBuilder::triangleIndex* Tools::AssetBuilder::Mesh::getTriangleIndicesList()
{
	if (mIndices)
		return mIndices;
	return nullptr;
}

bool Tools::AssetBuilder::Mesh::LoadMesh()
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
	if(meshFileName.empty())
	{
		errormessage << "No File Name for the mesh. Call setMeshFileName(char*) before calling LoadMesh()";
		WindowsUtil::Print(errormessage.str());
		exitAndShutdownLua(mLuaState);
		return false;
	}
		
	int luaResult = luaL_loadfile(mLuaState, meshFileName.c_str());

	//Checking the load was successful or not
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
		vertexCount = luaL_len(mLuaState, -1);
		if (vertexCount > 0)
		{
			mVertex = new vertex[vertexCount];
			if (!LuaLoadVertex(mLuaState, this))
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

		lua_pushstring(mLuaState, "nooftriangles");
		lua_gettable(mLuaState, -2);
		triangleCount = static_cast<int>(lua_tonumber(mLuaState, -1));
		lua_pop(mLuaState, 1);// Popping out the nooftriangles

		if (triangleCount > 0)
		{
			mIndices = new triangleIndex[triangleCount];
			if (!LuaLoadTriangleIndex(mLuaState, this))
				return false;
		}
	}

	lua_pop(mLuaState, 1); //Popping out the indices table

	lua_pop(mLuaState, 1); //Popping out complete table
	exitAndShutdownLua(mLuaState);
	return true;
}

Tools::AssetBuilder::Mesh::~Mesh()
{
	if (mVertex)
	{
		delete mVertex;
		mVertex = nullptr;
	}

	if (mIndices)
	{
		delete mIndices;
		mIndices = nullptr;
	}
}

#ifdef BUILD_DEBUG
void Tools::AssetBuilder::Mesh::displayVertices()
{
	std::cout << "Size of Vertex is" << sizeof(vertex) << std::endl;
	for (int i = 0; i < vertexCount; i++)
	{
		if(mVertex)
		{
			std::cout << "\nPosition = [" << mVertex[i].X << " , " << mVertex[i].Y << " ]\n";
			std::cout << "\nColor =[" << mVertex[i].R << "," << mVertex[i].G << "," << mVertex[i].B << "," << mVertex[i].A << "]\n";
		}
	}
}
#endif
