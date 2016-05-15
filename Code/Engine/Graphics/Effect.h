#ifndef _EFECTS_H
#define _EFECTS_H

#ifdef PLATFORM_D3D
#include <d3dx9shader.h>
#elif PLATFORM_OPEN_GL
#include "../Graphics/Graphics.h"
#include <gl/GLU.h>
#endif

#include <map>
#include "Uniform.h"
#include "UniformBlock.h"
#include "../../Engine/Core/Utilities/RTTI.h"

namespace Engine
{	
	namespace Graphics
	{
		class Effect :public Engine::RTTI
		{
		public:
			static bool addEffectToList(std::string);
			static Engine::SharedPointer<Effect> getEffect(std::string);
			static void deleteAllEffect();
			static bool isEffectExist(std::string);
			static std::vector<SharedPointer<Effect>> getAllEfects();
			std::string getEffectName()const;
			std::string getTransformMatrixUniformName(ShaderType iShaderType,
				Transform_Matrix_Type iMatrixType) const;
			bool LoadEffect();
			bool setShaders() const;
			void changeRenderState(__renderState iRenderState, bool iSatus);
			std::string getTypeInfo() const override { return ""; }
			bool isBothSameType(SharedPointer<RTTI>, std::string) const  override { return true; }						
			void setMaterialUniformValue(char*, MaterialUniform) const;
			UniformHandle getUniformHandle(const char *, ShaderType) const;
			SamplerID getSamplerID(UniformHandle, ShaderType);		
			SharedPointer<Uniform> addUniform(std::string iUniformName, 
				ShaderType iShaderType, 
				UniformDataType iDataType, 
				uint8_t iDataCount, UniformValues& iData);
			SharedPointer<UniformBlock> addUniformBlock(std::string iUniformName,
				ShaderType iShaderType,
				UniformDataType iDataType,
				std::vector<std::string> i_uniformInBlockNames);
			void changeUniformData(std::string iUniformName,
				ShaderType iShaderType, UniformValues& iNewValues);
			const ConstantTable getConstantTable(ShaderType iType) const;
#ifdef PLATFORM_OPEN_GL
			unsigned int GetProgramID() const;
#endif
			~Effect();
		private:
			static std::map<std::string, Engine::SharedPointer<Effect>> mEffectList;
			std::map<ShaderType, std::string> shaderNames;
			std::string normalMatrixUniformName;
			std::string scaleMatrixUniformName;
			std::string localToWorldTransformUniformName;
			std::string worldToViewTransformUniformName;
			std::string viewToScreenTransformUniformName;			
			std::string effectName;					
			uint8_t *renderState;
			bool isLocalToWorldTransformExist;
			bool isWorldToViewTransformExist;
			bool isViewToScreenTransformExist;
			bool isScaleMatrixTransformExist;
			bool isNormalMAtrixTransformExist;
			bool LoadShaders();
			bool LoadFragmentShader();
			bool LoadVertexShader();	
			void setTransformMatrixExistenceFlag(
				std::string uniformName, Transform_Matrix_Type iMatrixType);
			Effect(std::string);
#ifdef PLATFORM_D3D
			IDirect3DVertexShader9* s_vertexShader;
			IDirect3DPixelShader9*  s_fragmentShader;
			ID3DXConstantTable*  s_vertexShaderConstantTable;
			ID3DXConstantTable*  s_fragmentShaderConstantTable;			
#elif PLATFORM_OPEN_GL
			GLuint s_programId;
			bool CreateProgram();
#endif
		};
	}
}

#endif

