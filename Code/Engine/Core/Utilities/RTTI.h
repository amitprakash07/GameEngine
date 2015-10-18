#ifndef __RTTI_H
#define __RTTI_H

#include <string>

namespace Engine
{

	class RTTI
	{
	public:
		virtual std::string getTypeInfo() = 0;
		virtual bool isBothSameType(RTTI*, std::string) =0;
		virtual ~RTTI(){};
		RTTI(){};	
	};
}
#endif