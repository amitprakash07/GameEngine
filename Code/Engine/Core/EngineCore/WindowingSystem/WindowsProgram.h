/*
This file contains all of the function declarations for this example program
*/

#ifndef __WINDOWSPROGRAM_H
#define __WINDOWSPROGRAM_H

// Header Files
//=============

#include <string>
#include "../../../Windows/WindowsIncludes.h"
#include "../../Utilities/SharedPointer.h"
#include "../../Utilities/RTTI.h"

namespace Engine
{
	namespace Windows
	{
		class WindowingSystem : public Engine::RTTI
		{
		public:
			static SharedPointer<WindowingSystem> getWindowingSystem(bool fullScreen = false, int width = 1600, int height = 900);
			HWND getMainWindow();
			bool CreateMainWindow(const HINSTANCE i_thisInstanceOfTheProgram, const int i_initialWindowDisplayState);
			static bool OnMainWindowClosed(const HINSTANCE i_thisInstanceOfTheProgram);
			std::string getTypeInfo() const override;
			bool isBothSameType(RTTI*, std::string) const override;
			int getWindowHeight() const;
			int getWindowWidth() const;
			~WindowingSystem();
		private:
			static SharedPointer<WindowingSystem> mWindowingSystem;
			int width;
			int height;
			HWND s_mainWindow;
			const char* s_mainWindowClassName;
			HWND CreateMainWindowHandle(const HINSTANCE i_thisInstanceOfTheProgram, const int i_initialWindowDisplayState);
			ATOM RegisterMainWindowClass(const HINSTANCE i_thisInstanceOfTheProgram);
			static LRESULT CALLBACK OnMessageReceived(HWND i_window, UINT i_message, WPARAM i_wParam, LPARAM i_lParam);
			bool UnregisterMainWindowClass(const HINSTANCE i_thisInstanceOfTheProgram);
			bool CleanupMainWindow();
			WindowingSystem();
			void AssignFullResolutionWindow();
		};
	}
}


#endif	// __WINDOWSPROGRAM_H
