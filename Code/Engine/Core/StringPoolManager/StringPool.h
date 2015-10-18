#ifndef __STRING_POOL_H
#define __STRING_POOL_H


#include <vector>
#include "additionaltypes.h"
#include "../Utilities/SharedPointer.h"


namespace Engine
{
	class StringPool:public RTTI
	{
	public:
		static SharedPointer<StringPool>			getStringPool();
		char*										findString(char*);
		std::string getTypeInfo() override { return ""; }
		bool isBothSameType(RTTI*, std::string) override { return true; }
				~StringPool();
	private:
		static SharedPointer<StringPool>			mStringPool;
		std::vector<Engine::typedefs::String>		mStringList;
		char*										addString(char *);
		StringPool();
		StringPool(StringPool&);
		
	};//end-StringPool
}//end namespace myEngine

#endif //__STRING_POOL_H