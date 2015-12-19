#ifndef __MOUSE_CONTROLLER_H
#define __MOUSE_CONTROLLER_H

#include "../../Utilities/SharedPointer.h"
#include "../../Utilities/IMessageHandler.h"
#include "../../Utilities/RTTI.h"
#include "../EngineTypdefs.h"




namespace Engine
{
	class MouseController:public  IMessageHandler
	{
	public:
		static SharedPointer<MouseController> getMouseController();
		MouseEventAndPosition getCurrentMouseState();
		void HandleMessage(Engine::utils::StringHash &, RTTI*, void* i_pMessageData) override;
		std::string getTypeInfo() override;
		bool isBothSameType(RTTI*, std::string) override;
		void leftButtonPressed(bool);
		void rightButtonPressed(bool);
		void middleButtonPressed(bool);
		void mouseMoving(bool);
		void setMousePosition(int, int ,POINTS);
	private:
		static SharedPointer<MouseController> mMouseInputController;
		std::string mTypeName;
		MouseEventAndPosition mMouseCurrentStateAndPosition;
		MouseEventAndPosition mMousePreviousStateAndPosition;
		MouseController();
	};
}
#endif