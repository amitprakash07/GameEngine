/*
	This file contains all of the function declarations for this example program
*/

#ifndef __WINDOWSPROGRAM_H
#define __WINDOWSPROGRAM_H

// Header Files
//=============

#include <string>
#include "../../Engine/Windows/WindowsIncludes.h"


namespace Engine
{
	namespace WindowUtil
	{
		class WindowingSystem
		{
		public:
			static bool CreateMainWindow(const HINSTANCE i_thisInstanceOfTheProgram, const int i_initialWindowDisplayState);
			static HWND getMainWindow();
			static bool OnMainWindowClosed(const HINSTANCE i_thisInstanceOfTheProgram);
		private:
			static HWND s_mainWindow;
			static const char* s_mainWindowClassName; 
			static HWND CreateMainWindowHandle(const HINSTANCE i_thisInstanceOfTheProgram, const int i_initialWindowDisplayState);
			static ATOM RegisterMainWindowClass(const HINSTANCE i_thisInstanceOfTheProgram);
			static LRESULT CALLBACK OnMessageReceived(HWND i_window, UINT i_message, WPARAM i_wParam, LPARAM i_lParam);
			static bool UnregisterMainWindowClass(const HINSTANCE i_thisInstanceOfTheProgram);
			static bool CleanupMainWindow();
		};
	}
}


#endif	// __WINDOWSPROGRAM_H
