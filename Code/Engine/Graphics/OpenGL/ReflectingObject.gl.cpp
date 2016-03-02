#include "../ReflectingObject.h"
#include <sstream>
#include "../../../Externals/OpenGLExtensions/OpenGlExtensions.h"
#include "../../../Engine/Core/EngineCore/WindowingSystem/WindowsProgram.h"
#include "../../Windows/WindowsFunctions.h"
#include "../../Core/EngineCore/Objects/Camera.h"
#include "../../Core/EngineCore/Objects/Scene.h"

Engine::Graphics::ReflectingObject::ReflectingObject()
{
	shaderType = Fragment;
	texture = 0;
	textureSamplerID = -1;
	textureType = TEXTURE_CUBE;
}


void Engine::Graphics::ReflectingObject::generateCubeMap()
{
	std::stringstream errormessage;
	if(init())
	{
		SharedPointer<Engine::Scene> currentScene =
			Engine::Scene::getRenderableScene();
		SharedPointer<Engine::Camera> previousCamera =
			currentScene->getActiveCamera();
		
		//SharedPointer<>
	}
	else
	{
		errormessage << "Unable to initialize the texture";
		MessageBox(nullptr, errormessage.str().c_str(), nullptr, MB_OK);
	}
}

bool Engine::Graphics::ReflectingObject::init()
{
	GLuint width = Engine::Windows::WindowingSystem::getWindowingSystem()->getWindowWidth();
	GLuint height = Engine::Windows::WindowingSystem::getWindowingSystem()->getWindowHeight();
	bool wereThereErrors = false;;
	//cretating textures
	{
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
		GLenum errorCode;
		errorCode = glGetError();
		if (errorCode != GL_NO_ERROR)
		{
			for (int i = 0; i < 6; i++)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
				WindowsUtil::Assert(glGetError() == GL_NO_ERROR, "Unable to create immutable texture");
			}		
		}
		else
			wereThereErrors = true;
	}
	
	//Creating the render buffers
	{
		glGenRenderbuffers(6, renderBuffer);
		for (int i = 0; i < 6; i++)
		{
			glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer[i]);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
			wereThereErrors |= glGetError() == GL_NO_ERROR ? false : true;
			WindowsUtil::Assert(wereThereErrors, "Unable to bind or create the buffer storage for the render buffer");
		}
	}
	
	//Creating Frame Buffers
	{
		glGenFramebuffers(6, frameBuffer);
		for (int i = 0; i < 6; i++)
		{
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffer[i]);
			glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, 
				GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, texture, 0);
			wereThereErrors |= glGetError() == GL_NO_ERROR ? false : true;
			WindowsUtil::Assert(wereThereErrors, "Unable to bind or create the buffer storage for the frame buffer");
		}
	}	
	return !wereThereErrors;
}


void Engine::Graphics::ReflectingObject::draw(bool)
{
	
}


