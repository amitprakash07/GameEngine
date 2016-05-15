#ifndef __DEBUG_MENU_CONTROLLER_H
#define __DEBUG_MENU_CONTROLLER_H

#include "../../../Engine/Core/Utilities/IObjectController.h"

namespace Game
{
	class DebugMenuController :public Engine::IObjectController
	{
	public:
		void updateObject(Engine::Object &,
			Engine::typedefs::ActionWithKeyBound iAction) override;
	};
}

#endif
