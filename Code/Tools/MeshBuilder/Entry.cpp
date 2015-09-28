#include "MeshBuilder.h"

int main(int i_argumentCount, char** i_arguments)
{
	return Tools::AssetBuilder::Build<Tools::AssetBuilder::MeshBuilder>(i_arguments, i_argumentCount);
}