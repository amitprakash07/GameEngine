#ifndef __IOBJECT_CONTROLLER
#define __IOBJECT_CONTROLLER

#include "../../Utilities/SharedPointer.h"
#include "../additionaltypes.h"

namespace Engine
{
	class GameObject;
	class IObjectController
	{
	public:
		virtual ~IObjectController(){};
		virtual void updateGameObject(Engine::GameObject &, Engine::typedefs::Direction) = 0;
		IObjectController() {}
		};
}

#endif