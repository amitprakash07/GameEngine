#ifndef __UNIFORMBLOCK_H
#define __UNIFORMBLOCK_H

#include <vector>
#include "uniformdefs.h"
#include <map>
#include "../Core/Utilities/SharedPointer.h"

namespace Engine
{
	namespace Graphics
	{
		class UniformBlock
		{
		public:
			static SharedPointer<UniformBlock>
				addUniformBlock(std::string effectFileName, 
					std::string uniformName,
					ShaderType iShaderType,
					std::vector<std::string> iUniforms);
			static SharedPointer<UniformBlock>
				getUniformBlock(std::string effectFileName,
					std::string iUniformName,
					ShaderType iShaderType);
			static bool isExist(std::string effectFileName,
				std::string iUniformName, ShaderType iShaderType);
			static void setAllUniformBlockForTheEffectInShader(std::string effectFileName);
			std::vector<std::string> getUniformNames() const;
			UniformBlockStruct getUniformBlockData(std::string iUniformName) const;
			void setUniformBlockData(std::string uniformName,
				DataTypes iUniformDataType,
				Data iUniformBlockData);
			std::string prefixUniformName() const;
			void setUniformBlockName(std::string iUniformName);
			void setEffectFileName(std::string iEffectFileName);
			void setShaderType(ShaderType iShaderType);
			std::string getUniformBlockName() const;
			std::string getEffectFileName() const;
			ShaderType getShaderType() const;			
		private:
			UniformBlock(std::string iEffectFileName, 
				std::string iUniformName,
				ShaderType iShaderType);
			void initialize(std::vector<std::string> iUniformNamesInBlock);
			void populateInformationForUniformBlock();
			void writeDataToShader();
			static std::map<std::string,SharedPointer<UniformBlock>> mUniformBlockList;
			std::vector<UniformBlockStruct> mUniformsInBLock;
			std::string effectFileName;
			ShaderType mShaderType;
			UniformHandle mHandle;
			std::string mUniformName;
			int uniformBlockSizeInShader;
#ifdef PLATFORM_OPEN_GL
			GLuint bufferObject;			
#endif
		};
	}
}

#endif