#include "../Effect.h"
#include "../../Windows/WindowsFunctions.h"
#include <assert.h>

namespace Engine
{
	namespace Graphics
	{
		bool LoadAndAllocateShaderProgram(const char* i_path, void*& o_shader, size_t& o_size, std::string* o_errorMessage);
		
		struct sLogInfo
		{
			GLchar* memory;
			sLogInfo(const size_t i_size) { memory = reinterpret_cast<GLchar*>(malloc(i_size)); }
			~sLogInfo() { if (memory) free(memory); }
		};
	}
}

bool Engine::Graphics::Effect::LoadShaders()
{
	if (CreateProgram())
		return true;
	return false;
}

bool Engine::Graphics::Effect::setShaders()
{
	GraphicsSystem::setRenderState(*renderState);
	glUseProgram(s_programId);
	if (glGetError() == GL_NO_ERROR)
		return true;
	return false;
}

bool Engine::Graphics::Effect::CreateProgram()
{
	// Create a program
	{
		s_programId = glCreateProgram();
		const GLenum errorCode = glGetError();
		if (errorCode != GL_NO_ERROR)
		{
			std::stringstream errorMessage;
			errorMessage << "OpenGL failed to create a program: " <<
				reinterpret_cast<const char*>(gluErrorString(errorCode));
			WindowsUtil::Print(errorMessage.str());
			return false;
		}
		else if (s_programId == 0)
		{
			WindowsUtil::Print("OpenGL failed to create a program");
			return false;
		}

	}
	// Load and attach the shaders
	if (!LoadVertexShader())
	{
		return false;
	}
	if (!LoadFragmentShader())
	{
		return false;
	}
	// Link the program
	{
		glLinkProgram(s_programId);
		GLenum errorCode = glGetError();
		if (errorCode == GL_NO_ERROR)
		{
			// Get link info
			// (this won't be used unless linking fails
			// but it can be useful to look at when debugging)
			std::string linkInfo;
			{
				GLint infoSize;
				glGetProgramiv(s_programId, GL_INFO_LOG_LENGTH, &infoSize);
				errorCode = glGetError();
				if (errorCode == GL_NO_ERROR)
				{
					sLogInfo info(static_cast<size_t>(infoSize));
					GLsizei* dontReturnLength = NULL;
					glGetProgramInfoLog(s_programId, static_cast<GLsizei>(infoSize), dontReturnLength, info.memory);
					errorCode = glGetError();
					if (errorCode == GL_NO_ERROR)
					{
						linkInfo = info.memory;
					}
					else
					{
						std::stringstream errorMessage;
						errorMessage << "OpenGL failed to get link info of the program: " <<
							reinterpret_cast<const char*>(gluErrorString(errorCode));
						WindowsUtil::Print(errorMessage.str());
						return false;
					}
				}
				else
				{
					std::stringstream errorMessage;
					errorMessage << "OpenGL failed to get the length of the program link info: " <<
						reinterpret_cast<const char*>(gluErrorString(errorCode));
					WindowsUtil::Print(errorMessage.str());
					return false;
				}
			}
			// Check to see if there were link errors
			GLint didLinkingSucceed;
			{
				glGetProgramiv(s_programId, GL_LINK_STATUS, &didLinkingSucceed);
				errorCode = glGetError();
				if (errorCode == GL_NO_ERROR)
				{
					if (didLinkingSucceed == GL_FALSE)
					{
						std::stringstream errorMessage;
						errorMessage << "The program failed to link:\n" << linkInfo;
						WindowsUtil::Print(errorMessage.str());
						return false;
					}
					else
					{
						/*Program Linking finished - grabbing the uniform loacation from the shader*/
						if(!ReadEngineUniformsHandle())
						{
							std::stringstream errormesage;
							errormesage << "Unable to get the uniform loacation from the linked program. Please check the shader code";
							WindowsUtil::Print(errormesage.str());
						}
					}
				}
				else
				{
					std::stringstream errorMessage;
					errorMessage << "OpenGL failed to find out if linking of the program succeeded: " <<
						reinterpret_cast<const char*>(gluErrorString(errorCode));
					WindowsUtil::Print(errorMessage.str());
					return false;
				}
			}
		}
		else
		{
			std::stringstream errorMessage;
			errorMessage << "OpenGL failed to link the program: " <<
				reinterpret_cast<const char*>(gluErrorString(errorCode));
			WindowsUtil::Print(errorMessage.str());
			return false;
		}
	}

	return true;
}

bool Engine::Graphics::LoadAndAllocateShaderProgram(const char* i_path, void*& o_shader, size_t& o_size, std::string* o_errorMessage)
{
	bool wereThereErrors = false;

	// Load the shader source from disk
	o_shader = nullptr;
	HANDLE fileHandle = INVALID_HANDLE_VALUE;
	{
		// Open the file
		{
			const DWORD desiredAccess = FILE_GENERIC_READ;
			const DWORD otherProgramsCanStillReadTheFile = FILE_SHARE_READ;
			SECURITY_ATTRIBUTES* useDefaultSecurity = nullptr;
			const DWORD onlySucceedIfFileExists = OPEN_EXISTING;
			const DWORD useDefaultAttributes = FILE_ATTRIBUTE_NORMAL;
			const HANDLE dontUseTemplateFile = nullptr;
			fileHandle = CreateFile(i_path, desiredAccess, otherProgramsCanStillReadTheFile,
				useDefaultSecurity, onlySucceedIfFileExists, useDefaultAttributes, dontUseTemplateFile);
			if (fileHandle == INVALID_HANDLE_VALUE)
			{
				wereThereErrors = true;
				if (o_errorMessage)
				{
					std::string windowsErrorMessage = WindowsUtil::GetLastWindowsError();
					std::stringstream errorMessage;
					errorMessage << "Windows failed to open the shader file: " << windowsErrorMessage;
					*o_errorMessage = errorMessage.str();
				}
				goto OnExit;
			}
		}
		// Get the file's size
		{
			LARGE_INTEGER fileSize_integer;
			if (GetFileSizeEx(fileHandle, &fileSize_integer) != FALSE)
			{
				assert(fileSize_integer.QuadPart <= SIZE_MAX);
				o_size = static_cast<size_t>(fileSize_integer.QuadPart);
			}
			else
			{
				wereThereErrors = true;
				if (o_errorMessage)
				{
					std::string windowsErrorMessage = WindowsUtil::GetLastWindowsError();
					std::stringstream errorMessage;
					errorMessage << "Windows failed to get the size of shader: " << windowsErrorMessage;
					*o_errorMessage = errorMessage.str();
				}
				goto OnExit;
			}
			// Add an extra byte for a NULL terminator
			o_size += 1;
		}
		// Read the file's contents into temporary memory
		o_shader = malloc(o_size);
		if (o_shader)
		{
			DWORD bytesReadCount;
			OVERLAPPED* readSynchronously = nullptr;
			if (ReadFile(fileHandle, o_shader, o_size,
				&bytesReadCount, readSynchronously) == FALSE)
			{
				wereThereErrors = true;
				if (o_errorMessage)
				{
					std::string windowsErrorMessage = WindowsUtil::GetLastWindowsError();
					std::stringstream errorMessage;
					errorMessage << "Windows failed to read the contents of shader: " << windowsErrorMessage;
					*o_errorMessage = errorMessage.str();
				}
				goto OnExit;
			}
		}
		else
		{
			wereThereErrors = true;
			if (o_errorMessage)
			{
				std::stringstream errorMessage;
				errorMessage << "Failed to allocate " << o_size << " bytes to read in the shader program " << i_path;
				*o_errorMessage = errorMessage.str();
			}
			goto OnExit;
		}
		// Add the NULL terminator
		reinterpret_cast<char*>(o_shader)[o_size - 1] = '\0';
	}

OnExit:

	if (wereThereErrors && o_shader)
	{
		free(o_shader);
		o_shader = nullptr;
	}
	if (fileHandle != INVALID_HANDLE_VALUE)
	{
		if (CloseHandle(fileHandle) == FALSE)
		{
			if (!wereThereErrors && o_errorMessage)
			{
				std::string windowsError = WindowsUtil::GetLastWindowsError();
				std::stringstream errorMessage;
				errorMessage << "Windows failed to close the shader file handle: " << windowsError;
				*o_errorMessage = errorMessage.str();
			}
			wereThereErrors = true;
		}
		fileHandle = INVALID_HANDLE_VALUE;
	}

	return !wereThereErrors;
}

bool Engine::Graphics::Effect::LoadFragmentShader()
{
	// Verify that compiling shaders at run-time is supported
	{
		GLboolean isShaderCompilingSupported;
		glGetBooleanv(GL_SHADER_COMPILER, &isShaderCompilingSupported);
		if (!isShaderCompilingSupported)
		{
			WindowsUtil::Print("Compiling shaders at run-time isn't supported on this implementation (this should never happen)");
			return false;
		}
	}

	bool wereThereErrors = false;

	// Load the source code from file and set it into a shader
	GLuint fragmentShaderId = 0;
	void* shaderSource = nullptr;
	{
		// Load the shader source code
		size_t fileSize;
		{
			const char* sourceCodeFileName = fragmentShader.c_str(); //@Amit -TO-DO Need to change the file name
			std::string errorMessage;
			if (!LoadAndAllocateShaderProgram(sourceCodeFileName, shaderSource, fileSize, &errorMessage))
			{
				wereThereErrors = true;
				WindowsUtil::Print(errorMessage);
				goto OnExit;
			}
		}
		// Generate a shader
		fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
		{
			const GLenum errorCode = glGetError();
			if (errorCode != GL_NO_ERROR)
			{
				wereThereErrors = true;
				std::stringstream errorMessage;
				errorMessage << "OpenGL failed to get an unused fragment shader ID: " <<
					reinterpret_cast<const char*>(gluErrorString(errorCode));
				WindowsUtil::Print(errorMessage.str());
				goto OnExit;
			}
			else if (fragmentShaderId == 0)
			{
				wereThereErrors = true;
				WindowsUtil::Print("OpenGL failed to get an unused fragment shader ID");
				goto OnExit;
			}
		}
		// Set the source code into the shader
		{
			const GLsizei shaderSourceCount = 1; //@Amit - Changed to 2 from 1 - seems to refer to that shader in in the secon section in the file
			const GLchar* shaderSources[] =
			{
				 reinterpret_cast<GLchar*>(shaderSource)
			};

			const GLint* sourcesAreNullTerminated = nullptr;
			//const GLint length = static_cast<GLuint>(fileSize);

			glShaderSource(fragmentShaderId, shaderSourceCount, shaderSources, sourcesAreNullTerminated); //@Amit - changed here in teh last parameter(from length to sourcesAreNullTerminated)
			const GLenum errorCode = glGetError();
			if (errorCode != GL_NO_ERROR)
			{
				wereThereErrors = true;
				std::stringstream errorMessage;
				errorMessage << "OpenGL failed to set the fragment shader source code: " <<
					reinterpret_cast<const char*>(gluErrorString(errorCode));
				WindowsUtil::Print(errorMessage.str());
				goto OnExit;
			}
		}
	}
	// Compile the shader source code
	{
		glCompileShader(fragmentShaderId);
		GLenum errorCode = glGetError();
		if (errorCode == GL_NO_ERROR)
		{
			// Get compilation info
			// (this won't be used unless compilation fails
			// but it can be useful to look at when debugging)
			std::string compilationInfo;
			{
				GLint infoSize;
				glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &infoSize);
				errorCode = glGetError();
				if (errorCode == GL_NO_ERROR)
				{
					sLogInfo info(static_cast<size_t>(infoSize));
					GLsizei* dontReturnLength = nullptr;
					glGetShaderInfoLog(fragmentShaderId, static_cast<GLsizei>(infoSize), dontReturnLength, info.memory);
					errorCode = glGetError();
					if (errorCode == GL_NO_ERROR)
					{
						compilationInfo = info.memory;
					}
					else
					{
						wereThereErrors = true;
						std::stringstream errorMessage;
						errorMessage << "OpenGL failed to get compilation info of the fragment shader source code: " <<
							reinterpret_cast<const char*>(gluErrorString(errorCode));
						WindowsUtil::Print(errorMessage.str());
						goto OnExit;
					}
				}
				else
				{
					wereThereErrors = true;
					std::stringstream errorMessage;
					errorMessage << "OpenGL failed to get the length of the fragment shader compilation info: " <<
						reinterpret_cast<const char*>(gluErrorString(errorCode));
					WindowsUtil::Print(errorMessage.str());
					goto OnExit;
				}
			}
			// Check to see if there were compilation errors
			GLint didCompilationSucceed;
			{
				glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &didCompilationSucceed);
				errorCode = glGetError();
				if (errorCode == GL_NO_ERROR)
				{
					if (didCompilationSucceed == GL_FALSE)
					{
						wereThereErrors = true;
						std::stringstream errorMessage;
						errorMessage << "The fragment shader failed to compile:\n" << compilationInfo;
						WindowsUtil::Print(errorMessage.str());
						goto OnExit;
					}
				}
				else
				{
					wereThereErrors = true;
					std::stringstream errorMessage;
					errorMessage << "OpenGL failed to find out if compilation of the fragment shader source code succeeded: " <<
						reinterpret_cast<const char*>(gluErrorString(errorCode));
					WindowsUtil::Print(errorMessage.str());
					goto OnExit;
				}
			}
		}
		else
		{
			wereThereErrors = true;
			std::stringstream errorMessage;
			errorMessage << "OpenGL failed to compile the fragment shader source code: " <<
				reinterpret_cast<const char*>(gluErrorString(errorCode));
			WindowsUtil::Print(errorMessage.str());
			goto OnExit;
		}
	}
	// Attach the shader to the program
	{
		glAttachShader(s_programId, fragmentShaderId);
		const GLenum errorCode = glGetError();
		if (errorCode != GL_NO_ERROR)
		{
			wereThereErrors = true;
			std::stringstream errorMessage;
			errorMessage << "OpenGL failed to attach the fragment shader to the program: " <<
				reinterpret_cast<const char*>(gluErrorString(errorCode));
			WindowsUtil::Print(errorMessage.str());
			goto OnExit;
		}
	}

OnExit:

	if (fragmentShaderId != 0)
	{
		// Even if the shader was successfully compiled
		// once it has been attached to the program we can (and should) delete our reference to it
		// (any associated memory that OpenGL has allocated internally will be freed
		// once the program is deleted)
		glDeleteShader(fragmentShaderId);
		const GLenum errorCode = glGetError();
		if (errorCode != GL_NO_ERROR)
		{
			std::stringstream errorMessage;
			errorMessage << "OpenGL failed to delete the fragment shader ID: " <<
				reinterpret_cast<const char*>(gluErrorString(errorCode));
			WindowsUtil::Print(errorMessage.str());
		}
		fragmentShaderId = 0;
	}
	if (shaderSource != nullptr)
	{
		free(shaderSource);
		shaderSource = nullptr;
	}

	return !wereThereErrors;
}

bool Engine::Graphics::Effect::LoadVertexShader()
{
	// Verify that compiling shaders at run-time is supported
	{
		GLboolean isShaderCompilingSupported;
		glGetBooleanv(GL_SHADER_COMPILER, &isShaderCompilingSupported);
		if (!isShaderCompilingSupported)
		{
			WindowsUtil::Print("Compiling shaders at run-time isn't supported on this implementation (this should never happen)");
			return false;
		}
	}

	bool wereThereErrors = false;

	// Load the source code from file and set it into a shader
	GLuint vertexShaderId = 0;
	void* shaderSource = nullptr;
	{
		// Load the shader source code
		size_t fileSize;
		{
			const char* sourceCodeFileName = vertexShader.c_str();  //@Amit To do - Need to change the file name
			std::string errorMessage;
			if (!LoadAndAllocateShaderProgram(sourceCodeFileName, shaderSource, fileSize, &errorMessage))
			{
				wereThereErrors = true;
				WindowsUtil::Print(errorMessage);
				goto OnExit;
			}
		}
		// Generate a shader
		vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
		{
			const GLenum errorCode = glGetError();
			if (errorCode != GL_NO_ERROR)
			{
				wereThereErrors = true;
				std::stringstream errorMessage;
				errorMessage << "OpenGL failed to get an unused vertex shader ID: " <<
					reinterpret_cast<const char*>(gluErrorString(errorCode));
				WindowsUtil::Print(errorMessage.str());
				goto OnExit;
			}
			else if (vertexShaderId == 0)
			{
				wereThereErrors = true;
				WindowsUtil::Print("OpenGL failed to get an unused vertex shader ID");
				goto OnExit;
			}
		}
		// Set the source code into the shader
		{
			const GLsizei shaderSourceCount = 1;  //@Amit - seems it refers that the shader code is in the second section
			const GLchar* shaderSources[] =
			{
				//@Amit - like a string which will look up in the shader file
				reinterpret_cast<GLchar*>(shaderSource)
			};
			const GLint* sourcesAreNullTerminated = nullptr;
			//const GLint length = static_cast<GLuint>(fileSize);			

			glShaderSource(vertexShaderId, shaderSourceCount, shaderSources, sourcesAreNullTerminated);
			const GLenum errorCode = glGetError();
			if (errorCode != GL_NO_ERROR)
			{
				wereThereErrors = true;
				std::stringstream errorMessage;
				errorMessage << "OpenGL failed to set the vertex shader source code: " <<
					reinterpret_cast<const char*>(gluErrorString(errorCode));
				WindowsUtil::Print(errorMessage.str());
				goto OnExit;
			}
		}
	}
	// Compile the shader source code
	{
		glCompileShader(vertexShaderId);
		GLenum errorCode = glGetError();
		if (errorCode == GL_NO_ERROR)
		{
			// Get compilation info
			// (this won't be used unless compilation fails
			// but it can be useful to look at when debugging)
			std::string compilationInfo;
			{
				GLint infoSize;
				glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &infoSize);
				errorCode = glGetError();
				if (errorCode == GL_NO_ERROR)
				{
					sLogInfo info(static_cast<size_t>(infoSize));
					GLsizei* dontReturnLength = nullptr;
					glGetShaderInfoLog(vertexShaderId, static_cast<GLsizei>(infoSize), dontReturnLength, info.memory);
					errorCode = glGetError();
					if (errorCode == GL_NO_ERROR)
					{
						compilationInfo = info.memory;
					}
					else
					{
						wereThereErrors = true;
						std::stringstream errorMessage;
						errorMessage << "OpenGL failed to get compilation info of the vertex shader source code: " <<
							reinterpret_cast<const char*>(gluErrorString(errorCode));
						WindowsUtil::Print(errorMessage.str());
						goto OnExit;
					}
				}
				else
				{
					wereThereErrors = true;
					std::stringstream errorMessage;
					errorMessage << "OpenGL failed to get the length of the vertex shader compilation info: " <<
						reinterpret_cast<const char*>(gluErrorString(errorCode));
					WindowsUtil::Print(errorMessage.str());
					goto OnExit;
				}
			}
			// Check to see if there were compilation errors
			GLint didCompilationSucceed;
			{
				glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &didCompilationSucceed);
				errorCode = glGetError();
				if (errorCode == GL_NO_ERROR)
				{
					if (didCompilationSucceed == GL_FALSE)
					{
						wereThereErrors = true;
						std::stringstream errorMessage;
						errorMessage << "The vertex shader failed to compile:\n" << compilationInfo;
						WindowsUtil::Print(errorMessage.str());
						goto OnExit;
					}
				}
				else
				{
					wereThereErrors = true;
					std::stringstream errorMessage;
					errorMessage << "OpenGL failed to find out if compilation of the vertex shader source code succeeded: " <<
						reinterpret_cast<const char*>(gluErrorString(errorCode));
					WindowsUtil::Print(errorMessage.str());
					goto OnExit;
				}
			}
		}
		else
		{
			wereThereErrors = true;
			std::stringstream errorMessage;
			errorMessage << "OpenGL failed to compile the vertex shader source code: " <<
				reinterpret_cast<const char*>(gluErrorString(errorCode));
			WindowsUtil::Print(errorMessage.str());
			goto OnExit;
		}
	}
	// Attach the shader to the program
	{
		glAttachShader(s_programId, vertexShaderId);
		const GLenum errorCode = glGetError();
		if (errorCode != GL_NO_ERROR)
		{
			wereThereErrors = true;
			std::stringstream errorMessage;
			errorMessage << "OpenGL failed to attach the vertex shader to the program: " <<
				reinterpret_cast<const char*>(gluErrorString(errorCode));
			WindowsUtil::Print(errorMessage.str());
			goto OnExit;
		}
	}

OnExit:

	if (vertexShaderId != 0)
	{
		// Even if the shader was successfully compiled
		// once it has been attached to the program we can (and should) delete our reference to it
		// (any associated memory that OpenGL has allocated internally will be freed
		// once the program is deleted)
		glDeleteShader(vertexShaderId);
		const GLenum errorCode = glGetError();
		if (errorCode != GL_NO_ERROR)
		{
			std::stringstream errorMessage;
			errorMessage << "OpenGL failed to delete the vertex shader ID: " <<
				reinterpret_cast<const char*>(gluErrorString(errorCode));
			WindowsUtil::Print(errorMessage.str());
		}
		vertexShaderId = 0;
	}
	if (shaderSource != nullptr)
	{
		free(shaderSource);
		shaderSource = nullptr;
	}

	return !wereThereErrors;
}

Engine::Graphics::Effect::Effect(std::string i_effectFileName)
{
	s_programId = 0;
	s_uniformLocalToWorld = 0;
	s_uniformWorldToView = 0;
	s_uniformViewToScreen = 0;
	effectName = i_effectFileName;
	renderState = new uint8_t;
}

Engine::Graphics::Effect::~Effect()
{
	if (s_programId != 0)
	{
		glDeleteProgram(s_programId);
		const GLenum errorCode = glGetError();
		if (errorCode != GL_NO_ERROR)
		{
			std::stringstream errorMessage;
			errorMessage << "OpenGL failed to delete the program: " <<
				reinterpret_cast<const char*>(gluErrorString(errorCode));
			WindowsUtil::Print(errorMessage.str());
		}
		s_programId = 0;
	}
	delete renderState;
}

void Engine::Graphics::Effect::setEngineUniformValue(Transformation i_gameObject, 
	Transformation i_camera, 
	float i_fieldOfView,
	float i_aspectRatio)
{

	/*GLfloat *temp = new GLfloat[2];
	temp[0] = i_offsetPosition.x;
	temp[1] = i_offsetPosition.y;
	glUniform2fv(s_uniformPositionOffset, 1, temp);*/
	
	const GLboolean dontTranspose = false;
	const GLsizei uniformCountToSet = 1;
	m_uniforms.calculateUniforms(i_gameObject, i_camera, i_fieldOfView, i_aspectRatio);
	glUniformMatrix4fv(s_uniformLocalToWorld, uniformCountToSet, dontTranspose, reinterpret_cast<const GLfloat*>(&m_uniforms.g_transform_localToWorld));
	glUniformMatrix4fv(s_uniformWorldToView, uniformCountToSet, dontTranspose, reinterpret_cast<const GLfloat*>(&m_uniforms.g_transform_worldToView));
	glUniformMatrix4fv(s_uniformViewToScreen, uniformCountToSet, dontTranspose, reinterpret_cast<const GLfloat*>(&m_uniforms.g_transform_viewToScreen));
	const GLenum errorCode = glGetError();
	if(!(errorCode == GL_NO_ERROR))
	{
		std::stringstream errormessage;
		errormessage << "Unable to set the position offset";
		WindowsUtil::Print(errormessage.str());
	}
	//delete temp;
}


void Engine::Graphics::Effect::setMaterialUniformValue(char* i_uniformName, MaterialUniform i_materialUniform)
{
	switch(i_materialUniform.valCount)
	{
	case One:
		glUniform1fv(i_materialUniform.Handle,1, i_materialUniform.values);
		break;
	case Two:
		glUniform2fv(i_materialUniform.Handle,1, i_materialUniform.values);
		break;
	case Three:
		glUniform3fv(i_materialUniform.Handle,1, i_materialUniform.values);
		break;
	case Four:
		glUniform4fv(i_materialUniform.Handle,1, i_materialUniform.values);
		break;
	case Zero:
		break;
	}

	const GLenum errorCode = glGetError();
	if (!(errorCode == GL_NO_ERROR))
	{
		std::stringstream errormessage;
		errormessage << "Unable to set the position offset";
		WindowsUtil::Print(errormessage.str());
	}
}


Engine::Graphics::UniformHandle Engine::Graphics::Effect::getUniformHandle(char* i_uniformName, ShaderType)
{
	UniformHandle handle = glGetUniformLocation(s_programId, i_uniformName);
	if (handle == -1)
	{
		std::stringstream errormessage;
		errormessage << "Unable to set the Material Uniforms";
		WindowsUtil::Print(errormessage.str());
	}

	return handle;
}

Engine::Graphics::SamplerID Engine::Graphics::Effect::getSamplerID(UniformHandle i_uniformHandle, ShaderType)
{
	SamplerID sampleId = i_uniformHandle;
	return sampleId;
}

void Engine::Graphics::Effect::setTextureUniform(TextureResource i_textureResource,
	SamplerID i_TextureSamplerID, int i_textureUnit)
{
	glActiveTexture(GL_TEXTURE0 + i_textureUnit);
	GLenum errorCode = glGetError();
	if ((errorCode == GL_NO_ERROR))
	{
		glBindTexture(GL_TEXTURE_2D, i_textureResource); 
		errorCode = glGetError();
		if ((errorCode == GL_NO_ERROR))
		{
			glUniform1i(i_TextureSamplerID, i_textureUnit); 
			errorCode = glGetError();
			if(!errorCode == GL_NO_ERROR)
			{
				std::stringstream errormessage;
				errormessage << "Unable to set the texture Uniform";
				WindowsUtil::Print(errormessage.str());
			}
		}
		else
		{
			std::stringstream errormessage;
			errormessage << "Unable to bind the texture";
			WindowsUtil::Print(errormessage.str());
		}
	}
	else
	{
		std::stringstream errormessage;
		errormessage << "Unable to active texture Uniform";
		WindowsUtil::Print(errormessage.str());
	}	
}






