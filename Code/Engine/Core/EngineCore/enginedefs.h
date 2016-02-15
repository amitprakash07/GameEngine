#ifndef __ENGINE_DEF_H
#define __ENGINE_DEF_H

#include "../../Windows/WindowsIncludes.h"
#include "../Maths/cQuaternion.h"
#include "../Maths/cVector.h"


namespace Engine
{
	struct Transformation
	{
		Engine::Math::cVector mPositionOffset;
		Engine::Math::cQuaternion mOrientation;
		Transformation()
		{
			mPositionOffset = Engine::Math::cVector();
			mOrientation = Engine::Math::cQuaternion();
		}
	};
}

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
