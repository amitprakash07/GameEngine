#pragma once
#ifndef __CORE_H
#define __CORE_H

#include "../Windows/WindowsIncludes.h"
#include "MessagingSystem/MessagingSystem.h"
#include "Time/FrameTime.h"
#include "Utilities/SharedPointer.h"
#include "Utilities/StringPool.h"

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
		static SharedPointer<Engine::Time::FrameTime> getFrameTimeController();
		static SharedPointer<Engine::StringPool> getStringPool();
	};
	
}

#endif
