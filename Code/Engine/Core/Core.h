#pragma once
#ifndef __CORE_H
#define __CORE_H

#include "../Windows/WindowsIncludes.h"

namespace EngineCore
{
	void Initialize(HINSTANCE hInstance, int windowLayout);
	void onNewFrame();
	bool isWindowClosed(HINSTANCE hInstance);
	void shutDownEngine();
}

#endif
