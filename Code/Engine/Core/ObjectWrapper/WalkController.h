#ifndef __WALK_CONTROLLER_H
#define __WALK_CONTROLLER_H

#include "IObjectController.h"


namespace Engine
{
	class WalkController:public IObjectController
	{
	public:
		void updateGameObject(Engine::SharedPointer<GameObject> & i_gameObject, Engine::typedefs::Direction i_dir) override;
	};
}

#endif