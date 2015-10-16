#include "StringPool.h"
#include "../Utilities/HashedString.h"

Engine::StringPool* Engine::StringPool::mStringPool = nullptr;

Engine::SharedPointer<Engine::StringPool> Engine::StringPool::getStringPool()
{
	if (mStringPool == nullptr)
	{
		/*mStringPool = EngineController::GameEngine::isEngineInitialized() ?
			new (EngineController::GameEngine::getMemoryManager()->__alloc(sizeof(StringPool))) StringPool() :
		*/
		mStringPool = new StringPool();
	}

	return mStringPool;

}//getStringPool

Engine::StringPool::~StringPool()
{
	while (mStringList.size() != 0)
	{
		delete (mStringList.at(0).mString);
		mStringList.at(0).mString = nullptr;
		mStringList.erase(mStringList.begin());
	}
}

Engine::StringPool::StringPool()
{
	mStringList.reserve(200);
}

char* Engine::StringPool::findString(char * i_string)
{
	if (i_string != nullptr)
	{
		size_t tempStringLength = strlen(i_string);
		bool isFound = false;

		for (size_t i = 0; i < mStringList.size(); i++)
		{
			if (Engine::utils::StringHash(mStringList[i].getAsChar()) == Engine::utils::StringHash(i_string))
				return mStringList[i].getAsChar();
		}
		return (addString(i_string));
	}
	return nullptr;
}//end find function


char* Engine::StringPool::addString(char* i_String)
{
	Engine::typedefs::String tempString = Engine::typedefs::String(i_String);
	mStringList.push_back(tempString);
	return tempString.mString;
}
