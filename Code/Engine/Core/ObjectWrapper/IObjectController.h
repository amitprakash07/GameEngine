#ifndef __IOBJECT_CONTROLLER
#define __IOBJECT_CONTROLLER

#include "../Utilities/SharedPointer.h"
#include "../EngineCore/additionaltypes.h"

namespace Engine
{
	class GameObject;
	class IObjectController
	{
	public:
		IObjectController(){}
		virtual ~IObjectController(){};
		virtual void updateGameObject(Engine::SharedPointer<Engine::GameObject> &, Engine::typedefs::Direction) = 0;
	};
}

#endif