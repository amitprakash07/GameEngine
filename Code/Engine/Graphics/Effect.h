#ifndef _EFECTS_H
#define _EFECTS_H

#include "../Windows/WindowsIncludes.h"

#ifdef PLATFORM_D3D
#include <d3dx9shader.h>
#elif PLATFORM_OPEN_GL
#include "../Graphics/Graphics.h"
#include <gl/GLU.h>
#endif

#include <vector>
#include <map>
#include "../Core/Utilities/SharedPointer.h"
#include "../Core/Maths/cMatrix_transformation.h"
#include "../Core/Maths/cVector.h"
#include "../Core/Maths/cQuaternion.h"

namespace Engine
{
	namespace Graphics
	{
		struct Uniforms
		{
			Engine::Math::cMatrix_transformation g_transform_localToWorld;
			Engine::Math::cMatrix_transformation g_transform_worldToView;
			Engine::Math::cMatrix_transformation g_transform_viewToScreen;
			void calculateUniforms(Engine::Math::cVector, Engine::Math::cQuaternion);
		};

		class Effect:public RTTI
		{
		public:
			static bool addEffectToList(std::string, std::string);
			//static Engine::SharedPointer<Effect> getEffect(std::string, std::string);
			static Engine::SharedPointer<Effect> getEffect(std::string);
			static void deleteAllEffect();
			bool LoadEffect();
			bool setShaders();
			std::string getTypeInfo() override { return ""; }
			bool isBothSameType(RTTI*, std::string) override { return true; }
			~Effect();
			void setUniforms(Engine::Math::cVector, Engine::Math::cQuaternion);
		private:
			static std::map<std::string, Engine::SharedPointer<Effect>> mEffectList;
			std::string shaderName;
			std::string fragmentShader;
			std::string vertexShader;
			std::string effectName;
			std::string effectFileName;
			Uniforms m_uniforms;
			bool LoadShaders();
			bool LoadFragmentShader();
			bool LoadVertexShader();
			bool ReadUniforms();
			//void setuniforms(Engine::Math::cVector, Engine::Math::cQuaternion);
			static bool isEffectExist(std::string);
			Effect(std::string, std::string);
#ifdef PLATFORM_D3D
			IDirect3DVertexShader9* s_vertexShader;
			IDirect3DPixelShader9* s_fragmentShader;
			ID3DXConstantTable*    s_constantsTable;
			D3DXHANDLE				s_uniformLocalToWorld; //Shader Name - g_transform_localToWorld 
			D3DXHANDLE				s_uniformWorldToView; //Shader Name - g_transform_worldToView
			D3DXHANDLE				s_uniformViewToScreen; //Shader Name - g_transform_viewToScreen
#elif PLATFORM_OPEN_GL
			GLuint s_programId;
			GLint s_uniformLocalToWorld;
			GLint s_uniformWorldToView;
			GLint s_uniformViewToScreen;
			bool CreateProgram();
#endif
		};
	}
}

#endif

