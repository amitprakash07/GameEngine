#ifndef __IOBJECT_CONTROLLER
#define __IOBJECT_CONTROLLER

#include "SharedPointer.h"
#include "additionaltypes.h"


namespace Engine
{
	class Object;
	class IObjectController: public RTTI
	{
	public:
		virtual ~IObjectController(){};
		virtual void updateObject(Engine::Object &, Engine::typedefs::Direction) = 0;
		virtual std::string getTypeInfo() const override { return "Engine::IObjectController"; }
		virtual bool isBothSameType(RTTI*, std::string i_inString) const override { return (i_inString == "Engine::IObjectController"); }
		IObjectController() {}
		};
}

#endif