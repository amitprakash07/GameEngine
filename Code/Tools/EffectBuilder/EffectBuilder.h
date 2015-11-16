#ifndef __EFFECT_BUILDER_H
#define __EFFECT_BUILDER_H

#include "../BuilderHelper/cbBuilder.h"

namespace Tools
{
	namespace AssetBuilder
	{
		enum __renderState
		{
			ALPHA_BLENDING = 1 << 0,
			DEPTH_TESTING = 1<<1,
			DEPTH_WRITING = 1<<2,
			FACE_CULLING = 1<<3
		};

		class EffectBuilder: public cbBuilder
		{
		public:
			EffectBuilder();
			bool LoadEffectFile();
			virtual bool Build(const std::vector<std::string>& i_arguments) override;
		private:
			char* vertexName;
			char* fragmentName;
			uint8_t* renderSate;

		};
	}
}

#endif