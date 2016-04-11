#include "UniformBlock.h"
#include "../Windows/WindowsFunctions.h"


std::map<std::string, Engine::SharedPointer<Engine::Graphics::UniformBlock>>
Engine::Graphics::UniformBlock::mUniformBlockList;


Engine::SharedPointer<class Engine::Graphics::UniformBlock> 
Engine::Graphics::UniformBlock::addUniformBlock(
	std::string effectFileName, 
	std::string iUniformName,
	ShaderType iShaderType, 
	std::vector<std::string> iUniforms)
{
	if (!isExist(effectFileName, iUniformName, iShaderType))
	{
		SharedPointer<UniformBlock> tempUniform =
			SharedPointer<UniformBlock>(new UniformBlock(effectFileName,
				iUniformName, iShaderType), "Engine::Graphics::UniformBlock");
		tempUniform->initialize(iUniforms);
		tempUniform->populateInformationForUniformBlock();
		mUniformBlockList[tempUniform->prefixUniformName()] = tempUniform;		
		return tempUniform;
	}
	return (getUniformBlock(effectFileName,iUniformName, iShaderType));
}


std::string Engine::Graphics::UniformBlock::getEffectFileName() const
{
	return effectFileName;
}


Engine::Graphics::ShaderType Engine::Graphics::UniformBlock::getShaderType() const
{
	return mShaderType;
}


std::string Engine::Graphics::UniformBlock::getUniformBlockName() const
{
	return mUniformName;
}


void Engine::Graphics::UniformBlock::setEffectFileName(std::string iEffectFileName)
{
	effectFileName = iEffectFileName;
}


void Engine::Graphics::UniformBlock::setShaderType(ShaderType iShaderType)
{
	mShaderType = iShaderType;
}

void Engine::Graphics::UniformBlock::setUniformBlockName(std::string iUniformName)
{
	mUniformName = iUniformName;
}


std::string Engine::Graphics::UniformBlock::prefixUniformName() const
{
	std::string prefixedNameWithEffect;
	switch (mShaderType)
	{
	case Vertex:
		prefixedNameWithEffect += "V";
		break;
	case Fragment:
		prefixedNameWithEffect += "F";
		break;
	case Tessalation:
		prefixedNameWithEffect += "T";
		break;
	case Geometry:
		prefixedNameWithEffect += "G";
		break;
	case Compute:
		prefixedNameWithEffect += "C";
		break;
	case Unknown:
		prefixedNameWithEffect += "U";
		break;
	}

	prefixedNameWithEffect += effectFileName;
	prefixedNameWithEffect += mUniformName;
	return prefixedNameWithEffect;
}


Engine::SharedPointer<class Engine::Graphics::UniformBlock> 
Engine::Graphics::UniformBlock::getUniformBlock(std::string effectFileName, 
	std::string iUniformName, 
	ShaderType iShaderType)
{
	for (std::map<std::string, SharedPointer<UniformBlock>>::iterator i = mUniformBlockList.begin();
	i != mUniformBlockList.end(); ++i)
	{
		if (strcmp(i->second->mUniformName.c_str(), iUniformName.c_str()) == 0 &&
			strcmp(i->second->effectFileName.c_str(), effectFileName.c_str()) == 0 &&
			i->second->mShaderType == iShaderType)
			return i->second;
	}
	return SharedPointer<UniformBlock>();
}


bool Engine::Graphics::UniformBlock::isExist(
	std::string effectFileName, 
	std::string iUniformName, 
	ShaderType iShaderType)
{
	if (mUniformBlockList.size() > 0)
	{
		SharedPointer<UniformBlock> tempUniform
			= getUniformBlock(effectFileName, iUniformName, iShaderType);
		if (tempUniform.isNull())
			return false;
		return true;
	}
	return false;
}


Engine::Graphics::UniformBlockStruct 
Engine::Graphics::UniformBlock::getUniformBlockData(
	std::string iUniformName) const
{
	for (int i = 0; i < mUniformsInBLock.size(); ++i)
	{
		if (strcmp(mUniformsInBLock[i].uniformName.c_str(), iUniformName.c_str()) == 0)
			return mUniformsInBLock[i];
	}
	return UniformBlockStruct();
}


void Engine::Graphics::UniformBlock::setUniformBlockData(std::string iUniformName, 
	DataTypes iUniformDataType, 
	Data iUniformBlockData){
	for (std::vector<UniformBlockStruct>::iterator i = mUniformsInBLock.begin();
	i!= mUniformsInBLock.end(); ++i)
	{
		if(i->uniformName == iUniformName
			&& WindowsUtil::Assert(i->type == iUniformDataType, 
				"Data Type Mismatch in Parameter and Shader"))
		{
			i->data.assignData(iUniformDataType,iUniformBlockData);
		}
	}
}


std::vector<std::string> Engine::Graphics::UniformBlock::getUniformNames() const
{
	std::vector<std::string> tempNames;
	for (int i = 0; i < mUniformsInBLock.size(); i++)
	{
		tempNames.push_back(mUniformsInBLock[i].uniformName);
	}

	return tempNames;
}

void Engine::Graphics::UniformBlock::initialize(
	std::vector<std::string> iUniformNamesInBlock)
{
	UniformBlockStruct temp;
	for (int i = 0; i < iUniformNamesInBlock.size(); i++)
	{
		temp.uniformName = iUniformNamesInBlock[i];
		mUniformsInBLock.push_back(temp);
	}
}


void Engine::Graphics::UniformBlock::setAllUniformBlockForTheEffectInShader(std::string iEffectFileName)
{
	for (std::map<std::string, SharedPointer<UniformBlock>>::iterator i = mUniformBlockList.begin();
	i!= mUniformBlockList.end(); ++i)
	{
		if(i->second->effectFileName == iEffectFileName)
		{
			i->second->writeDataToShader();
		}
	}
}





