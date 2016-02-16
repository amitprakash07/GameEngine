#ifndef __UNIFORM_H
#define __UNIFORM_H

#include "uniformdefs.h"
#include <map>
#include "../Core/Utilities/SharedPointer.h"


namespace Engine
{
	namespace Graphics
	{
		class Uniform
		{
		public:
			static SharedPointer<Uniform> addUniform(std::string iUniformName,
				std::string effectFileName, 
				ShaderType iShaderType);
			static SharedPointer<Uniform> getUniform(std::string uniformName,
				std::string effectFileName, ShaderType iShaderType);
			static bool isUnformExist(
				std::string i_UniformNamae, std::string effectName,
				ShaderType iShaderType);			
			static void setAllUniformToShaderObjects(std::string effectName);
			static void setUniformValueToShaderObject(
				std::string effect, std::string uniformName,
				ShaderType iShaderType);
			void setUniformValue(UniformValues& iinitialValue);			
			void setValType(UniformDataType iDataType);
			void setMatrixType(Transform_Matrix_Type iMatrixType);
			void setValCount(uint8_t iCount = 1);
			void setHandle(UniformHandle iHandle);
			const char* getUniformName()const;
			ShaderType getShaderType() const;
			UniformDataType getUniformDataType() const;
			uint8_t getValueCount() const;
			UniformHandle getHandle() const;
			Transform_Matrix_Type getMatrixType() const;
			UniformValues getUniformValues() const;							
			char* prefixUniformName() const;
			~Uniform();
		private:
			static std::map<std::string, SharedPointer<Uniform>> mUniformListInSystem;
#ifdef PLATFORM_D3D
			void setValueInShaderObject(const ID3DXConstantTable* constantTable) const;
#elif PLATFORM_OPEN_GL
			void setValueInShaderObject() const;
#endif
			Uniform();
			std::string effectName;
			UniformData mUniform;			
			void setName(char* iUniformName);
			void setShaderType(ShaderType iShaderType);
		};
	}
}

#endif