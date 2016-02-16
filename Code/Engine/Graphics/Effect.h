#ifndef _EFECTS_H
#define _EFECTS_H

#include "../Windows/WindowsIncludes.h"

#ifdef PLATFORM_D3D
#include <d3dx9shader.h>
#elif PLATFORM_OPEN_GL
#include "../Graphics/Graphics.h"
#include <gl/GLU.h>
#endif

#include <map>
#include "../Core/Utilities/SharedPointer.h"
#include "Uniform.h"


namespace Engine
{
	namespace Graphics
	{
		class Effect :public RTTI
		{
		public:
			static bool addEffectToList(std::string);
			static Engine::SharedPointer<Effect> getEffect(std::string);
			static void deleteAllEffect();
			static bool isEffectExist(std::string);
			std::string getTransformMatrixUniformName(ShaderType iShaderType,
				Transform_Matrix_Type iMatrixType) const;
			bool LoadEffect();
			bool setShaders() const;
			std::string getTypeInfo() const override { return ""; }
			bool isBothSameType(RTTI*, std::string) const  override { return true; }						
			void setMaterialUniformValue(char*, MaterialUniform) const;
			void setTextureUniform(TextureResource, SamplerID, int i_textureUnit = 0);
			UniformHandle getUniformHandle(const char *, ShaderType) const;
			SamplerID getSamplerID(UniformHandle, ShaderType);			
#ifdef PLATFORM_D3D
			const ID3DXConstantTable* getConstantTable(ShaderType iType) const;
#endif
			~Effect();
		private:
			static std::map<std::string, Engine::SharedPointer<Effect>> mEffectList;
			std::map<ShaderType, std::string> shaderNames;	
			std::string localToWorldTransformUniformName;
			std::string worldToViewTransformUniformName;
			std::string viewToScreenTransformUniformName;			
			std::string effectName;					
			uint8_t *renderState;
			bool isLocalToWorldTransformExist;
			bool isWorldToViewTransformExist;
			bool isViewToScreenTransformExist;
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

