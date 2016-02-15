#include "Effect.h"
#include "../Windows/WindowsFunctions.h"
#include "../../Engine/Core/Utilities/HashedString.h"
#include <fstream>
#include "../Core/EngineCore/EngineCore.h"
#include "Uniform.h"

typedef char BYTES;

std::map<std::string, Engine::SharedPointer<Engine::Graphics::Effect>> Engine::Graphics::Effect::mEffectList;

bool Engine::Graphics::Effect::addEffectToList(std::string i_effectName)
{
	bool success = false;
	std::stringstream errormessage;
	if (i_effectName.size() > 0)
	{
		if (isEffectExist(i_effectName))
		{
			return true;
		}
		else
		{
			Engine::SharedPointer<Engine::Graphics::Effect> effect(new Effect(i_effectName), "Engine::Graphics::Effect");
			if (!effect.isNull())
			{
				if (effect->LoadEffect())
				{
					mEffectList[i_effectName] = effect;
					success = true;
				}
				else
					success = false;
			}
		}
	}
	else
	{
		errormessage << "Vertex Shader and Fragment Shader file name is null";
		WindowsUtil::Print(errormessage.str());
		success = false;
	}
	return success;
}

Engine::SharedPointer<Engine::Graphics::Effect> Engine::Graphics::Effect::getEffect(std::string i_shaderName)
{
	for (std::map<std::string, Engine::SharedPointer<Engine::Graphics::Effect>>::iterator i = mEffectList.begin(); i != mEffectList.end(); ++i)
	{
		if (i->first == i_shaderName)
			return i->second;
	}
	return SharedPointer<Engine::Graphics::Effect>();
}

void Engine::Graphics::Effect::deleteAllEffect()
{
	for (std::map<std::string, Engine::SharedPointer<Engine::Graphics::Effect>>::iterator i = mEffectList.begin(); i != mEffectList.end(); ++i)
	{
		i->second.deleteObject();
	}
}

bool Engine::Graphics::Effect::isEffectExist(std::string i_effectName)
{
	if (!i_effectName.empty())
	{
		for (std::map<std::string, SharedPointer<Effect>>::iterator i = mEffectList.begin(); i != mEffectList.end(); ++i)
		{
			if (Engine::utils::StringHash(i->first.c_str()) == Engine::utils::StringHash(i_effectName.c_str()))
				return true;
		}
		return false;
	}
	return false;
}

bool Engine::Graphics::Effect::LoadEffect()
{
	std::stringstream errormessage;
	std::ifstream readFile;

	if (!readFile.is_open())
		readFile.open(effectName.c_str(), std::ifstream::binary);

	readFile.seekg(0, readFile.end);
	size_t length = static_cast<size_t>(readFile.tellg());
	readFile.seekg(0, readFile.beg);

	BYTES * buffer = new BYTES[length];
	//Lets read evrything from asset binary file
	readFile.read(buffer, length);
	readFile.close();//Closing the file Pointer

	if (buffer)
	{
		BYTES * tempBuffer = buffer;
		std::string vertexshader = Engine::EngineCore::getShaderFolderPath().c_str();
		std::string tempEffectVal = tempBuffer;
		vertexshader += tempEffectVal;
		tempBuffer += tempEffectVal.size() + 1;
		shaderNames[Vertex] = vertexshader;

		std::string fragmentShader = Engine::EngineCore::getShaderFolderPath();
		std::string tempFragment = tempBuffer;
		fragmentShader += tempFragment;
		tempBuffer += tempFragment.size() + 1;
		memcpy(renderState, tempBuffer, sizeof(char));
		tempBuffer += sizeof(char);
		shaderNames[Fragment] = fragmentShader;

		memcpy(&uniformCount, reinterpret_cast<uint8_t*>(tempBuffer), sizeof(uint8_t));
		tempBuffer += sizeof(uint8_t);

		if (!LoadShaders())
			return false;
		/*
		File Format
		vertexShaderFileName
		fragmentShaderFileName
		renderStates

		noOfEngineUniforms
		for each uniform
		{
		UniformName
		shaderType
		valType
		}
		*/
		if (uniformCount>0)
		{
			//m_uniforms = new ShaderUniform[uniformCount];
			for (int i = 0; i < uniformCount; ++i)
			{
				SharedPointer<Uniform> tempUniform = Uniform::createUniform();
				//Uniform Name
				char * tempUniformName = tempBuffer;
				int uniformNameLength = strlen(tempUniformName);
				tempUniformName[uniformNameLength] = '\0';
				tempBuffer += uniformNameLength + 1;
				tempUniform->setName(tempUniformName);

				//Shader Type
				ShaderType tempShaderType;
				memcpy(&tempShaderType, reinterpret_cast<ShaderType*>(tempBuffer), sizeof(ShaderType));
				tempBuffer += sizeof(ShaderType);
				tempUniform->setShaderType(tempShaderType);


				//ValType
				UniformDataType dataType;
				memcpy(&dataType, reinterpret_cast<UniformDataType*>(tempBuffer), sizeof(UniformDataType));
				tempBuffer += sizeof(UniformDataType);
				tempUniform->setValType(dataType);

				//MatrixType in case of Matrix Data type
				if (dataType == Matrix)
				{
					Transform_Matrix_Type tempMatrixType;
					memcpy(&tempMatrixType, reinterpret_cast<Transform_Matrix_Type*>(tempBuffer), sizeof(Transform_Matrix_Type));
					tempBuffer += sizeof(Transform_Matrix_Type);
					tempUniform->setMatrixType(tempMatrixType);
					setTransformMatrixExistenceFlag(tempMatrixType);
				}

				//ValCount
				uint8_t dataCount;
				memcpy(&dataCount, reinterpret_cast<uint8_t*>(tempBuffer), sizeof(uint8_t));
				tempBuffer += sizeof(uint8_t);
				tempUniform->setValCount(dataCount);


				//Handle
				UniformHandle uniformHandle = getUniformHandle(tempUniformName, tempShaderType);
				WindowsUtil::Assert(uniformHandle, "Unable to grab handle");
				tempUniform->setHandle(uniformHandle);

				uniformNames[tempUniform->prefixUniformName()] = tempUniform;
			}
		}

		delete buffer;
	}
	return false;
}


void Engine::Graphics::Effect::setTransformMatrixExistenceFlag(Transform_Matrix_Type iMatrixType)
{
	switch (iMatrixType)
	{
	case LocalToWorld:
		isLocalToWorldTransformExist = true;
		break;
	case WorldToView:
		isWorldToViewTransformExist = true;
		break;
	case ViewToScreen:
		isViewToScreenTransformExist = true;
		break;
	default:
		break;
	}
}

void Engine::Graphics::Effect::setLocalToWorldMatrrixTransformValue(Transformation iObject)
{
	if (isLocalToWorldTransformExist)
	{
		Engine::Math::cMatrix_transformation tempLocal =
			Math::cMatrix_transformation(iObject.mOrientation, iObject.mPositionOffset);
		SharedPointer<Uniform> localToWorld = getTransformationMatrix(LocalToWorld);
		if (!localToWorld.isNull())
		{
			UniformValues tempValue;
			tempValue.matrixValue.matrix = tempLocal;
			localToWorld->setUniformValue(tempValue);
		}
	}
}

void Engine::Graphics::Effect::setWorldToViewTransformationValue(Transformation cameraTransformation)
{
	if (isLocalToWorldTransformExist)
	{
		Engine::Math::cMatrix_transformation tempLocal =
			Math::cMatrix_transformation::CreateWorldToViewTransform(cameraTransformation.mOrientation,
				cameraTransformation.mPositionOffset);
		SharedPointer<Uniform> worldToView = getTransformationMatrix(WorldToView);
		if (!worldToView.isNull())
		{
			UniformValues tempValue;
			tempValue.matrixValue.matrix = tempLocal;
			worldToView->setUniformValue(tempValue);
		}
	}
}

void Engine::Graphics::Effect::setViewToScreenTransformationValue(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{
	if (isLocalToWorldTransformExist)
	{
		Engine::Math::cMatrix_transformation tempLocal =
			Math::cMatrix_transformation::CreateViewToScreenTransform(
				fieldOfView, aspectRatio, nearPlane, farPlane);
		SharedPointer<Uniform> viewToScreen = getTransformationMatrix(ViewToScreen);
		if (!viewToScreen.isNull())
		{
			UniformValues tempValue;
			tempValue.matrixValue.matrix = tempLocal;
			viewToScreen->setUniformValue(tempValue);
		}
	}
}


Engine::SharedPointer<Engine::Graphics::Uniform> Engine::Graphics::Effect::getTransformationMatrix(Transform_Matrix_Type iMatrixType)
{
	bool transformExist = false;
	switch (iMatrixType)
	{
	case LocalToWorld:
		if (isLocalToWorldTransformExist)
			transformExist = true;
		break;
	case WorldToView:
		if (isWorldToViewTransformExist)
			transformExist = true;
		break;
	case ViewToScreen:
		if (isViewToScreenTransformExist)
			transformExist = true;
		break;
	default:
		break;
	}

	if (transformExist)
	{
		for (std::map<std::string, SharedPointer<Uniform>>::iterator i = uniformNames.begin();
		i != uniformNames.end(); ++i)
		{
			if (i->second->getUniformData().value.matrixValue.Type == iMatrixType)
				return i->second;
		}
	}
	return SharedPointer<Uniform>();
}


void Engine::Graphics::Effect::setUniformValue(std::string iUniformName, UniformValues iValues)
{
	SharedPointer<Uniform> tempUniform = getUniform(iUniformName);
	if (!tempUniform.isNull())
		tempUniform->setUniformValue(iValues);
}


Engine::SharedPointer<Engine::Graphics::Uniform> Engine::Graphics::Effect::getUniform(std::string iUniformName)
{
	for (std::map<std::string, SharedPointer<Uniform>>::iterator i = uniformNames.begin();
	i != uniformNames.end(); ++i)
	{
		if (strcmp(i->second->getUniformData().uniformName, iUniformName.c_str()) == 0)
			return i->second;
	}
	return SharedPointer<Uniform>();
}


bool Engine::Graphics::Effect::isUniformExist(std::string iUniformName)
{
	for (std::map<std::string, SharedPointer<Uniform>>::iterator i = uniformNames.begin();
	i != uniformNames.end(); ++i)
	{
		if (strcmp(i->second->getUniformData().uniformName, iUniformName.c_str()) == 0)
			return true;
	}
	return false;
}





















