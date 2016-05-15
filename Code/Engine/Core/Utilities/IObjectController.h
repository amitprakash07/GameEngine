#ifndef __IOBJECT_CONTROLLER
#define __IOBJECT_CONTROLLER

#include "additionaltypes.h"

namespace Engine
{
	class Object;
	class IObjectController
	{
	public:
		virtual ~IObjectController(){};
		virtual void updateObject(Engine::Object &, typedefs::ActionWithKeyBound iAction) = 0;		
		IObjectController() {}
		};
}

#endif