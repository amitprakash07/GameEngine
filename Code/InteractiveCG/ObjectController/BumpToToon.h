#ifndef __BUMP_TO_TOON_H
#define __BUMP_TO_TOON_H

#include "../../Engine/Core/Utilities/IObjectController.h"


namespace Application
{
	class BumpToToon : public Engine::IObjectController
	{
		void updateObject(Engine::Object &, Engine::typedefs::ActionWithKeyBound iAction) override;
	};
}

#endif