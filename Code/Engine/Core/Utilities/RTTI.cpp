#include "RTTI.h"
#include "StringPool.h"

Engine::RTTI::~RTTI()
{
	
}

void Engine::RTTI::setTypeInfo(char* i_char)
{
	if(i_char)
		mTypeInfo = Engine::StringPool::getStringPool()->findString(i_char);
}

bool Engine::RTTI::isType(RTTI* i_RTTI_ptr)
{
	if(i_RTTI_ptr)
	{
		if (mTypeInfo == i_RTTI_ptr->mTypeInfo)
			return true;
		return false;
	}
	return false;
}

Engine::RTTI::RTTI()
{
	
}




