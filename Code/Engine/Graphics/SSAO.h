#ifndef __SSAO_H
#define __SSAO_H

#include "../../Externals/OpenGLExtensions/OpenGlExtensions.h"
#include "../Core/Utilities/SharedPointer.h"

namespace Engine
{
	namespace Graphics
	{
		class SSAO
		{
		public:
			static void GenerateSSAOTexture();
			static void InitializeSSAO(std::string iMaterialFileName);
			static unsigned int GetSSAOTexture();
			static unsigned int GetSSAOBlurTexture();
		private:
			static SharedPointer<SSAO> mSSAOInstance;
			SSAO();
			std::string mMaterial;
			GLuint glNormalTexture;
			GLuint glViewPositionTexture;
			GLuint glDepthTexture;
			GLuint glGeometryFrameBuffer;
			GLuint glGeometryRenderBuffer;

			//SSAO Stage
			GLuint glSSAOTexture;
			GLuint glSSAOBlurTexture;
			GLuint glSSAOFrameBuffer;
			GLuint glSSAOBlurFrameBuffer;
		};
	}
}

#endif