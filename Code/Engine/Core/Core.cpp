
#include "Core.h"
#include "..\Windows\WindowsProgram.h"
#include "..\Graphics\Graphics.h"
#include "..\Graphics\Mesh.h"
#include <sstream>
#include "..\Windows/WindowsFunctions.h"


namespace EngineCore
{	
	HWND s_mainWindow;

	void Initialize(HINSTANCE hInstance, int windowLayout)
	{
		CreateMainWindow(hInstance, windowLayout, s_mainWindow);
		if (!Engine::Graphics::Mesh::LoadMesh())
		{
			std::stringstream errorMessage;
			errorMessage<< "There is something went wrong while reading mesh data file - either file not found or bad data";
			WindowsUtil::Print(errorMessage.str());
			exit(0);
		}
		Engine::Graphics::GraphicsSystem::Initialize(s_mainWindow);
	}

	void onNewFrame()
	{
		MSG message = {};
		bool hasWindowsSentAMessage;
		
		
		{
			HWND getMessagesFromAnyWindowBelongingToTheCurrentThread = NULL;
			unsigned int getAllMessageTypes = 0;
			unsigned int ifAMessageExistsRemoveItFromTheQueue = PM_REMOVE;
			hasWindowsSentAMessage = PeekMessage(&message, getMessagesFromAnyWindowBelongingToTheCurrentThread,
				getAllMessageTypes, getAllMessageTypes, ifAMessageExistsRemoveItFromTheQueue) == TRUE;
		}

		if(!hasWindowsSentAMessage)
		{
			Engine::Graphics::GraphicsSystem::Render();
		}
		else
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

	}

	bool isWindowClosed()
	{
		return (s_mainWindow == NULL ? true : false);
	}

}