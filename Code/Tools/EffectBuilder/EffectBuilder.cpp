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
		/*
		File Format
		vertexShaderFileName
		fragmentShaderFileName
		renderStates

		noOfEngineUniforms
		UniformName
		shaderType
		valType
		MatrixType-optional
		valCount
		*/
		writeTofile.write(vertexName, sizeof(char)*strlen(vertexName));
		writeTofile.write("\0", sizeof(char));
		writeTofile.write(fragmentName, sizeof(char)* strlen(fragmentName));
		writeTofile.write("\0", sizeof(char));
		writeTofile.write(reinterpret_cast<const char*>(renderSate), sizeof(uint8_t));

		writeTofile.write(reinterpret_cast<const char*>(&uniformCount), sizeof(uint8_t));
		if (uniformCount > 0)
		{
			for (int i = 0; i < uniformCount; ++i)
			{
				writeTofile.write(uniforms[i].uniformName, sizeof(char)*strlen(uniforms[i].uniformName));
				writeTofile.write("\0", sizeof(char));
				writeTofile.write(reinterpret_cast<char*>(&uniforms[i].shaderType), sizeof(Engine::Graphics::ShaderType));
				writeTofile.write(reinterpret_cast<char*>(&uniforms[i].uniformValType), sizeof(Engine::Graphics::UniformDataType));
				if (uniforms[i].uniformValType == Engine::Graphics::Matrix)
				{
					writeTofile.write(reinterpret_cast<char*>(&uniforms[i].matrixType), sizeof(Engine::Graphics::Transform_Matrix_Type));
				}
				writeTofile.write(reinterpret_cast<char*>(&uniforms[i].valCount), sizeof(uint8_t));
			}
		}

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
	uniforms = nullptr;
	uniformCount = 0;
}


bool Tools::AssetBuilder::EffectBuilder::LoadEffectFile()
{
	lua_State *mLuaState = nullptr;
	std::stringstream errorMessage;
	mLuaState = luaL_newstate();

	if (!mLuaState)
	{
		errorMessage << "Failed to create a new Lua state \n";
		LuaHelper::OutputErrorMessage(errorMessage.str().c_str(), __FILE__);
		LuaHelper::exitAndShutdownLua(mLuaState);
		return false;
	}

	if (m_path_source == nullptr)
	{
		errorMessage << "Source Path is empty";
		LuaHelper::OutputErrorMessage(errorMessage.str().c_str(), __FILE__);
		LuaHelper::exitAndShutdownLua(mLuaState);
		return false;
	}

	int luaResult = 20;
	luaResult = luaL_loadfile(mLuaState, m_path_source);

	if (luaResult != LUA_OK)
	{
		errorMessage << "Lua is unable to parse the file. Please check the file" << m_path_source << " Error found " << lua_tostring(mLuaState, 1);
		lua_pop(mLuaState, 1);//Popping out the error message
		LuaHelper::OutputErrorMessage(errorMessage.str().c_str(), __FILE__);
		LuaHelper::exitAndShutdownLua(mLuaState);
		return false;
	}

	int returnCount = LUA_MULTRET; //Returns everything in one go
	int argument = 0;
	int noMessageHandler = 0;

	luaResult = lua_pcall(mLuaState, argument, returnCount, noMessageHandler);

	if (!LuaHelper::isLuaResultOkay(mLuaState, luaResult) || returnCount > 1 || !LuaHelper::isTable(mLuaState))
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
	memcpy(vertexName, lua_tostring(mLuaState, -1), length);
	vertexName[length] = '\0';
	lua_pop(mLuaState, 1);//Popping out the vertex shader file name


	lua_pushstring(mLuaState, "fragment");
	lua_gettable(mLuaState, -2);
	length = strlen(lua_tostring(mLuaState, -1)) + 1;
	fragmentName = new char[length];
	memcpy(fragmentName, lua_tostring(mLuaState, -1), length);
	fragmentName[length] = '\0';
	lua_pop(mLuaState, 1);//Popping out the fragment shader file name

	std::string status = "";
	std::string temp = "";
	renderSate = new uint8_t;
	*renderSate = 0;

	lua_pushstring(mLuaState, "AlphaTransparency");
	lua_gettable(mLuaState, -2);
	status = lua_tostring(mLuaState, -1);
	if (status.compare("True") == 0)
		*renderSate |= Engine::Graphics::ALPHA_BLENDING;

	lua_pop(mLuaState, 1);//Popping out the AlphaTransparency

	lua_pushstring(mLuaState, "DepthTesting");
	lua_gettable(mLuaState, -2);
	status = lua_tostring(mLuaState, -1);
	lua_pop(mLuaState, 1);//Popping out the DepthTesting
	if (status.compare("True") == 0)
		*renderSate |= Engine::Graphics::DEPTH_TESTING;

	lua_pushstring(mLuaState, "DepthWriting");
	lua_gettable(mLuaState, -2);
	status = lua_tostring(mLuaState, -1);
	lua_pop(mLuaState, 1);//Popping out the DepthWriting
	if (status.compare("True") == 0)
		*renderSate |= Engine::Graphics::DEPTH_WRITING;

	lua_pushstring(mLuaState, "FaceCulling");
	lua_gettable(mLuaState, -2);
	status = lua_tostring(mLuaState, -1);
	lua_pop(mLuaState, 1);//Popping out the FaceCulling
	if (status.compare("True") == 0)
		*renderSate |= Engine::Graphics::FACE_CULLING;



SHADER_UNIFORM:
	{
		lua_pushstring(mLuaState, "uniforms");
		lua_gettable(mLuaState, -2);
		if (LuaHelper::isTable(mLuaState))
		{
			uniformCount = luaL_len(mLuaState, -1);
			if (uniformCount > 0)
			{
				uniforms = new ShaderUniformDef[uniformCount];
				for (int i = 1; i <= uniformCount; ++i)
				{
					lua_pushinteger(mLuaState, i);
					lua_gettable(mLuaState, -2);

					//Name
					{
						lua_pushstring(mLuaState, "name");
						lua_gettable(mLuaState, -2);
						const char* tempUniformName = lua_tostring(mLuaState, -1);
						size_t uniformNamelength = strlen(tempUniformName);
						uniforms[i - 1].uniformName = new char[uniformNamelength];
						memcpy(uniforms[i - 1].uniformName, tempUniformName, uniformNamelength);
						uniforms[i - 1].uniformName[uniformNamelength] = '\0';
						lua_pop(mLuaState, 1);//Popping out "name"
					}

					//Shader Type
					{
						lua_pushstring(mLuaState, "shader");
						lua_gettable(mLuaState, -2);
						const char* shaderType = lua_tostring(mLuaState, -1);
						if (strcmp(shaderType, "vertex") == 0)
							uniforms[i - 1].shaderType = Engine::Graphics::Vertex;
						lua_pop(mLuaState, 1);//Popping "Shader"
					}

					//Val type
					{
						lua_pushstring(mLuaState, "valType");
						lua_gettable(mLuaState, -2);
						const char* shaderType = lua_tostring(mLuaState, -1);
						lua_pop(mLuaState, 1); //Popping "valType"

						if (strcmp(shaderType, "Matrix") == 0)
						{
							uniforms[i - 1].uniformValType = Engine::Graphics::Matrix;
							lua_pushstring(mLuaState, "MatrixType");
							lua_gettable(mLuaState, -2);
							const char* tempMatrixType = lua_tostring(mLuaState, -1);
							if (strcmp(tempMatrixType, "LocalToWorld")==0)
								uniforms[i - 1].matrixType = Engine::Graphics::LocalToWorld;
							else if (strcmp(tempMatrixType, "WorldToView")==0)
								uniforms[i - 1].matrixType = Engine::Graphics::WorldToView;
							else if (strcmp(tempMatrixType, "ViewToScreen")==0)
								uniforms[i - 1].matrixType = Engine::Graphics::ViewToScreen;
							else if (strcmp(tempMatrixType, "NormalMatrix") == 0)
								uniforms[i - 1].matrixType = Engine::Graphics::NormalMatrix;
							else if (strcmp(tempMatrixType, "ScaleMatrix") == 0)
								uniforms[i - 1].matrixType = Engine::Graphics::ScaleMatrix;
							lua_pop(mLuaState, 1);//Popping out matrixType
						}
					}

					//type Count
					{
						lua_pushstring(mLuaState, "count");
						lua_gettable(mLuaState, -2);
						uniforms[i - 1].valCount = static_cast<uint8_t>(lua_tonumber(mLuaState, -1));
						lua_pop(mLuaState, 1); //Popping "count"
					}

					lua_pop(mLuaState, 1);//Popping i
				}
			}
		}
	}

	lua_pop(mLuaState, 1);//Popping out "uniform"

	lua_pop(mLuaState, 1);//Popping out the whole table
	LuaHelper::exitAndShutdownLua(mLuaState);

#if _DEBUG
	//std::cerr << effectName.c_str()<<fragmentName.c_str()<<vertexName.c_str();
#endif

	return true;
}
