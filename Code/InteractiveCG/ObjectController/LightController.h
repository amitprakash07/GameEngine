#ifndef __LIGHT_CONTROLLER_H
#define __LIGHT_CONTROLLER_H

#include "../../Engine/Core/Utilities/IObjectController.h"


namespace Application
{
	class LightController : public Engine::IObjectController
	{
		void updateObject(Engine::Object &, Engine::typedefs::ActionWithKeyBound iAction) override;
	};
}

#endif