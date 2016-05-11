#ifndef __RTTI_H
#define __RTTI_H

#include <string>
#include "SharedPointer.h"

namespace Engine
{
	class RTTI
	{
	public:
		virtual std::string getTypeInfo() const = 0;
		virtual bool isBothSameType(SharedPointer<RTTI>, std::string) const = 0;
		virtual ~RTTI() {};
		RTTI() {};
	};
}
#endif