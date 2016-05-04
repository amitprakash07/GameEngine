#include "SSAO.h"
#include "../Windows/WindowsFunctions.h"
#include "../Core/EngineCore/Objects/Scene.h"
#include "../Core/EngineCore/EngineCore.h"
#include <ctime>

Engine::SharedPointer<Engine::Graphics::SSAO>
		Engine::Graphics::SSAO::mSSAOInstance;

void Engine::Graphics::SSAO::GenerateGBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, mSSAOInstance->glGeometryFrameBuffer);	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, mSSAOInstance->glNormalTexture);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	

	glBindTexture(GL_TEXTURE_2D, mSSAOInstance->glViewPositionTexture);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	glBindTexture(GL_TEXTURE_2D, mSSAOInstance->glColorTexture);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);		
}

unsigned Engine::Graphics::SSAO::GetSSAOBlurTexture()
{
	return mSSAOInstance->glSSAOBlurTexture;
}

unsigned Engine::Graphics::SSAO::GetSSAOTexture()
{
	return mSSAOInstance->glSSAOTexture;
}

void Engine::Graphics::SSAO::InitializeSSAO(std::string i_SSAOEffectFileName)
{
	GLenum errorCode;
	if(mSSAOInstance.isNull())
	{
		SharedPointer<SSAO> tempSSAO = SharedPointer<SSAO>(
			new SSAO(), "SSAO");

		mSSAOInstance = tempSSAO;
		mSSAOInstance->bufferAttachment[0] = GL_COLOR_ATTACHMENT0;
		mSSAOInstance->bufferAttachment[1] = GL_COLOR_ATTACHMENT1;
		mSSAOInstance->bufferAttachment[2] = GL_COLOR_ATTACHMENT2;
		mSSAOInstance->bufferAttachment[3] = GL_DEPTH_ATTACHMENT;	
		
		i_SSAOEffectFileName =
			Engine::EngineCore::getEffectFolderPath() + i_SSAOEffectFileName;


		/*iGeometryMaterialFileName = 
			Engine::EngineCore::getMaterialFolderPath() + iGeometryMaterialFileName;
		iSSAOMAterialFileName = 
			Engine::EngineCore::getMaterialFolderPath() + iSSAOMAterialFileName;
		iBlurMaterial =
			Engine::EngineCore::getMaterialFolderPath() + iBlurMaterial;*/

		/*Material::addMaterialToList(iGeometryMaterialFileName.c_str());
		Material::addMaterialToList(iSSAOMAterialFileName.c_str());
		Material::addMaterialToList(iBlurMaterial.c_str());*/
		//TestBuffers
		//{
		//	glGenFramebuffers(1, &mSSAOInstance->testFrameBuffer);
		//	errorCode = glGetError();
		//	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to \
		//	create Frame Buffer for the G-Buffer");
		//	glBindFramebuffer(GL_FRAMEBUFFER, mSSAOInstance->testFrameBuffer);
		//	errorCode = glGetError();
		//	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to \
		//	create Frame Buffer for the G-Buffer");

		//	glGenTextures(1, &mSSAOInstance->testTexture);
		//	errorCode = glGetError();
		//	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to create Frame Buffer");
		//	glBindTexture(GL_TEXTURE_2D, mSSAOInstance->testTexture);
		//	errorCode = glGetError();
		//	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to bind\
		//		the immutable texture");
		//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2048, 2048, 0, GL_RGBA,
		//		GL_UNSIGNED_INT_8_8_8_8, nullptr);
		//	errorCode = glGetError();
		//	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to create\
		//		the immutable texture");

		//	//Attaching the normal texture - color 0
		//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
		//		GL_TEXTURE_2D, mSSAOInstance->testTexture, 0);
		//	errorCode = glGetError();
		//	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to bind or create\
		//		the immutable texture");

		//	glDrawBuffer(GL_COLOR_ATTACHMENT0);
		//}


		//Creating FrameBUffers for geometry pass  i.e. G-Buffer
		glGenFramebuffers(1, &mSSAOInstance->glGeometryFrameBuffer);
		errorCode = glGetError();
		WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to \
			create Frame Buffer for the G-Buffer");
		glBindFramebuffer(GL_FRAMEBUFFER, mSSAOInstance->glGeometryFrameBuffer);
		errorCode = glGetError();
		WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to \
			create Frame Buffer for the G-Buffer");

		//Creating txtures for the G-Buffer

		//Normal Texture
		{
			glGenTextures(1, &mSSAOInstance->glNormalTexture);
			errorCode = glGetError();
			WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to create Frame Buffer");
			glBindTexture(GL_TEXTURE_2D, mSSAOInstance->glNormalTexture);
			errorCode = glGetError();
			WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to bind\
				the immutable texture");
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2048, 2048, 0, GL_RGBA,
				GL_UNSIGNED_INT_8_8_8_8, nullptr);
			errorCode = glGetError();
			WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to create\
				the immutable texture");

			//Attaching the normal texture - color 0
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
				GL_TEXTURE_2D, mSSAOInstance->glNormalTexture, 0);
			errorCode = glGetError();
			WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to bind or create\
				the immutable texture");
		}

		{
			//view position texture
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
			errorCode = glGetError();
			WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to bind or create\
				the immutable texture");
		}
		
		{
			//color texture - 
			glGenTextures(1, &mSSAOInstance->glColorTexture);
			errorCode = glGetError();
			WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to create Frame Buffer");
			glBindTexture(GL_TEXTURE_2D, mSSAOInstance->glColorTexture);
			errorCode = glGetError();
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2048, 2048, 0, GL_RGBA,
				GL_UNSIGNED_INT_8_8_8_8, nullptr);
			errorCode = glGetError();
			WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to bind or create\
				the immutable texture");

			//Attaching the view texture - color 1
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2,
				GL_TEXTURE_2D, mSSAOInstance->glColorTexture, 0);
			errorCode = glGetError();
			WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to bind or create\
				the immutable texture");
		}

		{
			//Creating the Depth Texture
			glGenTextures(1, &mSSAOInstance->glDepthTexture);
			errorCode = glGetError();
			WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to create Frame Buffer");
			glBindTexture(GL_TEXTURE_2D, mSSAOInstance->glDepthTexture);
			errorCode = glGetError();
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 2048, 2048, 0, GL_DEPTH_COMPONENT,
				GL_FLOAT, nullptr);
			errorCode = glGetError();
			WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to bind or create\
				the immutable texture");

			//Attaching the depth texture - color 0
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
				GL_TEXTURE_2D, mSSAOInstance->glDepthTexture, 0);
			WindowsUtil::Assert((errorCode= glGetError()) == GL_NO_ERROR, "Unable to store the texture\
				the immutable texture");
		}

		glDrawBuffers(3, mSSAOInstance->bufferAttachment);
		errorCode = glGetError();


		/*glGenRenderbuffers(1, &mSSAOInstance->glGeometryRenderBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, mSSAOInstance->glGeometryRenderBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER,
			GL_DEPTH_COMPONENT24, 2048, 2048);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
			GL_RENDERBUFFER, mSSAOInstance->glGeometryRenderBuffer);

		WindowsUtil::Assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE,
			"Unable to complete frame buffer operation");*/

		//Creating Frame Buffer for the SSAO shader
		//glGenFramebuffers(1, &mSSAOInstance->glSSAOFrameBuffer);
		//errorCode = glGetError();
		//WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to \
		//	create Frame Buffer for the SSAO Pass");
		//glBindFramebuffer(GL_FRAMEBUFFER, mSSAOInstance->glSSAOFrameBuffer);

		//glGenTextures(1, &mSSAOInstance->glSSAOTexture);
		//errorCode = glGetError();
		//WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to create Frame Buffer");
		//glBindTexture(GL_TEXTURE_2D, mSSAOInstance->glSSAOTexture);
		//errorCode = glGetError();
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2048, 2048, 0, GL_RGBA,
		//	GL_UNSIGNED_INT_8_8_8_8, nullptr);
		//errorCode = glGetError();
		//WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to bind or create\
		//		the immutable texture");

		//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, 
		//	GL_TEXTURE_2D, mSSAOInstance->glSSAOTexture, 0);
		//WindowsUtil::Assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE,
		//	"Unable to complete the SSAO Frame Buffer Operation");
		
		////Creating Frame Buffer for the Blur Effect
		//glGenFramebuffers(1, &mSSAOInstance->glSSAOBlurFrameBuffer);
		//errorCode = glGetError();
		//WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to \
		//	create Frame Buffer for the Blur pass");		
		//glBindFramebuffer(GL_FRAMEBUFFER, mSSAOInstance->glSSAOBlurFrameBuffer);

		//glGenTextures(1, &mSSAOInstance->glSSAOBlurTexture);
		//errorCode = glGetError();
		//WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to create Frame Buffer");
		//glBindTexture(GL_TEXTURE_2D, mSSAOInstance->glSSAOBlurTexture);
		//errorCode = glGetError();
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2048, 2048, 0, GL_RGBA,
		//	GL_UNSIGNED_INT_8_8_8_8, nullptr);
		//errorCode = glGetError();
		//WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to bind or create\
		//		the immutable texture");

		//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
		//	GL_TEXTURE_2D, mSSAOInstance->glSSAOBlurFrameBuffer, 0);
		//WindowsUtil::Assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE,
		//	"Unable to complete Blur SSAO Frame Buffer");		


		mSSAOInstance->mSSAOEffectFile = i_SSAOEffectFileName;

		Effect::addEffectToList(mSSAOInstance->mSSAOEffectFile);
		SharedPointer<Effect> ssaoEffect =
			Effect::getEffect(mSSAOInstance->mSSAOEffectFile);
		mSSAOInstance->SSAOProgram = ssaoEffect->GetProgramID();
		

		//UniformLocations
		mSSAOInstance->mRadius = glGetUniformLocation(mSSAOInstance->SSAOProgram, "radius");
		errorCode = glGetError();
		WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to \
			create Frame Buffer for the G-Buffer");

		mSSAOInstance->mSamplePointCount = glGetUniformLocation(mSSAOInstance->SSAOProgram, "sampleCount");
		errorCode = glGetError();
		WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to \
			create Frame Buffer for the G-Buffer");

		mSSAOInstance->mProjectionMatrix = glGetUniformLocation(
			mSSAOInstance->SSAOProgram, "g_transform_viewToScreen");
		errorCode = glGetError();
		WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to \
			create Frame Buffer for the G-Buffer");

		glGenVertexArrays(1, &mSSAOInstance->mVertexArray);
		errorCode = glGetError();
		WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to \
			create Frame Buffer for the G-Buffer");

		glBindVertexArray(mSSAOInstance->mVertexArray);
		errorCode = glGetError();
		WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to \
			create Frame Buffer for the G-Buffer");
		//Calculate Sample Points
		//To Do

		srand(time(nullptr));
		
		for (unsigned int i = 0; i < 256; i++)
		{
			mSSAOInstance->mSamplePointsData.point[i].x = rand()% RAND_MAX * 2.0f - 1.0f;
			mSSAOInstance->mSamplePointsData.point[i].y = rand() % RAND_MAX * 2.0f - 1.0f;
			mSSAOInstance->mSamplePointsData.point[i].z = rand() % RAND_MAX; //Z should be between 0 and 1
			mSSAOInstance->mSamplePointsData.point[i].w = 0.0f;			
			mSSAOInstance->mSamplePointsData.point[i].Normalize();

			float scale = static_cast<float>(i) / 256.0f;

			auto lerpedScale = [](float i_A, float i_B, float iScale)->float
			{
				return (i_A + (iScale) * (i_B - i_A));
			};

			mSSAOInstance->mSamplePointsData.point[i] *= lerpedScale(0.1f, 1.0f, scale * scale);

			mSSAOInstance->mSamplePointsData.randomVectors[i].x = rand() % RAND_MAX;
			mSSAOInstance->mSamplePointsData.randomVectors[i].y = rand() % RAND_MAX;
			mSSAOInstance->mSamplePointsData.randomVectors[i].z = rand() % RAND_MAX;
			mSSAOInstance->mSamplePointsData.randomVectors[i].w = rand() % RAND_MAX;
		}	
			
		

		glGenBuffers(1, &mSSAOInstance->samplePointsBuffer);
		errorCode = glGetError();
		WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to \
			create Frame Buffer for the G-Buffer");

		glBindBuffer(GL_UNIFORM_BUFFER, mSSAOInstance->samplePointsBuffer);
		errorCode = glGetError();
		WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to \
			create Frame Buffer for the G-Buffer");

		glBufferData(GL_UNIFORM_BUFFER,
			sizeof(samplePoints),
			&mSSAOInstance->mSamplePointsData,
			GL_STATIC_DRAW);
		errorCode = glGetError();
		WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to \
			create Frame Buffer for the G-Buffer");
	}
}

Engine::Graphics::SSAO::SSAO()
{
	glNormalTexture = 0;
	glViewPositionTexture = 0;
	glDepthTexture = 0;
	glColorTexture = 0;
	glGeometryFrameBuffer = 0;
	//glGeometryRenderBuffer = 0;

	glSSAOTexture = 0;
	glSSAOBlurTexture = 0;
	glSSAOFrameBuffer = 0;
	glSSAOBlurFrameBuffer = 0;
	mVaryingRadius = 5.0f;
	mSampleCount = 256;
}

void Engine::Graphics::SSAO::RunSSAO()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//glBindFramebuffer(GL_FRAMEBUFFER, mSSAOInstance->testFrameBuffer);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	GLenum errorCode;
	SharedPointer<Effect> ssaoEffect =
		Effect::getEffect(mSSAOInstance->mSSAOEffectFile);
	ssaoEffect->setShaders();
	
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, mSSAOInstance->samplePointsBuffer);

	glUniform1ui(mSSAOInstance->mSamplePointCount, mSSAOInstance->mSampleCount);
	errorCode = glGetError();
	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to \
			create Frame Buffer for the G-Buffer");

	glUniform1f(mSSAOInstance->mRadius, mSSAOInstance->mVaryingRadius);
	errorCode = glGetError();
	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to \
			create Frame Buffer for the G-Buffer");

	SharedPointer<Camera> activeCamera = Scene::getRenderableScene()->getActiveCamera();
	Math::Matrix4x4 projectionMatrix =
		Math::Matrix4x4::CreateViewToScreenTransform(
			activeCamera->getFieldOfView(),
			activeCamera->getAspectRatio(),
			activeCamera->getNearPlane(),
			activeCamera->getFarPlane());
	glUniformMatrix4fv(mSSAOInstance->mProjectionMatrix,
		1, GL_FALSE, reinterpret_cast<float*>(&projectionMatrix));
	errorCode = glGetError();
	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to \
			create Frame Buffer for the G-Buffer");


	glActiveTexture(GL_TEXTURE0);
	errorCode = glGetError();
	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to \
			create Frame Buffer for the G-Buffer");

	glBindTexture(GL_TEXTURE_2D, mSSAOInstance->glNormalTexture);
	errorCode = glGetError();
	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to \
			create Frame Buffer for the G-Buffer");

	glActiveTexture(GL_TEXTURE1);
	errorCode = glGetError();
	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to \
			create Frame Buffer for the G-Buffer");

	glBindTexture(GL_TEXTURE_2D, mSSAOInstance->glViewPositionTexture);
	errorCode = glGetError();
	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to \
			create Frame Buffer for the G-Buffer");

	glActiveTexture(GL_TEXTURE2);
	errorCode = glGetError();
	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to \
			create Frame Buffer for the G-Buffer");

	glBindTexture(GL_TEXTURE_2D, mSSAOInstance->glDepthTexture);
	errorCode = glGetError();
	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to \
			create Frame Buffer for the G-Buffer");

	glActiveTexture(GL_TEXTURE3);
	errorCode = glGetError();
	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to \
			create Frame Buffer for the G-Buffer");

	glBindTexture(GL_TEXTURE_2D, mSSAOInstance->glColorTexture);
	errorCode = glGetError();
	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to \
			create Frame Buffer for the G-Buffer");

	glDisable(GL_DEPTH_TEST);
	errorCode = glGetError();
	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to \
			create Frame Buffer for the G-Buffer");

	glBindVertexArray(mSSAOInstance->mVertexArray);
	errorCode = glGetError();
	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to \
			create Frame Buffer for the G-Buffer");

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	errorCode = glGetError();
	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to \
			create Frame Buffer for the G-Buffer");
}




