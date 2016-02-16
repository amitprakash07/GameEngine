// SetAssetFile.cpp : Defines the entry point for the console application.
//

#include "../../Engine/Windows/WindowsFunctions.h"

int main()
{
	WindowsUtil::Assert(
		WindowsUtil::setVSEnvironmentVariableValue("AssetFile", "AssetsToBuild.lua")
		,"Unable to set the AssetFile Name");
    return 0;
}

