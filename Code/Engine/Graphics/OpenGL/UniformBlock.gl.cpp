#include "../UniformBlock.h"
#include "../Effect.h"
#include "../../Windows/WindowsFunctions.h"

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
	uniformBlockSizeInShader = 0;
	mUniformsInBLock.reserve(20);
}


void Engine::Graphics::UniformBlock::populateInformationForUniformBlock()
{
	ConstantTable programId =
		Engine::Graphics::Effect::getEffect(effectFileName)->getConstantTable(mShaderType);
	glGenBuffers(1, &bufferObject);
	glBindBuffer(GL_UNIFORM_BUFFER, bufferObject);
	GLenum errorCode = glGetError();
	
	mHandle = glGetUniformBlockIndex(programId, mUniformName.c_str());
	errorCode = glGetError();
	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unbale to get the index of the uniform");

	glGetActiveUniformBlockiv(programId, mHandle, GL_UNIFORM_BLOCK_DATA_SIZE, &uniformBlockSizeInShader);
	errorCode = glGetError();
	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unbale to get the uniform block size in shader");

	GLint NumUniforms = mUniformsInBLock.size();
	GLuint *indices = new GLuint[NumUniforms];
	GLint *size = new GLint[NumUniforms];
	GLint *offset = new GLint[NumUniforms];
	GLint * type = new GLint[NumUniforms];
	GLchar ** names = nullptr;
	names = new char*[NumUniforms];
	for (unsigned int i = 0; i < mUniformsInBLock.size(); i++)
	{
		int uniformNameLength = mUniformsInBLock[i].uniformName.size();
		names[i] = new char[uniformNameLength];
		memcpy(names[i], mUniformsInBLock[i].uniformName.c_str(), uniformNameLength);
		*(names[i] + uniformNameLength) = '\0';
	}	 

	glGetUniformIndices(programId, NumUniforms, names, indices);
	errorCode = glGetError();
	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to get the uniform indices in the block");
	glGetActiveUniformsiv(programId, NumUniforms, indices, GL_UNIFORM_OFFSET, offset);
	errorCode = glGetError();
	WindowsUtil::Assert(errorCode ==GL_NO_ERROR, "Unable to get the uniform offsets");
	glGetActiveUniformsiv(programId, NumUniforms, indices, GL_UNIFORM_SIZE, size);
	errorCode = glGetError();
	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to get the size of the uniforms");
	glGetActiveUniformsiv(programId, NumUniforms, indices, GL_UNIFORM_TYPE, type);
	errorCode = glGetError();
	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to get tht type of the uniforms");

	for (int i = 0; i < NumUniforms; i++)
	{
		mUniformsInBLock[i].index = indices[i];
		mUniformsInBLock[i].offset = offset[i];
		mUniformsInBLock[i].type = Graphics::getDataType(type[i]);
		mUniformsInBLock[i].size = Graphics::getDataTypeSize(mUniformsInBLock[i].type);
	}
}


void Engine::Graphics::UniformBlock::writeDataToShader()
{
	glBindBuffer(GL_UNIFORM_BUFFER, bufferObject);
	GLenum errorCode;
	errorCode = glGetError();
	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to bind the uniform buffer");
	GLvoid* buffer = malloc(uniformBlockSizeInShader);

	for (unsigned int i = 0; i < mUniformsInBLock.size(); i++)
	{
		memcpy(static_cast<char*>(buffer) + mUniformsInBLock[i].offset, &mUniformsInBLock[i].data, mUniformsInBLock[i].size);
	}

	glBufferData(GL_UNIFORM_BUFFER, uniformBlockSizeInShader, buffer, GL_DYNAMIC_DRAW);
	errorCode = glGetError();
	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to write data to shader");
	glBindBufferBase(GL_UNIFORM_BUFFER, mHandle, bufferObject);
	errorCode = glGetError();
	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to Bind the uniform buffer base");
}



