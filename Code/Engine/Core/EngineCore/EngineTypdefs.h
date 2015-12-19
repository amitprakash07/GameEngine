#ifndef __ENGINE_TYPEDEF_H
#define __ENGINE_TYPEDEF_H

#include "../../Windows/WindowsIncludes.h"

struct MouseStates
{
	bool leftButtonPressed;
	bool rightButtonPressed;
	bool middleButtonPressed;
	bool mouseMoving;

};

struct MouseEventAndPosition
{
	int x; //x-coordinate
	int y; //y-coordiante
	POINTS P; //Point in screen coordinate - depending on screen size
	MouseStates mMouseStates;
};

struct WindowsParam
{
	UINT windowsMessage;
	WPARAM wParam;
	LPARAM lParam;
};


#endif
