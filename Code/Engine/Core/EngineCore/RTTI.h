#ifndef __RTTI_H
#define __RTTI_H

#include "../Utilities/HashedString.h"

namespace Engine
{
	class RTTI
	{
	public:
		virtual void setTypeInfo(char*);
		virtual bool isType(RTTI*);
		virtual ~RTTI();
		RTTI();
	private:
		Engine::utils::StringHash mTypeInfo;
	};
}
#endif