#include "StringUtil.h"


std::string Engine::Utils::RemoveString(
	std::string removeFrom, std::string removeWith,
	bool beggining)
{
	std::string returnString;
	if(beggining)
	{
		char * returnStringInChar = new char[removeFrom.size() - removeWith.size() + 1];
		memcpy(returnStringInChar, 
			removeFrom.c_str() + removeWith.size(), 
			removeFrom.size() - removeWith.size());
		returnStringInChar[removeFrom.size() - removeWith.size()] = '\0';
		returnString = returnStringInChar;
		delete []returnStringInChar;
	}
	return returnString;
}