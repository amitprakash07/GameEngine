#ifndef __EFFECT_BUILDER_H
#define __EFFECT_BUILDER_H

#include "../BuilderHelper/cbBuilder.h"

namespace Tools
{
	namespace AssetBuilder
	{
		class EffectBuilder: public cbBuilder
		{
		public:
			bool LoadEffectFile();
			virtual bool Build(const std::vector<std::string>& i_arguments) override;
		private:
			std::string vertexName;
			std::string fragmentName;

		};
	}
}

#endif