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
#include <vector>

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
			bool LoadEffect();
			bool setShaders() const;
			std::string getTypeInfo() const override { return ""; }
			bool isBothSameType(RTTI*, std::string) const  override { return true; }
			void setLocalToWorldMatrrixTransformValue(Transformation iObject);
			void setWorldToViewTransformationValue(Transformation cameraTransformation);
			void setViewToScreenTransformationValue(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
			void setUniformValue(std::string, UniformValues);
			void setAllUniforms();
			void setMaterialUniformValue(char*, MaterialUniform) const;
			void setTextureUniform(TextureResource, SamplerID, int i_textureUnit = 0);
			UniformHandle getUniformHandle(char *, ShaderType) const;
			SamplerID getSamplerID(UniformHandle, ShaderType);
			bool isUniformExist(std::string iUniformName);
			~Effect();
		private:
			static std::map<std::string, Engine::SharedPointer<Effect>> mEffectList;
			std::map<ShaderType, std::string> shaderNames;
			std::map<std::string, SharedPointer<Engine::Graphics::Uniform>> uniformNames;
			std::string effectName;
			int uniformCount;
			uint8_t *renderState;
			bool LoadShaders();
			bool LoadFragmentShader();
			bool LoadVertexShader();
			bool isLocalToWorldTransformExist;
			bool isWorldToViewTransformExist;
			bool isViewToScreenTransformExist;
			void setTransformMatrixExistenceFlag(Transform_Matrix_Type iMatrixType);
			SharedPointer<Uniform> getTransformationMatrix(Transform_Matrix_Type iMatrixType);
			SharedPointer<Uniform> getUniform(std::string iUniformName);
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

