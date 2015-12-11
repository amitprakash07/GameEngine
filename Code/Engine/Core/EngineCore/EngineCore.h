#pragma once
#ifndef __CORE_H
#define __CORE_H

#include "WindowingSystem/WindowsProgram.h"
#include "../StringPoolManager/StringPool.h"
#include "../MessagingSystem/MessagingSystem.h"
#include "InputController/InputController.h"
#include "../Utilities/SharedPointer.h"


namespace Engine
{
	class EngineCore
	{
	public:
		static void Initialize(HINSTANCE hInstance, int windowLayout);
		static void onNewFrame();
		static bool isWindowClosed(HINSTANCE hInstance);
		static void shutDownEngine();
		static SharedPointer<Engine::MessagingSystem> getMessagingSystem();
		static SharedPointer<Engine::StringPool> getStringPool();
		static SharedPointer<Engine::Windows::WindowingSystem> getWindowingSystem();
		static SharedPointer<Engine::InputController> getInputController();
		static std::string getMeshFolderPath();
		static std::string getMaterialFolderPath();
		static std::string getEffectFolderPath();
		static std::string getShaderFolderPath();
		static std::string getTextureFolderPath();
	private:
		EngineCore();
		//static SharedPointer<EngineCore> mEngineInstance;
		static SharedPointer<Engine::MessagingSystem> mMessagingSystem;
		static SharedPointer<Engine::StringPool> mStringPool;
		static SharedPointer<Engine::Windows::WindowingSystem> mEngineWindowingSystem;
		static SharedPointer<Engine::InputController> mInputController;
		static std::string materialFolderPath;
		static std::string shaderFolderName;
		static std::string effectFolderName;
		static std::string meshFolderName;
		static std::string textureFolderName;
	};
}

#endif
