#ifndef __RTTI_H
#define __RTTI_H

#include "SharedPointer.h"
#include <string>

namespace Engine
{
	class RTTI
	{
	public:
		virtual std::string getTypeInfo() = 0;
		virtual bool isBothSameType(SharedPointer<RTTI>, std::string) =0;
		virtual ~RTTI(){};
		RTTI(){};	
	};
}
#endif