#ifndef __STRING_POOL_H
#define __STRING_POOL_H


#include <vector>
#include "../Utilities/additionaltypes.h"
#include "../Utilities/RTTI.h"


namespace Engine
{
	class StringPool:public RTTI
	{
	public:
		static SharedPointer<StringPool>			getStringPool();
		char*										findString(char*);
		std::string getTypeInfo() const override { return ""; }
		bool isBothSameType(SharedPointer<RTTI>, std::string)const  override { return true; }
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