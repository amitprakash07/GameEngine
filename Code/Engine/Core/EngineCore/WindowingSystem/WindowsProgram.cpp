#include "WindowsProgram.h"
#include "Resources/Resource.h"
#include "../../../Windows/WindowsFunctions.h"
#include "../../MessagingSystem/MessagingSystem.h"
#include "../../StringPoolManager/StringPool.h"
#include "../EngineCore.h"
#include <iostream>


Engine::SharedPointer<Engine::Windows::WindowingSystem> Engine::Windows::WindowingSystem::mWindowingSystem;

Engine::SharedPointer<Engine::Windows::WindowingSystem> Engine::Windows::WindowingSystem::getWindowingSystem()
{
	if (mWindowingSystem.isNull())
	{
		SharedPointer<Engine::Windows::WindowingSystem> temp(new WindowingSystem(), "Engine::Windows::WindowingSystem");
		mWindowingSystem = temp;
	}
	return mWindowingSystem;
}

bool Engine::Windows::WindowingSystem::CreateMainWindow(const HINSTANCE i_thisInstanceOfTheProgram, const int i_initialWindowDisplayState)
{
	ATOM mainWindowClass = RegisterMainWindowClass(i_thisInstanceOfTheProgram);
	if (mainWindowClass != NULL)
	{
		s_mainWindow = CreateMainWindowHandle(i_thisInstanceOfTheProgram, i_initialWindowDisplayState);
		if (s_mainWindow == nullptr)
			return false;
		return true;
	}
	return false;
}

ATOM Engine::Windows::WindowingSystem::RegisterMainWindowClass(const HINSTANCE i_thisInstanceOfTheProgram)
{
	WNDCLASSEX wndClassEx = { 0 };
	wndClassEx.cbSize = sizeof(WNDCLASSEX);
	wndClassEx.hInstance = i_thisInstanceOfTheProgram;
#ifdef PLATFORM_D3D
	wndClassEx.style = 0;
#elif PLATFORM_OPEN_GL
	wndClassEx.style |= CS_OWNDC;
#endif
	wndClassEx.lpfnWndProc = OnMessageReceived;
	// Extra bytes can be set aside in the class for user data
	wndClassEx.cbClsExtra = 0;
	// Extra bytes can be set aside for each window of this class,
	// but this is usually specified for each window individually
	wndClassEx.cbWndExtra = 0;
	// The large and small icons that windows of this class should use
	// (These can be found in the Resources folder; feel free to change them)
	wndClassEx.hIcon = LoadIcon(i_thisInstanceOfTheProgram, MAKEINTRESOURCE(IDI_BIG));
	wndClassEx.hIconSm = LoadIcon(i_thisInstanceOfTheProgram, MAKEINTRESOURCE(IDI_SMALL));
	// The cursor that should display when the mouse pointer is over windows of this class
	wndClassEx.hCursor = LoadCursor(nullptr , IDC_ARROW);
	// The "brush" that windows of this class should use as a background
	// (Setting this is a bit confusing but not important,
	// so don't be alarmed if the next line looks scary)
	wndClassEx.hbrBackground = reinterpret_cast<HBRUSH>(IntToPtr(COLOR_BACKGROUND + 1));
	// A menu can be specified that all windows of this class would use by default,
	// but usually this is set for each window individually
	wndClassEx.lpszMenuName = nullptr;
	// The class name (see comments where this is initialized)
	wndClassEx.lpszClassName = s_mainWindowClassName;
	// Now all of the above information is given to Windows.
	// If all goes well, the class will be successfully registered
	// and it can be specified by name when creating the main window.
	const ATOM mainWindowClass = RegisterClassEx(&wndClassEx);
	if (mainWindowClass == NULL)
	{
		const char* errorCaption = "No Main Window Class";
		std::string errorMessage("Windows failed to register the main window's class: ");
		errorMessage += WindowsUtil::GetLastWindowsError();
		MessageBox(nullptr, errorMessage.c_str(), errorCaption, MB_OK | MB_ICONERROR);
	}
	return mainWindowClass;
}

HWND Engine::Windows::WindowingSystem::CreateMainWindowHandle( const HINSTANCE i_thisInstanceOfTheProgram, const int i_initialWindowDisplayState )
{
	// Create the main window
	HWND mainWindow;
	{
		// The window's "caption"
		// (The text that is displayed in the title bar)
		std::string windowCaptionString = "Amit Prakash's - WindowsUtil Game";
		//char* windowCaption = "Amit Prakash's - WindowsUtil Game";
		std::string platform;
#ifdef PLATFORM_D3D
		platform = " --DirectX";
#elif PLATFORM_OPEN_GL
		platform = " --OpenGL";
#endif
		windowCaptionString.append(platform);
		//strcat(windowCaption, platform);
		// The window's style
		const DWORD windowStyle =
			// "Overlapped" is basically the same as "top-level"
			WS_OVERLAPPED
			// The caption is the title bar when in windowed-mode
			| WS_CAPTION
			// The window should never change dimensions, so only a minimize box is allowed
			| WS_MINIMIZEBOX
			// The system menu appears when you right-click the title bar
			| WS_SYSMENU;
		// The window's extended style
		const DWORD windowStyle_extended =
			// The following is a macro to make the extended style the default top-level look
			WS_EX_OVERLAPPEDWINDOW;
		// The width and height of the window.
		// A game cares about the width and height of the actual "client area",
		// which is the part of the window that doesn't include the borders and title bar;
		// this means that if we say that a game runs at a resolution of 800 x 600,
		// the actual window will be slightly bigger than that.
		// Initially, then, the window will be created with default values that Windows chooses
		// and then resized after creation)
		const int width = CW_USEDEFAULT;
		const int height = CW_USEDEFAULT;
		// The initial position of the window
		// (We don't care, and will let Windows decide)
		const int position_x = CW_USEDEFAULT;
		const int position_y = CW_USEDEFAULT;
		// Handle to the parent of this window
		// (Since this is our main window, it can't have a parent)
		const HWND hParent = nullptr;
		// Handle to the menu for this window
		// (The main window won't have a menu)
		const HMENU hMenu = nullptr;
		// Handle to the instance of the program that this window should be associated with
		const HINSTANCE hProgram = i_thisInstanceOfTheProgram;
		// Any arbitrary pointer can be associated with this window;
		// usually a program's own custom representation of the window will be used, like this:
		// void* userData = someCustomStructOrClass;
		// Since this example program is simple, though, no data will be associated:
		void* userData = nullptr;
		// Ask Windows to create the specified window.
		// CreateWindowEx() will return a handle to the window,
		// which is what we'll use to communicate with Windows about this window
		mainWindow = CreateWindowEx( windowStyle_extended, s_mainWindowClassName, windowCaptionString.c_str(), windowStyle,
			position_x, position_y, width, height,
			hParent, hMenu, hProgram, userData );
		if ( mainWindow == nullptr )
		{
			const char* errorCaption = "No Main Window";
			std::string errorMessage( "Windows failed to create the main window: " );
			errorMessage += WindowsUtil::GetLastWindowsError();
			MessageBox( nullptr, errorMessage.c_str(), errorCaption, MB_OK | MB_ICONERROR );
			return nullptr;
		}
	}

	// Change the window's size based on the desired client area resolution
	{
		// In a real game these values would come from an external source
		// rather than be hard-coded
		const int desiredWidth = 1600;
		const int desiredHeight = 900;

		// Calculate how much of the window is coming from the "non-client area"
		// (the borders and title bar)
		RECT windowCoordinates;
		struct
		{
			long width;
			long height;
		} nonClientAreaSize;
		{
			// Get the coordinates of the entire window
			if ( GetWindowRect( mainWindow, &windowCoordinates ) == FALSE )
			{
				std::string errorMessage( "Windows failed to get the coordinates of the main window: " );
				errorMessage += WindowsUtil::GetLastWindowsError();
				MessageBox(nullptr, errorMessage.c_str(), nullptr, MB_OK | MB_ICONERROR );
				return nullptr;
			}
			// Get the dimensions of the client area
			RECT clientDimensions;
			if ( GetClientRect( mainWindow, &clientDimensions ) == FALSE )
			{
				std::string errorMessage( "Windows failed to get the dimensions of the main window's client area: " );
				errorMessage += WindowsUtil::GetLastWindowsError();
				MessageBox(nullptr, errorMessage.c_str(), nullptr, MB_OK | MB_ICONERROR );
				return nullptr;
			}
			// Get the difference between them
			nonClientAreaSize.width = ( windowCoordinates.right - windowCoordinates.left ) - clientDimensions.right;
			nonClientAreaSize.height = ( windowCoordinates.bottom - windowCoordinates.top ) - clientDimensions.bottom;
		}
		// Resize the window
		{
			BOOL shouldTheResizedWindowBeRedrawn = TRUE;
			if ( MoveWindow( mainWindow, windowCoordinates.left, windowCoordinates.top,
				desiredWidth + nonClientAreaSize.width, desiredHeight + nonClientAreaSize.height,
				shouldTheResizedWindowBeRedrawn ) == FALSE )
			{
				std::string errorMessage( "Windows failed to resize the main window: " );
				errorMessage += WindowsUtil::GetLastWindowsError();
				MessageBox(nullptr, errorMessage.c_str(), nullptr, MB_OK | MB_ICONERROR );
				return nullptr;
			}
		}
	}

	// Display the window in the initial state that Windows requested
	ShowWindow( mainWindow, i_initialWindowDisplayState );
	return mainWindow;
}

LRESULT CALLBACK Engine::Windows::WindowingSystem::OnMessageReceived(HWND i_window, UINT i_message, WPARAM i_wParam, LPARAM i_lParam)
{
	switch (i_message)
	{
	case WM_CHAR:
	{
		// This isn't usually the best way to handle keyboard input in a real-time game,
		// but it is a convenient way to handle an exit key
		// (The WPARAM input parameter indicates which key was pressed,
		// but this example program only cares about the escape key)
		//if (i_wParam == VK_ESCAPE)
		//{
		//	// You do _not_ need to do this in your game,
		//	// but this example program shows you how to display a "message box"
		//	// that asks the user for confirmation
		//	int result;
		//	{
		//		const char* caption = "Exit Program?";
		//		const char* message = "Are you sure you want to quit?";
		//		result = MessageBox(s_mainWindow, message, caption, MB_YESNO | MB_ICONQUESTION);
		//	}
		//	if (result == IDYES)
		//	{
		//		// Instruct Windows to send a WM_QUIT message
		//		{
		//			// The exit code is ignored,
		//			// but just as an example of what's possible a different exit code is sent here
		//			// than when the user closes the program in the usual way
		//			// (by clicking the X in the upper-right hand corner).
		//			/*int exitCode = 0;
		//			PostQuitMessage(exitCode);*/
		//			SendMessage(i_window, WM_NCDESTROY, i_wParam, i_lParam);
		//		}
		//		// For WM_CHAR messages, return 0 to indicate that it was processed
		//		return 0;
		//	}
		//	else
		//	{
		//		// If the user doesn't select "Yes" to quit
		//		// then do nothing to keep running the program
		//	}

		//}
		// If the key press wasn't handled pass it on to Windows to process in the default way
		Engine::utils::StringHash temp = Engine::EngineCore::getStringPool()->findString("KeyDown");
		SharedPointer<WindowingSystem> tempWindowingSystem = Engine::EngineCore::getWindowingSystem();
		Engine::EngineCore::getMessagingSystem()->sendMessage(temp, reinterpret_cast<IMessageHandler*>(tempWindowingSystem.getRawPointer()), reinterpret_cast<void*>(i_wParam));
		break;
	}
	case WM_KEYDOWN:
	{
		Engine::utils::StringHash temp = Engine::EngineCore::getStringPool()->findString("KeyDown");
		SharedPointer<WindowingSystem> tempWindowingSystem = Engine::EngineCore::getWindowingSystem();
		Engine::EngineCore::getMessagingSystem()->sendMessage(temp, reinterpret_cast<IMessageHandler*>(tempWindowingSystem.getRawPointer()), reinterpret_cast<void*>(i_wParam));
		break;
	}
	case WM_LBUTTONDOWN:
	{
		Engine::utils::StringHash temp = Engine::EngineCore::getStringPool()->findString("MouseEvent");
		SharedPointer<Engine::MouseController> tempMouseController = Engine::EngineCore::getMouseInputController();
		WindowsParam windowsParameter;
		windowsParameter.windowsMessage = i_message;
		windowsParameter.wParam = i_wParam;
		windowsParameter.lParam = i_lParam;
		Engine::EngineCore::getMessagingSystem()->sendMessage(temp,
			reinterpret_cast<IMessageHandler*>(tempMouseController.getRawPointer()),
			reinterpret_cast<void*>(&windowsParameter));
		break;
	}
	case WM_MOUSEMOVE:
	{
		Engine::utils::StringHash temp = Engine::EngineCore::getStringPool()->findString("MouseEvent");
		SharedPointer<Engine::MouseController> tempMouseController = Engine::EngineCore::getMouseInputController();
		WindowsParam windowsParameter;
		windowsParameter.windowsMessage = i_message;
		windowsParameter.wParam = i_wParam;
		windowsParameter.lParam = i_lParam;
		Engine::EngineCore::getMessagingSystem()->sendMessage(temp,
			reinterpret_cast<IMessageHandler*>(tempMouseController.getRawPointer()),
			reinterpret_cast<void*>(&windowsParameter));
		break;
	}
	case WM_LBUTTONUP:
	{
		Engine::utils::StringHash temp = Engine::EngineCore::getStringPool()->findString("MouseEvent");
		SharedPointer<Engine::MouseController> tempMouseController = Engine::EngineCore::getMouseInputController();
		WindowsParam windowsParameter;
		windowsParameter.windowsMessage = i_message;
		windowsParameter.wParam = i_wParam;
		windowsParameter.lParam = i_lParam;
		Engine::EngineCore::getMessagingSystem()->sendMessage(temp,
			reinterpret_cast<IMessageHandler*>(tempMouseController.getRawPointer()),
			reinterpret_cast<void*>(&windowsParameter));
		break;
	}
	
	// The window's nonclient area is being destroyed
	case WM_NCDESTROY:
	{
		//mWindowingSystem->s_mainWindow = nullptr;
		// When the main window is destroyed
		// a WM_QUIT message should be sent
		// (if this isn't done the application would continue to run with no window).
		// This is where the exitCode in WaitForShutdown() comes from:
		//mWindowingSystem->s_mainWindow = nullptr;
		EngineCore::getWindowingSystem()->s_mainWindow = nullptr;
		int exitCode = 0;			// Arbitrary de facto success code
		PostQuitMessage(exitCode);	// This sends a WM_QUIT message
									// For WM_NCDESTROY messages, return 0 to indicate that it was processed
		
		return 0;
	}
	}//Switch 
	// Pass any messages that weren't handled on to Windows
	return DefWindowProc(i_window, i_message, i_wParam, i_lParam);
}

bool Engine::Windows::WindowingSystem::UnregisterMainWindowClass(const HINSTANCE i_thisInstanceOfTheProgram)
{
	if (UnregisterClass(s_mainWindowClassName, i_thisInstanceOfTheProgram) != FALSE)
		return true;
	else
	{
		const char* errorCaption = "Couldn't Unregister Main Window Class";
		std::string errorMessage("Windows failed to unregister the main window's class: ");
		errorMessage += WindowsUtil::GetLastWindowsError();
		MessageBox(nullptr, errorMessage.c_str(), errorCaption, MB_OK | MB_ICONERROR);
		return false;
	}
}

HWND Engine::Windows::WindowingSystem::getMainWindow()
{
	if (s_mainWindow)
		return s_mainWindow;
	return nullptr;
}

bool Engine::Windows::WindowingSystem::CleanupMainWindow()
{
	if ( s_mainWindow != nullptr )
	{
		if ( DestroyWindow( s_mainWindow ) != FALSE )
		{
			s_mainWindow = nullptr;
		}
		else
		{
			const char* errorCaption = "Couldn't Destroy Main Window";
			std::string errorMessage( "Windows failed to destroy the main window: " );
			errorMessage += WindowsUtil::GetLastWindowsError();
			MessageBox( nullptr, errorMessage.c_str(), errorCaption, MB_OK | MB_ICONERROR );
			return false;
		}
	}
	return true;
}

bool Engine::Windows::WindowingSystem::OnMainWindowClosed( const HINSTANCE i_thisInstanceOfTheProgram )
{
	bool wereThereErrors = false;
	if ( !EngineCore::getWindowingSystem()->CleanupMainWindow() )
		wereThereErrors = true;
	if ( !EngineCore::getWindowingSystem()->UnregisterMainWindowClass( i_thisInstanceOfTheProgram ) )
		wereThereErrors = true;
	
	return !wereThereErrors;
}

Engine::Windows::WindowingSystem::WindowingSystem()
{
	s_mainWindow = nullptr;
	s_mainWindowClassName = "Amit Prakash - Main Window Class";
}

Engine::Windows::WindowingSystem::~WindowingSystem()
{
	/*std::cout << "Something";
	s_mainWindow = nullptr;*/
}

bool Engine::Windows::WindowingSystem::isBothSameType(RTTI*, std::string)
{
	return true;
}

std::string Engine::Windows::WindowingSystem::getTypeInfo()
{
	return "";
}












