// Header Files
//=============

#include "../cShaderBuilder.h"
#include <sstream>
#include "../../../Engine/Windows/WindowsFunctions.h"
#include <iostream>
#include "../../../Engine/Graphics/uniformdefs.h"


// Interface
//==========

// Build
//------

bool Tools::AssetBuilder::cShaderBuilder::Build(const std::vector<std::string>& i_arguments)
{
	// Decide which kind of shader program to compile
	std::stringstream errorMessage;
	Engine::Graphics::ShaderType shaderType = Engine::Graphics::ShaderType::Unknown;
	{
		if (i_arguments.size() >= 1)
		{

			const std::string& argument = i_arguments[0];

			if (argument == "vertex")
			{
				shaderType = Engine::Graphics::ShaderType::Vertex;
			}
			else if (argument == "fragment")
			{
				shaderType = Engine::Graphics::ShaderType::Fragment;
			}
			else
			{
				errorMessage << "\"" << argument << "\" is not a valid shader program type " << m_path_source;
				WindowsUtil::Print(errorMessage.str().c_str());
				return false;
			}
		}
		else
		{
			errorMessage << "A Shader must be built with an argument defining which "
				<< "type of shader program (e.g. \"vertex\" or \"fragment\") to compile " << m_path_source;
			WindowsUtil::Print(errorMessage.str().c_str());
			return false;
		}
	}
	// Get the path to the shader compiler
	std::string path_fxc;
	{
		// Get the path to the DirectX SDK
		std::string path_sdk;
		{
			std::string othererrormessage;
			if (!WindowsUtil::GetVSEnvironmentVariable("DXSDK_DIR", path_sdk, &othererrormessage))
			{
				std::stringstream decoratedErrorMessage;
				decoratedErrorMessage << "Windows failed to get the path to the DirectX SDK: " << othererrormessage << __FILE__;
				WindowsUtil::Print(decoratedErrorMessage.str().c_str());
				return false;
			}
		}
		path_fxc = path_sdk + "Utilities/bin/" +
#ifndef _WIN64
			"x86"
#else
			"x64"
#endif
			+ "/fxc.exe";
	}
	// Create the command to run
	std::string command;
	{
		std::stringstream commandToBuild;
		commandToBuild << "\"" << path_fxc << "\"";
		// Target profile
		switch (shaderType)
		{
		case Engine::Graphics::ShaderType::Vertex:
			commandToBuild << " /Tvs_3_0";
			break;
		case Engine::Graphics::ShaderType::Fragment:
			commandToBuild << " /Tps_3_0";
			break;
		default:
			break;
		}
		// Entry point
		commandToBuild << " /Emain"
			// #define the platform
			<< " /DPLATFORM_D3D"
#ifdef EAE6320_GRAPHICS_AREDEBUGSHADERSENABLED
			// Disable optimizations so that debugging is easier
			<< " /Od"
			// Enable debugging
			<< " /Zi"
#endif
			// Target file
			<< " /Fo\"" << m_path_target << "\""
			// Don't output the logo
			<< " /nologo"
			// Source file
			<< " \"" << m_path_source << "\""
			;
		command = commandToBuild.str();

	}

	//std::cerr << "\nCommand for the compilation of the shader" << command;
	std::cerr << "\nPrint Shader Code\n" << command.c_str();
	// Execute the command
	{
		DWORD exitCode;
		std::string othererrorMessage;
		if (WindowsUtil::ExecuteCommand(command.c_str(), &exitCode, &othererrorMessage))
		{
			return exitCode == EXIT_SUCCESS;
		}
		else
		{
			errorMessage << othererrorMessage << m_path_source;
			WindowsUtil::Print(errorMessage.str().c_str());
			return false;
		}
	}
}
