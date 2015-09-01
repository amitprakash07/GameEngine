#include "Game.h"
#include "../../Engine/Core/Core.h"
#include <windows.h>


int WINAPI WinMain(HINSTANCE i_thisInstanceOfTheProgram,HINSTANCE,char* i_commandLineArguments,	int i_initialWindowDisplayState)
{
	EngineCore::Initialize(i_thisInstanceOfTheProgram, i_initialWindowDisplayState);
	while(!EngineCore::isWindowClosed())
		EngineCore::onNewFrame();
}