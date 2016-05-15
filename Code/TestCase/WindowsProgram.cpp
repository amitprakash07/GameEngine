/*
	This file contains all of the function definitions for this example program
*/

// Header Files
//=============
#include "../../Engine/UserInput/UserInput.h"
#include "../../Engine/Time/Time.h"
#include "WindowsProgram.h"
#include "../../Engine/Graphics/Camera.h"
#include "..\..\Engine\Graphics\Graphics.h"
#include "..\..\Engine\Windows\WindowsFunctions.h"
#include "../../Engine/Math/cQuaternion.h"
#include "../../Engine/Math/cVector.h"
// Resource.h contains the #defines for the icon resources
// that the main window will use
#include "Resources/Resource.h"
// WindowsFunctions.h contains convenience functionality for Windows features;
// in this example program we just use it to get error messages
#include "..\..\Engine\Windows\WindowsIncludes.h"

// Static Data Initialization
//===========================

namespace
{
	// Instead of a pointer Windows provides a "handle"
	// to represent each window that is created
	// ("HWND" == "window handle").
	// In Windows every separate element
	// (buttons, text fields, scroll bars, etc.) is a "window",
	// and so a typical Windows program will have many different windows.
	// In our class, however, we will only have a single main window.
	HWND s_mainWindow = NULL;

	// Window classes are almost always identified by name;
	// there is also a unique ATOM associated with them,
	// but in practice Windows expects to use the class name as an identifier.
	// If you don't change the name below from the default then
	// your program could have problems when it is run at the same time on the same computer
	// as one of your classmate's
	const char* s_mainWindowClass_name = "[Yash]'s Main Window Class";
}

// Main Function
//==============

void ThirdPersonMovement(eae6320::Graphics::GameObject* player, eae6320::Math::cVector posOffset, eae6320::Math::cVector rotOffset, eae6320::Math::cVector thirdPersonOffset)
{
	// Rotating Player
	player->m_orientation = player->m_orientation *
		eae6320::Math::cQuaternion(rotOffset.y, eae6320::Math::cVector(0.0f, 1.0f, 0.0f));

	// Updating player's position
	eae6320::Math::cVector oldSnowmanPos = player->m_position;
	eae6320::Math::cMatrix_transformation i_localToWorldTransformSnowman = eae6320::Math::cMatrix_transformation(
		Camera::getInstance().camear_rotation, player->m_position);
	eae6320::Math::cVector newSnowmanPos = eae6320::Math::cMatrix_transformation::matrixMulVector(i_localToWorldTransformSnowman, posOffset);
	player->m_position = newSnowmanPos;

	// Updating third person camera according to the player's position
	eae6320::Math::cVector camOffset =Camera::getInstance().offset;
	eae6320::Math::cVector val = eae6320::Math::cMatrix_transformation::matrixMulVector(i_localToWorldTransformSnowman, camOffset);
	Camera::getInstance().camera_axis += (val - Camera::getInstance().camera_axis) * eae6320::Time::GetSecondsElapsedThisFrame() * 3;
	Camera::getInstance().camear_rotation = player->m_orientation *
		eae6320::Math::cQuaternion(rotOffset.y, eae6320::Math::cVector(0.0f, 1.0f, 0.0f));

	// Temporarily moving third person camera left/right
	eae6320::Math::cMatrix_transformation i_localToWorldTransformCamera = eae6320::Math::cMatrix_transformation(
		Camera::getInstance().camear_rotation,Camera::getInstance().camera_axis);
	Camera::getInstance().camera_axis = eae6320::Math::cMatrix_transformation::matrixMulVector(i_localToWorldTransformCamera, thirdPersonOffset);

	// Updating debug line for the player
	oldSnowmanPos.y += 0;
	newSnowmanPos.y = oldSnowmanPos.y;
	if (!(newSnowmanPos == oldSnowmanPos))
	{
		eae6320::Math::cVector directionVector = (newSnowmanPos - oldSnowmanPos);
		directionVector.Normalize();
		//eae6320::Graphics::s_snowmanLine->m_startPoint = newSnowmanPos;
		//eae6320::Graphics::s_snowmanLine->m_endPoint = newSnowmanPos + (directionVector * 100);
		//eae6320::Graphics::s_snowmanLine->LoadDebugLine();
		eae6320::Graphics::LoadDebugLine(newSnowmanPos, newSnowmanPos + (directionVector * 100), eae6320::Math::cVector(1, 0, 0));
	}
	else
	{
		//eae6320::Graphics::s_snowmanLine->m_startPoint = eae6320::Graphics::s_snowmanLine->m_endPoint = oldSnowmanPos;
		//eae6320::Graphics::s_snowmanLine->LoadDebugLine();
		eae6320::Graphics::LoadDebugLine(oldSnowmanPos, oldSnowmanPos , eae6320::Math::cVector(1, 0, 0));

	}
}
int CreateMainWindowAndReturnExitCodeWhenItCloses( const HINSTANCE i_thisInstanceOfTheProgram, const int i_initialWindowDisplayState )
{
	// Try to create the main window
	if ( CreateMainWindow( i_thisInstanceOfTheProgram, i_initialWindowDisplayState ) )
	{
		// If the main window was successfully created wait for it to be closed
		const int exitCode = WaitForMainWindowToCloseAndReturnExitCode( i_thisInstanceOfTheProgram );
		return exitCode;
	}
	else
	{
		// If the main window wasn't created return a made-up error code
		return -1;
	}
}

// Helper Functions
//=================

bool CreateMainWindow( const HINSTANCE i_thisInstanceOfTheProgram, const int i_initialWindowDisplayState )
{
	// Every window that Windows creates must belong to a "class".
	// Note that this is different than a C++ class (but similar in theory):
	// A windows class defines things that will be the same for every window
	// that belongs to the class.
	// (In other words, every window will have exactly one class,
	// but a windows class can have many windows.)
	// To create a new windows class it must be "registered" with Windows.
	ATOM mainWindowClass = RegisterMainWindowClass( i_thisInstanceOfTheProgram );
	if ( mainWindowClass != NULL )
	{
		s_mainWindow = CreateMainWindowHandle( i_thisInstanceOfTheProgram, i_initialWindowDisplayState );
		if ( s_mainWindow == NULL )
		{
			goto OnError;
		}
		eae6320::Graphics::Initialize(s_mainWindow);
		return true;

OnError:

		// Unregister the main window class
		{
			UnregisterMainWindowClass( i_thisInstanceOfTheProgram );
			mainWindowClass = NULL;
		}

		return false;
	}
	else
	{
		return false;
	}
}

int WaitForMainWindowToCloseAndReturnExitCode( const HINSTANCE i_thisInstanceOfTheProgram )
{
	// Wait for the main window to close
	int exitCode;
	bool wereThereErrors = WaitForMainWindowToClose( exitCode );

	// Clean up anything that was created/registered/initialized
	if ( OnMainWindowClosed( i_thisInstanceOfTheProgram ) )
	{
		return exitCode;
	}
	else
	{
		if ( wereThereErrors )
		{
			// If the program already had errors while waiting for the main window to close
			// the existing error exit code can be returned
			return exitCode;
		}
		else
		{
			// In a real program you might decide to define a special constant for this situation,
			// but for this example program -1 is a good arbitrary error code
			return -1;
		}
	}
}

// CreateMainWindow

//-----------------

HWND CreateMainWindowHandle( const HINSTANCE i_thisInstanceOfTheProgram, const int i_initialWindowDisplayState )
{
	// Create the main window
	HWND mainWindow;
	{
		// The window's "caption"
		// (The text that is displayed in the title bar)
		const char* windowCaption = "[Yash]'s EAE6320 Game";
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
		const HWND hParent = NULL;
		// Handle to the menu for this window
		// (The main window won't have a menu)
		const HMENU hMenu = NULL;
		// Handle to the instance of the program that this window should be associated with
		const HINSTANCE hProgram = i_thisInstanceOfTheProgram;
		// Any arbitrary pointer can be associated with this window;
		// usually a program's own custom representation of the window will be used, like this:
		// void* userData = someCustomStructOrClass;
		// Since this example program is simple, though, no data will be associated:
		void* userData = NULL;

		// Ask Windows to create the specified window.
		// CreateWindowEx() will return a handle to the window,
		// which is what we'll use to communicate with Windows about this window
		mainWindow = CreateWindowEx( windowStyle_extended, s_mainWindowClass_name, windowCaption, windowStyle,
			position_x, position_y, width, height,
			hParent, hMenu, hProgram, userData );
		if ( mainWindow == NULL )
		{
			const char* errorCaption = "No Main Window";
			std::string errorMessage( "Windows failed to create the main window: " );
			errorMessage += eae6320::GetLastWindowsError();
			MessageBox( NULL, errorMessage.c_str(), errorCaption, MB_OK | MB_ICONERROR );
			return NULL;
		}
	}

	// Change the window's size based on the desired client area resolution
	{
		// In a real game these values would come from an external source
		// rather than be hard-coded
		const int desiredWidth = 800;
		const int desiredHeight = 600;

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
				errorMessage += eae6320::GetLastWindowsError();
				MessageBox( NULL, errorMessage.c_str(), NULL, MB_OK | MB_ICONERROR );
				goto OnError;
			}
			// Get the dimensions of the client area
			RECT clientDimensions;
			if ( GetClientRect( mainWindow, &clientDimensions ) == FALSE )
			{
				std::string errorMessage( "Windows failed to get the dimensions of the main window's client area: " );
				errorMessage += eae6320::GetLastWindowsError();
				MessageBox( NULL, errorMessage.c_str(), NULL, MB_OK | MB_ICONERROR );
				goto OnError;
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
				errorMessage += eae6320::GetLastWindowsError();
				MessageBox( NULL, errorMessage.c_str(), NULL, MB_OK | MB_ICONERROR );
				goto OnError;
			}
		}
	}

	// Display the window in the initial state that Windows requested
	ShowWindow( mainWindow, i_initialWindowDisplayState );

	return mainWindow;

OnError:

	if ( DestroyWindow( mainWindow ) == FALSE )
	{
		std::string errorMessage( "Windows failed to destroy the main window "
			"after an error in creation: " );
		errorMessage += eae6320::GetLastWindowsError();
		MessageBox( NULL, errorMessage.c_str(), NULL, MB_OK | MB_ICONERROR );
	}
	mainWindow = NULL;

	return NULL;
}

ATOM RegisterMainWindowClass( const HINSTANCE i_thisInstanceOfTheProgram )
{
	WNDCLASSEX wndClassEx = { 0 };
	wndClassEx.cbSize = sizeof( WNDCLASSEX );
	wndClassEx.hInstance = i_thisInstanceOfTheProgram;

	// The class's style
	wndClassEx.style = 0;
#ifdef EAE6320_PLATFORM_GL
	// Reserve a unique device context for this window for OpenGL's use
	wndClassEx.style |= CS_OWNDC;
#endif
	// The function that will process all of the messages
	// that Windows will send to windows of this class
	wndClassEx.lpfnWndProc = OnMessageReceived;
	// Extra bytes can be set aside in the class for user data
	wndClassEx.cbClsExtra = 0;
	// Extra bytes can be set aside for each window of this class,
	// but this is usually specified for each window individually
	wndClassEx.cbWndExtra = 0;
	// The large and small icons that windows of this class should use
	// (These can be found in the Resources folder; feel free to change them)
	wndClassEx.hIcon = LoadIcon( i_thisInstanceOfTheProgram, MAKEINTRESOURCE( IDI_BIG ) );
	wndClassEx.hIconSm = LoadIcon( i_thisInstanceOfTheProgram, MAKEINTRESOURCE( IDI_SMALL ) );
	// The cursor that should display when the mouse pointer is over windows of this class
	wndClassEx.hCursor = LoadCursor( NULL, IDC_ARROW );
	// The "brush" that windows of this class should use as a background
	// (Setting this is a bit confusing but not important,
	// so don't be alarmed if the next line looks scary)
	wndClassEx.hbrBackground = reinterpret_cast<HBRUSH>( IntToPtr( COLOR_BACKGROUND + 1 ) );
	// A menu can be specified that all windows of this class would use by default,
	// but usually this is set for each window individually
	wndClassEx.lpszMenuName = NULL;
	// The class name (see comments where this is initialized)
	wndClassEx.lpszClassName = s_mainWindowClass_name;

	// Now all of the above information is given to Windows.
	// If all goes well, the class will be successfully registered
	// and it can be specified by name when creating the main window.
	const ATOM mainWindowClass = RegisterClassEx( &wndClassEx );
	if ( mainWindowClass == NULL )
	{
		const char* errorCaption = "No Main Window Class";
		std::string errorMessage( "Windows failed to register the main window's class: " );
		errorMessage += eae6320::GetLastWindowsError();
		MessageBox( NULL, errorMessage.c_str(), errorCaption, MB_OK | MB_ICONERROR );
	}
	return mainWindowClass;
}

// WaitForMainWindowToCloseAndReturnExitCode
//------------------------------------------

bool CleanupMainWindow()
{
	if ( s_mainWindow != NULL )
	{
		if ( DestroyWindow( s_mainWindow ) != FALSE )
		{
			s_mainWindow = NULL;
		}
		else
		{

			const char* errorCaption = "Couldn't Destroy Main Window";
			std::string errorMessage( "Windows failed to destroy the main window: " );
			errorMessage += eae6320::GetLastWindowsError();
			MessageBox( NULL, errorMessage.c_str(), errorCaption, MB_OK | MB_ICONERROR );
			return false;
		}
		
	}
	
	return true;
}

bool OnMainWindowClosed( const HINSTANCE i_thisInstanceOfTheProgram )
{
	bool wereThereErrors = false;

	if ( !CleanupMainWindow() )
	{
		wereThereErrors = true;
	}

	if ( !UnregisterMainWindowClass( i_thisInstanceOfTheProgram ) )
	{
		wereThereErrors = true;
	}

	return !wereThereErrors;
}

LRESULT CALLBACK OnMessageReceived( HWND i_window, UINT i_message, WPARAM i_wParam, LPARAM i_lParam )
{
	// DispatchMessage() will send messages to the main window here.
	// There are many messages that get sent to a window,
	// but games can ignore most of them
	// and let Windows handle them in the default way.

	// Process any messages that the game cares about
	// (any messages that are processed here should return a value
	// rather than letting the default processing function try to handle them a second time)
	switch( i_message )
	{
	// A key has been pressed down, and this is the translated character
	case WM_CHAR:
		{
			// This isn't usually the best way to handle keyboard input in a real-time game,
			// but it is a convenient way to handle an exit key
			// (The WPARAM input parameter indicates which key was pressed,
			// but this example program only cares about the escape key)
			if ( i_wParam == VK_ESCAPE )
			{
				// You do _not_ need to do this in your game,
				// but this example program shows you how to display a "message box"
				// that asks the user for confirmation
				int result;
				{
					const char* caption = "Exit Program?";
					const char* message = "Are you sure you want to quit?";
					result = MessageBox( s_mainWindow, message, caption, MB_YESNO | MB_ICONQUESTION );
				}
				if ( result == IDYES )
				{
					// Instruct Windows to send a WM_QUIT message
					{
						// The exit code is ignored,
						// but just as an example of what's possible a different exit code is sent here
						// than when the user closes the program in the usual way
						// (by clicking the X in the upper-right hand corner).
						int exitCode = 1;
						PostQuitMessage( exitCode );
					}

					// For WM_CHAR messages, return 0 to indicate that it was processed
					return 0;
				}
				else
				{
					// If the user doesn't select "Yes" to quit
					// then do nothing to keep running the program
				}
			}

			// If the key press wasn't handled pass it on to Windows to process in the default way
			break;
		}
	// The window's nonclient area is being destroyed
	case WM_NCDESTROY:
		{
			// This is the last message a window will receive
			// (Any child windows have already been destroyed).
			// After this message has been processed the window's handle will be invalid:
			s_mainWindow = NULL;

			// When the main window is destroyed
			// a WM_QUIT message should be sent
			// (if this isn't done the application would continue to run with no window).
			// This is where the exitCode in WaitForShutdown() comes from:
			int exitCode = 0;	// Arbitrary de facto success code
			PostQuitMessage( exitCode );	// This sends a WM_QUIT message

			// For WM_NCDESTROY messages, return 0 to indicate that it was processed
			return 0;
		}
	}

	// Pass any messages that weren't handled on to Windows
	return DefWindowProc( i_window, i_message, i_wParam, i_lParam );
}

bool UnregisterMainWindowClass( const HINSTANCE i_thisInstanceOfTheProgram )
{
	if ( UnregisterClass( s_mainWindowClass_name, i_thisInstanceOfTheProgram ) != FALSE )
	{
		return true;
	}
	else
	{
		const char* errorCaption = "Couldn't Unregister Main Window Class";
		std::string errorMessage( "Windows failed to unregister the main window's class: " );
		errorMessage += eae6320::GetLastWindowsError();
		MessageBox( NULL, errorMessage.c_str(), errorCaption, MB_OK | MB_ICONERROR );
		return false;
	}
}

bool WaitForMainWindowToClose( int& o_exitCode )
{
	float o_x =0.0f, o_y=100.0f;
	eae6320::Math::cQuaternion playerrotation;
	eae6320::Math::cVector playeraxisofrotation = eae6320::Math::cVector(0, 0, 0);
	eae6320::Math::cVector offset(0.0f, 0.0f, 0.0f);
	eae6320::Math::cVector rotationOffset(0.0f, 0.0f, 0.0f);
	eae6320::Math::cVector thirdPersonCamOffset(0.0f, 0.0f, 0.0f);
	// Any time something happens that Windows cares about, it will send the main window a message.

	// One of the messages it sends is that the application should quit;
	// this can be sent when a user closes the window
	// (e.g. presses the X in the upper-right corner),
	// but we can also tell Windows to send a quit message if the user chooses to quit from within the game
	// (e.g. from an in-game menu)

	// Enter an infinite loop that will continue until a quit message (WM_QUIT) is received from Windows
	MSG message = { 0 };
	do
	{
		// To send us a message, Windows will add it to a queue.
		// Most Windows applications should wait until a message is received and then react to it.
		// Real-time programs, though, must continually draw new images to the screen as fast as possible
		// and only pause momentarily when there is a Windows message to deal with.
		//eae6320::Graphics::Render();
		// This means that the first thing that must be done every iteration of the game loop is to "peek" at the message queue
		// and see if there are any messages from Windows that need to be handled
		bool hasWindowsSentAMessage;
		{
#ifdef EAE6320_PLATFORM_GL
			//eae6320::Graphics::Render();
#endif
			HWND getMessagesFromAnyWindowBelongingToTheCurrentThread = NULL;
			unsigned int getAllMessageTypes = 0;
			unsigned int ifAMessageExistsRemoveItFromTheQueue = PM_REMOVE;
			hasWindowsSentAMessage = PeekMessage( &message, getMessagesFromAnyWindowBelongingToTheCurrentThread,
				getAllMessageTypes, getAllMessageTypes, ifAMessageExistsRemoveItFromTheQueue ) == TRUE;
		}
		if ( !hasWindowsSentAMessage )
		{
			
			eae6320::Time::OnNewFrame();
			// Usually there will be no messages in the queue, and the game can run
			
			offset.x =offset.z = offset.y = 0.0f;
			{
				if (eae6320::UserInput::IsKeyPressed(VK_LEFT))
				{
					rotationOffset.y -= 0.3f;
					//playeraxisofrotation.y = -1;
					//playerrotation = playerrotation * eae6320::Math::cQuaternion(0.01f, playeraxisofrotation);
					//offset.x = -10.0f;

				}
				if (eae6320::UserInput::IsKeyPressed(VK_RIGHT))
				{
					rotationOffset.y += 0.3f;
				//	playeraxisofrotation.y = 1;
					//playerrotation = playerrotation * eae6320::Math::cQuaternion(0.01f, playeraxisofrotation);
					//offset.x = 1.0f;
				}
				if (eae6320::UserInput::IsKeyPressed(VK_UP))
				{
					//offset.y = -15.0f;
				}
				if (eae6320::UserInput::IsKeyPressed(VK_DOWN))
				{
					//offset.y = +15.0f;
				}
				if (eae6320::UserInput::IsKeyPressed('W'))
				{
					offset.z -= 1.0f;
				//	Camera::getInstance().camera_axis.z -= 2.0f;

				}
				if (eae6320::UserInput::IsKeyPressed('S'))
				{
					offset.z += 1.0f;
				//	Camera::getInstance().camera_axis.z += 2.0f;
				}
				if (eae6320::UserInput::IsKeyPressed('A'))
				{
					offset.x -= 1.0f;
				//	Camera::getInstance().camera_axis.x -= 2.0f;
				}
				if (eae6320::UserInput::IsKeyPressed('D'))
				{
					offset.x += 1.0f;

				//	Camera::getInstance().camera_axis.x += 2.0f;
				}
				if (eae6320::UserInput::IsKeyPressed('0'))
				{
					//offset.z = 0;

				}
				if (eae6320::UserInput::IsKeyPressed('1'))
				{
					//offset.z = 1;

				}
				if (eae6320::UserInput::IsKeyPressed('2'))
				{
					//offset.z = 2;

				}
				if (eae6320::UserInput::IsKeyPressed('3'))
				{
					//offset.z = 3;

				}
				if (eae6320::UserInput::IsKeyPressed('4'))
				{
					//offset.z = 4;

				}
				if (eae6320::UserInput::IsKeyPressed('5'))
				{
					//offset.z = 5;

				}
				if (eae6320::UserInput::IsKeyPressed('6'))
				{
					//offset.z = 6;

				}
				if (eae6320::UserInput::IsKeyPressed('7'))
				{
					//offset.z = 7;

				}
				if (eae6320::UserInput::IsKeyPressed('8'))
				{
					//offset.z = 8;

				}
				if (eae6320::UserInput::IsKeyPressed('9'))
				{
					//offset.z = 9;

				}

				if (eae6320::UserInput::IsKeyPressed('R'))
				{
					offset.y += 1.0f;
					Camera::getInstance().camera_axis.y -= 2.0f;
				}
				if (eae6320::UserInput::IsKeyPressed('F'))
				{
					offset.y -= 1.0f;
					Camera::getInstance().camera_axis.y += 2.0f;
				}
				if (eae6320::UserInput::IsKeyPressed('Z'))
				{

					thirdPersonCamOffset.x -= 5.0f;
					//Camera::getInstance().axisofrotation.y = -1;
				//	Camera::getInstance().camear_rotation = Camera::getInstance().camear_rotation * eae6320::Math::cQuaternion(0.01f, Camera::getInstance().axisofrotation);
				//	Camera::getInstance().camera_axis.x += ( cosf(2*3.14*(3.6/360)));
				//	Camera::getInstance().camera_axis.z += ( sinf(2 * 3.14*(1 / 360)));
					//Camera::getInstance().camera_axis.y += 2.0f;
				}
				if (eae6320::UserInput::IsKeyPressed('X'))
				{
					thirdPersonCamOffset.x += 5.0f;
				//	Camera::getInstance().axisofrotation.y = 1;
				//	Camera::getInstance().camear_rotation = Camera::getInstance().camear_rotation * eae6320::Math::cQuaternion(0.01f, Camera::getInstance().axisofrotation);
				}

			}
			const float unitsPerSecond = 300.0f;	// This is arbitrary
			const float unitsToMove = unitsPerSecond * eae6320::Time::GetSecondsElapsedThisFrame();	// This makes the speed frame-rate-independent
																									// Normalize the offset
			offset.x *= unitsToMove;
			offset.y *= unitsToMove;
			offset.z *= unitsToMove;
			rotationOffset *= unitsToMove / 100.0f;


			Camera::getInstance().UpdateOrientation(rotationOffset);
			Camera::getInstance().UpdatePosition(offset);
			ThirdPersonMovement(eae6320::Graphics::Player1, offset ,  rotationOffset, thirdPersonCamOffset);





			//o_x += offset.x;
			//o_y += offset.y;
			//Camera::getInstance().camera_axis.x += offset.x;
			//Camera::getInstance().camera_axis.z += offset.y;
			//eae6320::Graphics::m_x = eae6320::Graphics::m_x + offset.x;
			//eae6320::Graphics::m_y = eae6320::Graphics::m_y + offset.y;
			//eae6320::Graphics::getGlobalEffect()->SetPositionOffset(eae6320::Graphics::m_x, eae6320::Graphics::m_y, 0);
			//eae6320::Graphics::getGlobalDefaultMaterial()->i_effect->SetPositionOffset(eae6320::Graphics::m_x, eae6320::Graphics::m_y, 0);
			eae6320::Graphics::Render();
			//eae6320::Graphics::s_Effect->SetPositionOffset(offset.x, offset.y);
			// (This example program has nothing to do,
			// and so it will just constantly run this while loop using up CPU cycles.
			// A real game might have something like the following:
			//	someGameClass.OnNewFrame();
			// or similar, though.)



		}
		else
		{
// If Windows _has_ sent a message, this iteration of the loop will handle it.
			// Note that Windows messages will take precedence over our game functionality;
			// this is because if we don't handle Windows messages the window can appear sluggish to the user
			// (if s/he tries to move it, for example, but we give too much precedence to our own game code).

			// First, the message must be "translated"
			// (Key presses are translated into character messages)
			TranslateMessage( &message );

			// Then, the message is sent on to the appropriate processing function.
			// This function is specified in the lpfnWndProc field of the WNDCLASSEX struct
			// used to register a class with Windows.
			// In the case of the main window in this example program
			// it will always be OnMessageReceived()
			DispatchMessage( &message );
		}
	} while ( message.message != WM_QUIT );
	
	eae6320::Graphics::ShutDown();
	// The exit code for the application is stored in the WPARAM of a WM_QUIT message
	o_exitCode = static_cast<int>( message.wParam );

	return true;

}
