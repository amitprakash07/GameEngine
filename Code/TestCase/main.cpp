#include <iostream>
#include "../Engine/Windows/WindowsFunctions.h"

int main()
{
	WindowsUtil::setVSEnvironmentVariableValue("Hello", "kjhsdkjfhdskjfhdksj");
	std::string valueData;
	WindowsUtil::GetVSEnvironmentVariable("Hello", valueData);
	std::cout << valueData;
}
