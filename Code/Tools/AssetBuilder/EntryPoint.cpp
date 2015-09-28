/*
	The main() function is where the program starts execution
*/

// Header Files
//=============

#include <cstdlib>
#include "AssetBuilder.h"
#include <string>
#include "../../Engine/Windows/WindowsFunctions.h"

// Entry Point
//============

int main( int argumentCount, char** arguments )
{
	bool wereThereErrors = false;
	
	if (!Tools::AssetBuilder::AssetBuilderUsingLua::Initialize())
		return EXIT_FAILURE;

	////The command line should have a list of assets to build
	Tools::AssetBuilder::AssetBuilderUsingLua::BuildAssets();
	
	Tools::AssetBuilder::AssetBuilderUsingLua::ShutDown();
	if ( !wereThereErrors )
	{
		return EXIT_SUCCESS;
	}
	else
	{
		return EXIT_FAILURE;
	}
}
