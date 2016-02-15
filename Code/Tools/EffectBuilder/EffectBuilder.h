#ifndef __EFFECT_BUILDER_H
#define __EFFECT_BUILDER_H

#include "../BuilderHelper/cbBuilder.h"
#include "../../Engine/Graphics/uniformdefs.h"



namespace Tools
{
	namespace AssetBuilder
	{
		struct ShaderUniformDef
		{
			char * uniformName;
			Engine::Graphics::ShaderType shaderType;
			Engine::Graphics::UniformDataType uniformValType;
			Engine::Graphics::Transform_Matrix_Type matrixType;
			uint8_t valCount;
		};

		class EffectBuilder : public cbBuilder
		{
		public:
			EffectBuilder();
			bool LoadEffectFile();
			virtual bool Build(const std::vector<std::string>& i_arguments) override;
		private:
			char* vertexName;
			char* fragmentName;
			uint8_t* renderSate;
			uint8_t uniformCount;
			ShaderUniformDef* uniforms;
		};
	}
}

#endif