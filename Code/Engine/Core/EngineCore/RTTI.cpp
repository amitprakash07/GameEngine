#include "RTTI.h"
#include "EngineCore.h"

Engine::RTTI::~RTTI()
{
	
}

void Engine::RTTI::setTypeInfo(char* i_char)
{
	if(i_char)
		mTypeInfo = Engine::EngineCore::getStringPool()->findString(i_char);
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




