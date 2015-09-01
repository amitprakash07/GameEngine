/*
	This file contains all of the function declarations for this example program
*/

#ifndef EAE6320_WINDOWSPROGRAM_H
#define EAE6320_WINDOWSPROGRAM_H

// Header Files
//=============

#include <string>
#include "../../Engine/Windows/WindowsIncludes.h"

//namespace
//{
//	//	// Instead of a pointer Windows provides a "handle"
//	//	// to represent each window that is created
//	//	// ("HWND" == "window handle").
//	//	// In Windows every separate element
//	//	// (buttons, text fields, scroll bars, etc.) is a "window",
//	//	// and so a typical Windows program will have many different windows.
//	//	// In our class, however, we will only have a single main window.
//	HWND s_mainWindow;
//	//HWND getWindow() { return s_mainWindow; }
//	//
//	//	// Window classes are almost always identified by name;
//	//	// there is also a unique ATOM associated with them,
//	//	// but in practice Windows expects to use the class name as an identifier.
//	//	// If you don't change the name below from the default then
//	//	// your program could have problems when it is run at the same time on the same computer
//	//	// as one of your classmate's
//	const char* s_mainWindowClass_name;
//}


// Main Function
//==============

int CreateMainWindowAndReturnExitCodeWhenItCloses( const HINSTANCE i_thisInstanceOfTheProgram, const int i_initialWindowDisplayState );

// Helper Functions
//=================

// There are two things that have to happen:
//	* The main window must be created
//		(this will happen quickly)
//	* The main window must run until it gets closed
//		(this is up to the user)
//HWND getWindow();

bool CreateMainWindow( const HINSTANCE i_thisInstanceOfTheProgram, const int i_initialWindowDisplayState);
bool CreateMainWindow(const HINSTANCE i_thisInstanceOfTheProgram, const int i_initialWindowDisplayState, HWND &);
int WaitForMainWindowToCloseAndReturnExitCode( const HINSTANCE i_thisInstanceOfTheProgram );

// CreateMainWindow
//-----------------

HWND CreateMainWindowHandle( const HINSTANCE i_thisInstanceOfTheProgram, const int i_initialWindowDisplayState );
ATOM RegisterMainWindowClass( const HINSTANCE i_thisInstanceOfTheProgram );

// WaitForMainWindowToCloseAndReturnExitCode
//------------------------------------------

bool CleanupMainWindow();
bool OnMainWindowClosed( const HINSTANCE i_thisInstanceOfTheProgram );
LRESULT CALLBACK OnMessageReceived( HWND i_window, UINT i_message, WPARAM i_wParam, LPARAM i_lParam );
bool UnregisterMainWindowClass( const HINSTANCE i_thisInstanceOfTheProgram );
bool WaitForMainWindowToClose( int& o_exitCode );

#endif	// EAE6320_WINDOWSPROGRAM_H
