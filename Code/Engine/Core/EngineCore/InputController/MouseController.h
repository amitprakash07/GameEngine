#ifndef __MOUSE_CONTROLLER_H
#define __MOUSE_CONTROLLER_H

#include "../../Utilities/SharedPointer.h"
#include "../../Utilities/IMessageHandler.h"
#include "../../Utilities/RTTI.h"
#include "../enginedefs.h"




namespace Engine
{
	class MouseController :public  IMessageHandler
	{
	public:
		static SharedPointer<MouseController> getMouseController();
		Engine::MouseEventAndPosition getCurrentMouseState()const;
		void HandleMessage(Engine::utils::StringHash &, RTTI*, void* i_pMessageData) override;
		std::string getTypeInfo() const override;
		bool isBothSameType(RTTI*, std::string) const override;
		void leftButtonPressed(bool);
		void rightButtonPressed(bool);
		void middleButtonPressed(bool);
		void mouseMoving(bool);
		void setMousePosition(int, int, POINTS);		
	private:
		static SharedPointer<MouseController> mMouseInputController;
		std::string mTypeName;
		MouseEventAndPosition mMouseCurrentStateAndPosition;
		MouseEventAndPosition mMousePreviousStateAndPosition;		
		MouseController();
		bool arcBallReady;
	};
}
#endif