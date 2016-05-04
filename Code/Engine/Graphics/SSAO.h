#ifndef __SSAO_H
#define __SSAO_H

#include "../../Externals/OpenGLExtensions/OpenGlExtensions.h"
#include "../Core/Utilities/SharedPointer.h"
#include "../Core/Maths/Vec4.h"

namespace Engine
{
	namespace Graphics
	{
		class SSAO
		{
		public:
			static void GenerateGBuffer();
			static void RunSSAO();
			static void InitializeSSAO(std::string i_SSAOEffectFileName);
			static unsigned int GetSSAOTexture();
			static unsigned int GetSSAOBlurTexture();
		private:
			static SharedPointer<SSAO> mSSAOInstance;
			SSAO();
			std::string mSSAOEffectFile;
			std::string mSSAOMaterial;
			std::string mBlurMaterial;
			//Normal Texture
			GLuint glNormalTexture;
			//View Position Texture
			GLuint glViewPositionTexture;
			//DepthTexture
			GLuint glDepthTexture;
			//Color Texture 
			GLuint glColorTexture;
			//FrameBuffer for G-Buffer Data
			GLuint glGeometryFrameBuffer;
			//Render Buffer for Depth
			//GLuint glGeometryRenderBuffer;

			int mSampleCount;
			float mVaryingRadius;


			struct samplePoints
			{
				Math::Vector4 point[256];
				Math::Vector4 randomVectors[256];
			};
						
			samplePoints mSamplePointsData;


			//Test
			GLuint testFrameBuffer;
			GLuint testTexture;

			//SSAO Stage
			GLuint glSSAOTexture;
			GLuint glSSAOBlurTexture;
			GLuint glSSAOFrameBuffer;
			GLuint glSSAOBlurFrameBuffer;
			GLenum bufferAttachment[4];		

			GLuint SSAOProgram;

			//UniformLocation
			GLuint mRadius;
			GLuint mSamplePointCount;
			GLuint mProjectionMatrix;
			

			//VertexArray for Quad
			GLuint mVertexArray;
			//Buffer for sample
			GLuint samplePointsBuffer;
			
		};
	}
}

#endif