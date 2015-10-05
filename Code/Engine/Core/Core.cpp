
#include "Core.h"
#include "..\Windows\WindowsProgram.h"
#include "..\Graphics\Graphics.h"
#include "..\Graphics\Scene.h"
#include "..\Windows\WindowsFunctions.h"
#include "..\Graphics\Effects.h"

namespace EngineCore
{	
	HWND s_mainWindow;

	void Initialize(HINSTANCE hInstance, int windowLayout)
	{
		std::stringstream errormessage;
		CreateMainWindow(hInstance, windowLayout, s_mainWindow);
		if (Engine::Graphics::GraphicsSystem::Initialize(s_mainWindow))
		{
			if (!Engine::Graphics::Effects::addEffect("data/standard.vshd", "data/standard.fshd"))
			{
				errormessage << "Unable to set the shader effets";
				WindowsUtil::Print(errormessage.str());
				exit(0);
			}

			if (!Engine::Graphics::Scene::addToScene("data/SquareMesh.mesh"))
			{
				errormessage << "Unable to add the Mesh";
				WindowsUtil::Print(errormessage.str());
				exit(0);
			}
			if (!Engine::Graphics::Scene::addToScene("data/TriangleMesh.mesh"))
			{
				errormessage << "Unable to add the Mesh";
				WindowsUtil::Print(errormessage.str());
				exit(0);
			}
		}
	}

	void onNewFrame()
	{
		MSG message = {};
		bool hasWindowsSentAMessage;
		
		
		{
			HWND getMessagesFromAnyWindowBelongingToTheCurrentThread = nullptr;
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