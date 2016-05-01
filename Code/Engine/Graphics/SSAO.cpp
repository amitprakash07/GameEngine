#include "SSAO.h"
#include "../Windows/WindowsFunctions.h"

Engine::SharedPointer<Engine::Graphics::SSAO>
	Engine::Graphics::SSAO::mSSAOInstance;

void Engine::Graphics::SSAO::GenerateSSAOTexture()
{
	
}

unsigned Engine::Graphics::SSAO::GetSSAOBlurTexture()
{
	return mSSAOInstance->glSSAOBlurTexture;
}

unsigned Engine::Graphics::SSAO::GetSSAOTexture()
{
	return mSSAOInstance->glSSAOTexture;
}

void Engine::Graphics::SSAO::InitializeSSAO(std::string iMaterialFileName)
{
	GLenum errorCode;
	if(!mSSAOInstance.isNull())
	{
		mSSAOInstance->mMaterial = iMaterialFileName;

		//Creating FrameBUffers for geometry pass  i.e. G-Buffer
		glGenFramebuffers(1, &mSSAOInstance->glGeometryFrameBuffer);
		errorCode = glGetError();
		WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to \
			create Frame Buffer for the G-Buffer");
		glBindFramebuffer(GL_FRAMEBUFFER, mSSAOInstance->glGeometryRenderBuffer);

		//Creating txtures for the G-Buffer
		glGenTextures(1, &mSSAOInstance->glNormalTexture);
		errorCode = glGetError();
		WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to create Frame Buffer");
		glBindTexture(GL_TEXTURE_2D, mSSAOInstance->glNormalTexture);
		errorCode = glGetError();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2048, 2048, 0, GL_RGBA,
			GL_UNSIGNED_INT_8_8_8_8, nullptr);
		errorCode = glGetError();
		WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to bind or create\
				the immutable texture");
		
		//Attaching the normal texture - color 0
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
			GL_TEXTURE_2D, mSSAOInstance->glNormalTexture, 0);


		glGenTextures(1, &mSSAOInstance->glViewPositionTexture);
		errorCode = glGetError();
		WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to create Frame Buffer");
		glBindTexture(GL_TEXTURE_2D, mSSAOInstance->glViewPositionTexture);
		errorCode = glGetError();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2048, 2048, 0, GL_RGBA,
			GL_UNSIGNED_INT_8_8_8_8, nullptr);
		errorCode = glGetError();
		WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to bind or create\
				the immutable texture");

		//Attaching the view texture - color 1
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1,
			GL_TEXTURE_2D, mSSAOInstance->glViewPositionTexture, 0);


		glGenTextures(1, &mSSAOInstance->glDepthTexture);
		errorCode = glGetError();
		WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to create Frame Buffer");
		glBindTexture(GL_TEXTURE_2D, mSSAOInstance->glDepthTexture);
		errorCode = glGetError();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2048, 2048, 0, GL_RGBA,
			GL_UNSIGNED_INT_8_8_8_8, nullptr);
		errorCode = glGetError();
		WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to bind or create\
				the immutable texture");

		//Attaching the depth texture - color 0
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2,
			GL_TEXTURE_2D, mSSAOInstance->glDepthTexture, 0);


		glGenRenderbuffers(1, &mSSAOInstance->glGeometryRenderBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, mSSAOInstance->glGeometryRenderBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER,
			GL_DEPTH_COMPONENT24, 2048, 2048);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
			GL_RENDERBUFFER, mSSAOInstance->glGeometryRenderBuffer);

		WindowsUtil::Assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE,
			"Unable to complete frame buffer operation");

		
		//Creating Frame Buffer for the SSAO shader
		glGenFramebuffers(1, &mSSAOInstance->glSSAOFrameBuffer);
		errorCode = glGetError();
		WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to \
			create Frame Buffer for the SSAO Pass");
		glBindFramebuffer(GL_FRAMEBUFFER, mSSAOInstance->glSSAOFrameBuffer);

		glGenTextures(1, &mSSAOInstance->glSSAOTexture);
		errorCode = glGetError();
		WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to create Frame Buffer");
		glBindTexture(GL_TEXTURE_2D, mSSAOInstance->glSSAOTexture);
		errorCode = glGetError();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2048, 2048, 0, GL_RGBA,
			GL_UNSIGNED_INT_8_8_8_8, nullptr);
		errorCode = glGetError();
		WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to bind or create\
				the immutable texture");

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, 
			GL_TEXTURE_2D, mSSAOInstance->glSSAOTexture, 0);
		WindowsUtil::Assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE,
			"Unable to complete the SSAO Frame Buffer Operation");


		//Creating Frame Buffer for the Blur Effect
		glGenFramebuffers(1, &mSSAOInstance->glSSAOBlurFrameBuffer);
		errorCode = glGetError();
		WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to \
			create Frame Buffer for the Blur pass");		
		glBindFramebuffer(GL_FRAMEBUFFER, mSSAOInstance->glSSAOBlurFrameBuffer);

		glGenTextures(1, &mSSAOInstance->glSSAOBlurTexture);
		errorCode = glGetError();
		WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to create Frame Buffer");
		glBindTexture(GL_TEXTURE_2D, mSSAOInstance->glSSAOBlurTexture);
		errorCode = glGetError();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2048, 2048, 0, GL_RGBA,
			GL_UNSIGNED_INT_8_8_8_8, nullptr);
		errorCode = glGetError();
		WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to bind or create\
				the immutable texture");

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
			GL_TEXTURE_2D, mSSAOInstance->glSSAOBlurFrameBuffer, 0);
		WindowsUtil::Assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE,
			"Unable to complete Blur SSAO Frame Buffer");
		

	}
}

Engine::Graphics::SSAO::SSAO()
{
	glNormalTexture = 0;
	glViewPositionTexture = 0;
	glDepthTexture = 0;
	glGeometryFrameBuffer = 0;
	glGeometryRenderBuffer = 0;

	glSSAOTexture = 0;
	glSSAOBlurTexture = 0;
	glSSAOFrameBuffer = 0;
	glSSAOBlurFrameBuffer = 0;
}




