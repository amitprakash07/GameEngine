#include "Game.h"
#include "../../Engine/Core/Core.h"
#include <windows.h>
#include <fstream>

int WINAPI WinMain(HINSTANCE i_thisInstanceOfTheProgram,HINSTANCE,char* i_commandLineArguments,	int i_initialWindowDisplayState)
{
	std::ifstream readFile("yay", std::ifstream::binary);
	readFile.close();
	EngineCore::Initialize(i_thisInstanceOfTheProgram, i_initialWindowDisplayState);
	while(!EngineCore::isWindowClosed())
		EngineCore::onNewFrame();
}