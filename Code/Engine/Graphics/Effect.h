#ifndef _EFECTS_H
#define _EFECTS_H

#pragma warning(disable :4006)
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
#include "../Core/Maths/cVector.h"

namespace Engine
{
	namespace Graphics
	{
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
			void setPositionOffset(Engine::Math::cVector);
		private:
			static std::map<std::string, Engine::SharedPointer<Effect>> mEffectList;
			std::string shaderName;
			std::string fragmentShader;
			std::string vertexShader;
			std::string effectName;
			std::string effectFileName;
			Engine::Math::cVector positionOffset;
			bool LoadShaders();
			bool LoadFragmentShader();
			bool LoadVertexShader();
			static bool isEffectExist(std::string);
			Effect(std::string, std::string);
#ifdef PLATFORM_D3D
			IDirect3DVertexShader9* s_vertexShader;
			IDirect3DPixelShader9* s_fragmentShader;
			ID3DXConstantTable*    s_constantsTable;
			D3DXHANDLE				s_uniformPositionOffset;
#elif PLATFORM_OPEN_GL
			GLuint s_programId;
			GLint s_uniformPositionOffset;
			bool CreateProgram();
#endif
		};
	}
}

#endif

