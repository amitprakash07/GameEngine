#ifndef __STRING_UTIL_H
#define __STRING_UTIL_H
#include <string>

namespace Engine
{
	namespace Utils
	{
		std::string RemoveString(std::string removeFrom, 
			std::string remmveWith, 
			bool beginning = true);
	}
}
#endif