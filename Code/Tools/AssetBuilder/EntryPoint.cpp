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
	for ( int i = 1; i < argumentCount; ++i )
	{
		Tools::AssetBuilder::AssetBuilderUsingLua::BuildAsset(arguments[i]);
	}




	Tools::AssetBuilder::AssetBuilderUsingLua::ShutDown();
	if ( !wereThereErrors )
	{
		Tools::AssetBuilder::AssetBuilderUsingLua::ShutDown();
		return EXIT_SUCCESS;
	}
	else
	{
		return EXIT_FAILURE;
	}
}
