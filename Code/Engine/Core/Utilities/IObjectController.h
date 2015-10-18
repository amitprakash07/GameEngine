#ifndef __IOBJECT_CONTROLLER
#define __IOBJECT_CONTROLLER

#include "SharedPointer.h"
#include "additionaltypes.h"

namespace Engine
{
	class GameObject;
	class IObjectController: public RTTI
	{
	public:
		virtual ~IObjectController(){};
		virtual void updateGameObject(Engine::GameObject &, Engine::typedefs::Direction) = 0;
		virtual std::string getTypeInfo() override { return "Engine::IObjectController"; }
		virtual bool isBothSameType(RTTI*, std::string i_inString) override { return (i_inString == "Engine::IObjectController"); }
		IObjectController() {}
		};
}

#endif