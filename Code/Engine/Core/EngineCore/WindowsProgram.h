/*
	This file contains all of the function declarations for this example program
*/

#ifndef __WINDOWSPROGRAM_H
#define __WINDOWSPROGRAM_H

// Header Files
//=============

#include <string>
#include "../../Windows/WindowsIncludes.h"
#include "../Utilities/SharedPointer.h"
#include "RTTI.h"

namespace Engine
{
	namespace WindowUtil
	{
		class WindowingSystem:public Engine::RTTI
		{
		public:
			static SharedPointer<WindowingSystem> getWindow();
			static HWND getMainWindow();
			bool CreateMainWindow(const HINSTANCE i_thisInstanceOfTheProgram, const int i_initialWindowDisplayState);
			static bool OnMainWindowClosed(const HINSTANCE i_thisInstanceOfTheProgram);
			bool isType(RTTI*) override;
		private:
			static WindowingSystem* mWindowingSystem;
			HWND s_mainWindow;
			const char* s_mainWindowClassName;
			HWND CreateMainWindowHandle(const HINSTANCE i_thisInstanceOfTheProgram, const int i_initialWindowDisplayState);
			ATOM RegisterMainWindowClass(const HINSTANCE i_thisInstanceOfTheProgram);
			static LRESULT CALLBACK OnMessageReceived(HWND i_window, UINT i_message, WPARAM i_wParam, LPARAM i_lParam);
			bool UnregisterMainWindowClass(const HINSTANCE i_thisInstanceOfTheProgram);
			bool CleanupMainWindow();
			WindowingSystem();
		};
	}
}


#endif	// __WINDOWSPROGRAM_H
