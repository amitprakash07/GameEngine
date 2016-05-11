#include "MouseController.h"
#include "../EngineCore.h"
#include "../../../Windows/WindowsFunctions.h"


Engine::SharedPointer<Engine::MouseController> Engine::MouseController::mMouseInputController;

std::string Engine::MouseController::getTypeInfo() const
{
	return mTypeName;
}

bool Engine::MouseController::isBothSameType(SharedPointer<RTTI> i_first, std::string i_second) const
{
	if (i_first->getTypeInfo() == i_second)
		return true;
	return false;
}

Engine::MouseController::MouseController()
{
	mTypeName = "Engine::InputController";
	mMouseCurrentStateAndPosition.mMouseStates.leftButtonPressed = false;
	mMouseCurrentStateAndPosition.mMouseStates.middleButtonPressed = false;
	mMouseCurrentStateAndPosition.mMouseStates.rightButtonPressed = false;
	mMouseCurrentStateAndPosition.x = 0;
	mMouseCurrentStateAndPosition.y = 0;

	mMousePreviousStateAndPosition.mMouseStates.leftButtonPressed = false;
	mMousePreviousStateAndPosition.mMouseStates.middleButtonPressed = false;
	mMousePreviousStateAndPosition.mMouseStates.rightButtonPressed = false;
	mMousePreviousStateAndPosition.x = 0;
	mMousePreviousStateAndPosition.y = 0;
	arcBallReady = false;

}

Engine::SharedPointer<Engine::MouseController> Engine::MouseController::getMouseController()
{
	if (mMouseInputController.isNull())
	{
		SharedPointer<MouseController> tempInputController(Engine::SharedPointer<MouseController>(new MouseController(), Engine::EngineCore::getStringPool()->findString("Engine::InputController")));
		mMouseInputController = tempInputController;
		Engine::utils::StringHash temp = Engine::utils::StringHash(Engine::EngineCore::getStringPool()->findString("MouseEvent"));
		Engine::EngineCore::getMessagingSystem()->addMessageHandler(temp, 
			tempInputController.CastSharedPointer<IMessageHandler>(), Engine::typedefs::HIGH);
	}
	return mMouseInputController;
}


void Engine::MouseController::HandleMessage(Engine::utils::StringHash&, SharedPointer<RTTI>, void* i_pMessageData)
{
	WindowsParam tempWindowsParameter = *reinterpret_cast<WindowsParam*>(i_pMessageData);
	if (tempWindowsParameter.windowsMessage && WM_LBUTTONDOWN && (!tempWindowsParameter.windowsMessage && WM_MOUSEMOVE))
	{
		mMouseCurrentStateAndPosition.mMouseStates.leftButtonPressed = true;
		if (tempWindowsParameter.wParam && MK_CONTROL)
			mMouseCurrentStateAndPosition.mMouseStates.ctrlKey = true;
		if (tempWindowsParameter.wParam && MK_SHIFT)
			mMouseCurrentStateAndPosition.mMouseStates.shiftKey = true;
		if (tempWindowsParameter.wParam && MK_RBUTTON)
			mMouseCurrentStateAndPosition.mMouseStates.rightButtonPressed = true;
		if (tempWindowsParameter.wParam && MK_MBUTTON)
			mMouseCurrentStateAndPosition.mMouseStates.middleButtonPressed = true;
		mMouseCurrentStateAndPosition.x = GET_X_LPARAM(tempWindowsParameter.lParam);
		mMouseCurrentStateAndPosition.y = GET_Y_LPARAM(tempWindowsParameter.lParam);
		mMouseCurrentStateAndPosition.P = MAKEPOINTS(tempWindowsParameter.lParam);
		arcBallReady = true;
		mMousePreviousStateAndPosition = mMouseCurrentStateAndPosition;
	}
	else
		arcBallReady = false;

	if(tempWindowsParameter.windowsMessage && WM_MOUSEMOVE && arcBallReady)
	{
		mMouseCurrentStateAndPosition.x = GET_X_LPARAM(tempWindowsParameter.lParam);
		mMouseCurrentStateAndPosition.y = GET_Y_LPARAM(tempWindowsParameter.lParam);
		mMouseCurrentStateAndPosition.P = MAKEPOINTS(tempWindowsParameter.lParam);
	}
	
	Engine::utils::StringHash temp = Engine::EngineCore::getStringPool()->findString("ActionOnMouseEvent");
	SharedPointer<MouseController> tempMouseController = Engine::EngineCore::getMouseInputController();
	Engine::EngineCore::getMessagingSystem()->sendMessage(temp, tempMouseController.CastSharedPointer<RTTI>(), i_pMessageData);
}

Engine::MouseEventAndPosition Engine::MouseController::getCurrentMouseState() const
{
	return mMouseCurrentStateAndPosition;
}

void Engine::MouseController::leftButtonPressed(bool i_state)
{
	mMousePreviousStateAndPosition.mMouseStates.leftButtonPressed
		= mMouseCurrentStateAndPosition.mMouseStates.leftButtonPressed;
	mMouseCurrentStateAndPosition.mMouseStates.leftButtonPressed = i_state;
}

void Engine::MouseController::rightButtonPressed(bool i_state)
{
	mMousePreviousStateAndPosition.mMouseStates.rightButtonPressed
		= mMouseCurrentStateAndPosition.mMouseStates.rightButtonPressed;
	mMouseCurrentStateAndPosition.mMouseStates.rightButtonPressed = i_state;
}

void Engine::MouseController::middleButtonPressed(bool i_state)
{
	mMousePreviousStateAndPosition.mMouseStates.middleButtonPressed
		= mMouseCurrentStateAndPosition.mMouseStates.middleButtonPressed;
	mMouseCurrentStateAndPosition.mMouseStates.middleButtonPressed = i_state;
}

void Engine::MouseController::mouseMoving(bool i_state)
{
	mMousePreviousStateAndPosition.mMouseStates.mouseMoving
		= mMouseCurrentStateAndPosition.mMouseStates.mouseMoving;
	mMouseCurrentStateAndPosition.mMouseStates.mouseMoving = i_state;
}


void Engine::MouseController::setMousePosition(int i_x, int i_y, POINTS i_point)
{
	mMousePreviousStateAndPosition.x = mMouseCurrentStateAndPosition.x;
	mMousePreviousStateAndPosition.y = mMouseCurrentStateAndPosition.y;
	mMousePreviousStateAndPosition.P = mMouseCurrentStateAndPosition.P;

	mMouseCurrentStateAndPosition.x = i_x;
	mMouseCurrentStateAndPosition.y = i_y;
	mMouseCurrentStateAndPosition.P = i_point;

}






