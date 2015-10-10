#include "Game.h"
#include "../../Engine/Core/Core.h"
#include <windows.h>
#include <fstream>
#include <crtdbg.h>

int WINAPI WinMain(HINSTANCE i_thisInstanceOfTheProgram,HINSTANCE,char* i_commandLineArguments,	int i_initialWindowDisplayState)
{
	{
		_CrtSetBreakAlloc(156);
		EngineCore::Initialize(i_thisInstanceOfTheProgram, i_initialWindowDisplayState);
		while (!EngineCore::isWindowClosed(i_thisInstanceOfTheProgram))
			EngineCore::onNewFrame();
		EngineCore::shutDownEngine();
	}
	_CrtDumpMemoryLeaks();
}