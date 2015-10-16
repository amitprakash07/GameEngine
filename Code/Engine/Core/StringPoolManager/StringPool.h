#ifndef __STRING_POOL_H
#define __STRING_POOL_H


#include <vector>
#include "additionaltypes.h"
#include "../Utilities/SharedPointer.h"

namespace Engine
{
	class StringPool
	{
	public:
		static SharedPointer<StringPool>			getStringPool();
		char*										findString(char*);
		~StringPool();
	private:
		static StringPool*							mStringPool;
		std::vector<Engine::typedefs::String>		mStringList;
		char*										addString(char *);
		StringPool();
		StringPool(StringPool&);
		
	};//end-StringPool
}//end namespace myEngine

#endif //__STRING_POOL_H