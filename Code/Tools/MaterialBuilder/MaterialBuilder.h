#ifndef __MATERIAL_BUILDER_H
#define __MATERIAL_BUILDER_H

#include "../BuilderHelper/cbBuilder.h"

namespace Tools
{
	namespace AssetBuilder
	{
		class MaterialBuilder : public cbBuilder
		{
			virtual bool Build(const std::vector<std::string>& i_arguments) override;
		};
	}
}
#endif