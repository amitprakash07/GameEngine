#ifndef __MESH_BUILDER_H
#define __MESH_BUILDER_H

#include "../BuilderHelper/cbBuilder.h"

namespace Tools
{
	namespace AssetBuilder
	{
		class MeshBuilder:public cbBuilder
		{
			virtual bool Build(const std::vector<std::string>& i_arguments) override;
		};
	}
}

#endif
