#include "../UniformBlock.h"
#include "../Effect.h"

Engine::Graphics::UniformBlock::UniformBlock(
	std::string iEffectFileName,
	std::string iUniformName,
	ShaderType iShaderType)
{
	effectFileName = iEffectFileName;
	mUniformName = iUniformName;
	mShaderType = iShaderType;
	mHandle = -1;
	bufferObject = 0;
}


void Engine::Graphics::UniformBlock::populateInformationForUniformBlock()
{
	ConstantTable programId =
		Engine::Graphics::Effect::getEffect(effectFileName)->getConstantTable(mShaderType);
	glGenBuffers(1, &bufferObject);
	GLenum errorCode = glGetError();
	mHandle = glGetUn
}



