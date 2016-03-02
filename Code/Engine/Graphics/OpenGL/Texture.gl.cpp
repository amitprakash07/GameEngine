#include "../Texture.h"
#include "../../Windows/WindowsFunctions.h"
#include <algorithm>

Engine::Graphics::Texture::Texture()
{
	//textureName = nullptr;
	texture = -1;
	//effectName = nullptr;
	shaderType = Fragment;
	textureSamplerID = -1;
	textureType = TEXTURE_2D;
	//samplerName = nullptr;
}

Engine::Graphics::Texture::Texture(char* i_effectName,
	char* i_textureName,
	char* i_samplerName,
	ShaderType iShaderType)
{
	if (i_textureName)
	{
		textureName = i_textureName;
		/*size_t length = strlen(i_textureName);
		textureName = new char[length];
		memcpy(textureName, i_textureName, length);*/
	}
	if (i_effectName)
	{
		effectName = i_effectName;
		//size_t length = strlen(i_effectName);
		//effectName = reinterpret_cast<char*>(malloc(length));// new char[length];
		//memcpy(effectName, i_effectName, length);
	}
	if (i_samplerName)
	{
		samplerName = i_samplerName;
		/*size_t length = strlen(i_samplerName);
		samplerName = new char[length];
		memcpy(samplerName, i_samplerName, length);*/
	}
	texture = -1;
	textureSamplerID = -1;
	shaderType = iShaderType;
	textureType = TEXTURE_2D;
}

bool Engine::Graphics::Texture::loadTexture()
{
	bool wereThereErrors = false;
	HANDLE fileHandle = INVALID_HANDLE_VALUE;
	void* fileContents = nullptr;
	texture = 0;
	std::string *o_errorMessage = new std::string;

	// Open the texture file
	{
		const DWORD desiredAccess = FILE_GENERIC_READ;
		const DWORD otherProgramsCanStillReadTheFile = FILE_SHARE_READ;
		SECURITY_ATTRIBUTES* useDefaultSecurity = nullptr;
		const DWORD onlySucceedIfFileExists = OPEN_EXISTING;
		const DWORD useDefaultAttributes = FILE_ATTRIBUTE_NORMAL;
		const HANDLE dontUseTemplateFile = nullptr;
		fileHandle = CreateFile(textureName.c_str(), desiredAccess, otherProgramsCanStillReadTheFile,
			useDefaultSecurity, onlySucceedIfFileExists, useDefaultAttributes, dontUseTemplateFile);

		if (fileHandle == INVALID_HANDLE_VALUE)
		{
			wereThereErrors = true;
			if (o_errorMessage)
			{
				std::string windowsErrorMessage(WindowsUtil::GetLastWindowsError());
				std::stringstream errorMessage;
				errorMessage << "Windows failed to open the texture file: " << windowsErrorMessage;
				*o_errorMessage = errorMessage.str();
			}
			goto OnExit;
		}
	}

	// Get the file's size
	size_t fileSize;
	{
		LARGE_INTEGER fileSize_integer;
		if (GetFileSizeEx(fileHandle, &fileSize_integer) != FALSE)
		{
			assert(fileSize_integer.QuadPart <= SIZE_MAX);
			fileSize = static_cast<size_t>(fileSize_integer.QuadPart);
		}
		else
		{
			wereThereErrors = true;
			if (o_errorMessage)
			{
				std::string windowsErrorMessage(WindowsUtil::GetLastWindowsError());
				std::stringstream errorMessage;
				errorMessage << "Windows failed to get the size of the texture file: " << windowsErrorMessage;
				*o_errorMessage = errorMessage.str();
			}
			goto OnExit;
		}
	}
	// Read the file's contents into temporary memory
	fileContents = malloc(fileSize);
	if (fileContents)
	{
		DWORD bytesReadCount;
		OVERLAPPED* readSynchronously = NULL;
		assert(fileSize < (uint64_t(1) << (sizeof(DWORD) * 8)));
		if (ReadFile(fileHandle, fileContents, static_cast<DWORD>(fileSize),
			&bytesReadCount, readSynchronously) == FALSE)
		{
			wereThereErrors = true;
			if (o_errorMessage)
			{
				std::string windowsErrorMessage(WindowsUtil::GetLastWindowsError());
				std::stringstream errorMessage;
				errorMessage << "Windows failed to read the contents of the texture file: " << windowsErrorMessage;
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
			errorMessage << "Failed to allocate " << fileSize << " bytes to read in the texture " 
				<< textureName;
			*o_errorMessage = errorMessage.str();
		}
		goto OnExit;
	}	

	// Extract the data
	const uint8_t* currentPosition = reinterpret_cast<uint8_t*>(fileContents);
	// Verify that the file is a valid DDS
	{
		const size_t fourCcCount = 4;
		const uint8_t* const fourCc = currentPosition;
		const uint8_t fourCc_dds[fourCcCount] = { 'D', 'D', 'S', ' ' };
		// Each of the four characters can be compared in a single operation by casting to a uint32_t
		const bool isDds = *reinterpret_cast<const uint32_t*>(fourCc) == *reinterpret_cast<const uint32_t*>(fourCc_dds);
		if (isDds)
		{
			currentPosition += fourCcCount;
		}
		else
		{
			wereThereErrors = true;
			if (o_errorMessage)
			{
				char fourCcString[fourCcCount + 1] = { 0 };	// Add NULL terminator
				memcpy(fourCcString, currentPosition, fourCcCount);
				std::stringstream errorMessage;
				errorMessage << "The texture file \"" << textureName << "\" isn't a valid DDS. The Four CC is \"" << fourCcString << "\""
					" instead of \"DDS \"";
				*o_errorMessage = errorMessage.str();
			}
			goto OnExit;
		}
	}
	
	// Extracting the header
	// https://msdn.microsoft.com/en-us/library/windows/desktop/bb943982(v=vs.85).aspx 
	struct sDdsHeader
	{
		uint32_t structSize;
		uint32_t flags;
		uint32_t height;
		uint32_t width;
		uint32_t pitchOrLinearSize;
		uint32_t depth;
		uint32_t mipMapCount;
		uint32_t reserved1[11];
		struct
		{
			uint32_t structSize;
			uint32_t flags;
			uint8_t fourCc[4];
			uint32_t rgbBitCount;
			uint32_t bitMask_red;
			uint32_t bitMask_green;
			uint32_t bitMask_blue;
			uint32_t bitMask_alpha;
		} pixelFormat;
		uint32_t caps[4];
		uint32_t reserved2;
	};
	const sDdsHeader* ddsHeader = reinterpret_cast<const sDdsHeader*>(currentPosition);
	currentPosition += sizeof(sDdsHeader);
	// Convert the DDS format into an OpenGL format
	GLenum format;
	{
		// This code can only handle the two basic formats that the example TextureBuilder will create.
		// If a DDS in a different format is provided to TextureBuilder it will be passed through unchanged
		// and this code won't work.
		// Similarly, if you improve the example TextureBuilder to support more formats
		// you will also have to update this code to support them.
		const uint8_t fourCc_dxt1[] = { 'D', 'X', 'T', '1' };	// No alpha channel
		const uint8_t fourCc_dxt5[] = { 'D', 'X', 'T', '5' };	// Alpha channel
		const uint32_t fourCc_texture = *reinterpret_cast<const uint32_t*>(ddsHeader->pixelFormat.fourCc);
		if (fourCc_texture == *reinterpret_cast<const uint32_t*>(fourCc_dxt1))
		{
			format = GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
		}
		else if (fourCc_texture == *reinterpret_cast<const uint32_t*>(fourCc_dxt5))
		{
			format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		}
		else
		{
			wereThereErrors = true;
			if (o_errorMessage)
			{
				char fourCcString[5] = { 0 };	// Add NULL terminator
				memcpy(fourCcString, ddsHeader->pixelFormat.fourCc, 4);
				std::stringstream errorMessage;
				errorMessage << "The texture file \"" << textureName << "\" has an unsupported format \"" << fourCcString << "\"";
				*o_errorMessage = errorMessage.str();
			}
			goto OnExit;
		}
	}



		/*
		DDSCAPS2_CUBEMAP	Required for a cube map.										0x200
		DDSCAPS2_CUBEMAP_POSITIVEX	Required when these surfaces are stored in a cube map.	0x400
		DDSCAPS2_CUBEMAP_NEGATIVEX	Required when these surfaces are stored in a cube map.	0x800
		DDSCAPS2_CUBEMAP_POSITIVEY	Required when these surfaces are stored in a cube map.	0x1000
		DDSCAPS2_CUBEMAP_NEGATIVEY	Required when these surfaces are stored in a cube map.	0x2000
		DDSCAPS2_CUBEMAP_POSITIVEZ	Required when these surfaces are stored in a cube map.	0x4000
		DDSCAPS2_CUBEMAP_NEGATIVEZ	Required when these surfaces are stored in a cube map.	0x8000
		DDSCAPS2_VOLUME	Required for a volume texture.										0x200000
		*/


	bool isCubeMap = false;
	bool isVolumeMap = false;
	GLenum imageTarget;
	GLint textureCount = 1;
	//Generate Texture
	{
		glGenTextures(textureCount, &texture);
		GLenum errorCode = glGetError();
		WindowsUtil::Assert(errorCode == GL_NO_ERROR, reinterpret_cast<const char*>(gluErrorString(errorCode)));
	}

	if(ddsHeader->caps[1] && 0x200)
	{
		imageTarget = GL_TEXTURE_CUBE_MAP;	
		textureType = TEXTURE_CUBE;
	}
	else if(ddsHeader->caps[1] && 0x200000)
	{
		imageTarget = GL_TEXTURE_3D;
		textureType = TEXTURE_3D;
	}
	else
	{
		imageTarget = GL_TEXTURE_2D;
		textureType = TEXTURE_2D;
	}

	//Binding Texture according to the image Target
	glBindTexture(imageTarget, texture);

	switch(imageTarget)
	{
	case GL_TEXTURE_2D:
	// Iterating through each MIP map level and fill in the OpenGL texture
	{
		GLsizei currentWidth = ddsHeader->width;
		GLsizei currentHeight = ddsHeader->height;
		const GLsizei blockSize = format == GL_COMPRESSED_RGB_S3TC_DXT1_EXT ? 8 : 16;
		const GLint borderWidth = 0;
		for (uint32_t mipMapLevel = 0; mipMapLevel < ddsHeader->mipMapCount; ++mipMapLevel)
		{
			const GLsizei mipMapSize = ((currentWidth + 3) / 4) * ((currentHeight + 3) / 4) * blockSize;
			glCompressedTexImage2D(GL_TEXTURE_2D, static_cast<GLint>(mipMapLevel), format, currentWidth, currentHeight,
				borderWidth, mipMapSize, currentPosition);
			const GLenum errorCode = glGetError();
			if (errorCode == GL_NO_ERROR)
			{
				currentPosition += static_cast<size_t>(mipMapSize);
				currentWidth = std::max(1, (currentWidth / 2));
				currentHeight = std::max(1, (currentHeight / 2));
			}
			else
			{
				wereThereErrors = true;
				if (o_errorMessage)
				{
					std::stringstream errorMessage;
					errorMessage << "OpenGL rejected compressed texture data: " <<
						reinterpret_cast<const char*>(gluErrorString(errorCode));
					*o_errorMessage = errorMessage.str();
				}
				goto OnExit;
			}
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
		break;
	case GL_TEXTURE_CUBE_MAP:
		//Confirm that all the faces exist
		/*
		DDSCAPS2_CUBEMAP	Required for a cube map.										0x200
		DDSCAPS2_CUBEMAP_POSITIVEX	Required when these surfaces are stored in a cube map.	0x400
		DDSCAPS2_CUBEMAP_NEGATIVEX	Required when these surfaces are stored in a cube map.	0x800
		DDSCAPS2_CUBEMAP_POSITIVEY	Required when these surfaces are stored in a cube map.	0x1000
		DDSCAPS2_CUBEMAP_NEGATIVEY	Required when these surfaces are stored in a cube map.	0x2000
		DDSCAPS2_CUBEMAP_POSITIVEZ	Required when these surfaces are stored in a cube map.	0x4000
		DDSCAPS2_CUBEMAP_NEGATIVEZ	Required when these surfaces are stored in a cube map.	0x8000
		DDSCAPS2_VOLUME	Required for a volume texture.										0x200000

		0x400 + 0x800 + 0x1000 + 0x2000 + 0x2000 + 0x4000 + 0x8000  = 0xFE00
		
		*/
		WindowsUtil::Assert(ddsHeader->caps[1] && 0xFE00, "Cube map doesn't contains all the textures");

		for (int face = 0; face < 6; face++)
		{

			GLsizei currentWidth = ddsHeader->width;
			GLsizei currentHeight = ddsHeader->height;
			const GLsizei blockSize = format == GL_COMPRESSED_RGB_S3TC_DXT1_EXT ? 8 : 16;
			const GLint borderWidth = 0;
			for (uint32_t mipMapLevel = 0; mipMapLevel < ddsHeader->mipMapCount; ++mipMapLevel)
			{
				const GLsizei mipMapSize = ((currentWidth + 3) / 4) * ((currentHeight + 3) / 4) * blockSize;
				glCompressedTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT + face, static_cast<GLint>(mipMapLevel), format, currentWidth, currentHeight,
					borderWidth, mipMapSize, currentPosition);
				const GLenum errorCode = glGetError();
				if (errorCode == GL_NO_ERROR)
				{
					currentPosition += static_cast<size_t>(mipMapSize);
					currentWidth = std::max(1, (currentWidth / 2));
					currentHeight = std::max(1, (currentHeight / 2));
				}
				else
				{
					wereThereErrors = true;
					if (o_errorMessage)
					{
						std::stringstream errorMessage;
						errorMessage << "OpenGL rejected compressed texture data: " <<
							reinterpret_cast<const char*>(gluErrorString(errorCode));
						*o_errorMessage = errorMessage.str();
					}
					goto OnExit;
				}

			}
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT);

		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
		break;
	case GL_TEXTURE_3D:
		break;
	}
	assert(currentPosition == (reinterpret_cast<uint8_t*>(fileContents) + fileSize));

OnExit:

	if (fileContents != NULL)
	{
		free(fileContents);
		fileContents = NULL;
	}
	if (fileHandle != INVALID_HANDLE_VALUE)
	{
		if (CloseHandle(fileHandle) == FALSE)
		{
			wereThereErrors = true;
			if (o_errorMessage)
			{
				std::string windowsErrorMessage(WindowsUtil::GetLastWindowsError());
				std::stringstream errorMessage;
				errorMessage << "\nWindows failed to close the texture file handle: " << windowsErrorMessage;
				*o_errorMessage += errorMessage.str();
			}
		}
		fileHandle = INVALID_HANDLE_VALUE;
	}
	if (wereThereErrors && (texture != 0))
	{
		const GLsizei textureCount = 1;
		glDeleteTextures(textureCount, &texture);
		assert(glGetError == GL_NO_ERROR);
		texture = 0;
	}

	if(o_errorMessage->size()>0)
	{
		WindowsUtil::Print((*o_errorMessage).c_str());
	}
	return !wereThereErrors;
}

Engine::Graphics::Texture::~Texture()
{
	for (std::map<std::string, SharedPointer<Texture>>::iterator i = mTextureList.begin();
	i != mTextureList.end(); ++i)
	{
//		glDeleteTextures(1, &i->second->texture);
	}
}


void Engine::Graphics::Texture::setSamplerID(SamplerID sampleID)
{
	textureSamplerID = sampleID;	
}

void Engine::Graphics::Texture::setTextureInShaderObject(int i_textureUnit)
{
	associateSamplerDataFromShader();
	glActiveTexture(GL_TEXTURE0 + i_textureUnit);
	GLenum errorCode = glGetError();
	if ((errorCode == GL_NO_ERROR))
	{
		switch(textureType)
		{
		case TEXTURE_2D:
			glBindTexture(GL_TEXTURE_2D, texture);
			break;
		case TEXTURE_3D:
			glBindTexture(GL_TEXTURE_3D, texture);
			break;
		case TEXTURE_CUBE:
			glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
			break;
		}		
		errorCode = glGetError();
		if ((errorCode == GL_NO_ERROR))
		{		
			glUniform1i(textureSamplerID, i_textureUnit);
			errorCode = glGetError();
			if (!errorCode == GL_NO_ERROR)
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




