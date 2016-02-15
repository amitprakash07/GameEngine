// Header Files
//=============

#include "OpenGlExtensions.h"

#include <sstream>
#include "../../Engine/Windows/WindowsFunctions.h"


// Helper Function Declarations
//=============================

namespace
{
	void* GetGlFunctionAddress(const char* i_functionName, std::string* o_errorMessage = NULL);
}

// Interface
//==========

// OpenGL Extension Definitions
//-----------------------------

PFNGLACTIVETEXTUREPROC glActiveTexture = NULL;
PFNGLATTACHSHADERPROC glAttachShader = NULL;
PFNGLBINDBUFFERPROC glBindBuffer = NULL;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray = NULL;
PFNGLBUFFERDATAPROC glBufferData = NULL;
PFNGLCOMPILESHADERPROC glCompileShader = NULL;
PFNGLCREATEPROGRAMPROC glCreateProgram = NULL;
PFNGLCREATESHADERPROC glCreateShader = NULL;
PFNGLDELETEBUFFERSPROC glDeleteBuffers = NULL;
PFNGLDELETEPROGRAMPROC glDeleteProgram = NULL;
PFNGLDELETESHADERPROC glDeleteShader = NULL;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = NULL;
PFNGLENABLEVERTEXATTRIBARRAYARBPROC glEnableVertexAttribArray = NULL;
PFNGLGENBUFFERSPROC glGenBuffers = NULL;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = NULL;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = NULL;
PFNGLGETPROGRAMIVPROC glGetProgramiv = NULL;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = NULL;
PFNGLGETSHADERIVPROC glGetShaderiv = NULL;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = NULL;
PFNGLLINKPROGRAMPROC glLinkProgram = NULL;
PFNGLSHADERSOURCEPROC glShaderSource = NULL;
PFNGLUSEPROGRAMPROC glUseProgram = nullptr;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = NULL;
PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D = nullptr;

//Uniform  Setting Functions
PFNGLUNIFORM1FPROC glUniform1f = nullptr;
PFNGLUNIFORM2FPROC glUniform2f = nullptr;
PFNGLUNIFORM3FPROC glUniform3f = nullptr;
PFNGLUNIFORM4FPROC glUniform4f = nullptr;

PFNGLUNIFORM1IPROC glUniform1i = nullptr;
PFNGLUNIFORM2IPROC glUniform2i = nullptr;
PFNGLUNIFORM3IPROC glUniform3i = nullptr;
PFNGLUNIFORM4IPROC glUniform4i = nullptr;

PFNGLUNIFORM1UIPROC glUniform1ui = nullptr;
PFNGLUNIFORM2UIPROC glUniform2ui = nullptr;
PFNGLUNIFORM3UIPROC glUniform3ui = nullptr;
PFNGLUNIFORM4UIPROC glUniform4ui = nullptr;

PFNGLUNIFORM1FVPROC glUniform1fv = nullptr;
PFNGLUNIFORM2FVPROC glUniform2fv = nullptr;
PFNGLUNIFORM3FVPROC glUniform3fv = nullptr;
PFNGLUNIFORM4FVPROC glUniform4fv = nullptr;

PFNGLUNIFORM1IVPROC glUniform1iv = nullptr;
PFNGLUNIFORM2IVPROC glUniform2iv = nullptr;
PFNGLUNIFORM3IVPROC glUniform3iv = nullptr;
PFNGLUNIFORM4IVPROC glUniform4iv = nullptr;

PFNGLUNIFORM1UIVPROC glUniform1uiv = nullptr;
PFNGLUNIFORM2UIVPROC glUniform2uiv = nullptr;
PFNGLUNIFORM3UIVPROC glUniform3uiv = nullptr;
PFNGLUNIFORM4UIVPROC glUnifrom4uiv = nullptr;

PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = nullptr;



// Initialization
//---------------

bool OpenGlExtensions::Load(std::string* o_errorMessage)
{
	// A current OpenGL context must exist before extensions can be loaded
	{
		const HGLRC currentContext = wglGetCurrentContext();
		if (currentContext == NULL)
		{
			if (o_errorMessage)
			{
				*o_errorMessage = "OpenGL extensions can't be loaded without a current OpenGL context";
			}
			return false;
		}
	}

#define LOADGLFUNCTION( i_functionName, i_functionType )														\
		i_functionName = reinterpret_cast<i_functionType>( GetGlFunctionAddress( #i_functionName, o_errorMessage ) );	\
		if ( !i_functionName )																							\
			return false;

	LOADGLFUNCTION(glActiveTexture, PFNGLACTIVETEXTUREPROC);
	LOADGLFUNCTION(glAttachShader, PFNGLATTACHSHADERPROC);
	LOADGLFUNCTION(glBindBuffer, PFNGLBINDBUFFERPROC);
	LOADGLFUNCTION(glBindVertexArray, PFNGLBINDVERTEXARRAYPROC);
	LOADGLFUNCTION(glBufferData, PFNGLBUFFERDATAPROC);
	LOADGLFUNCTION(glCompileShader, PFNGLCOMPILESHADERPROC);
	LOADGLFUNCTION(glCreateProgram, PFNGLCREATEPROGRAMPROC);
	LOADGLFUNCTION(glCreateShader, PFNGLCREATESHADERPROC);
	LOADGLFUNCTION(glDeleteBuffers, PFNGLDELETEBUFFERSPROC);
	LOADGLFUNCTION(glDeleteProgram, PFNGLDELETEPROGRAMPROC);
	LOADGLFUNCTION(glDeleteVertexArrays, PFNGLDELETEVERTEXARRAYSPROC);
	LOADGLFUNCTION(glDeleteShader, PFNGLDELETESHADERPROC);
	LOADGLFUNCTION(glEnableVertexAttribArray, PFNGLENABLEVERTEXATTRIBARRAYARBPROC);
	LOADGLFUNCTION(glGenBuffers, PFNGLGENBUFFERSPROC);
	LOADGLFUNCTION(glGenVertexArrays, PFNGLGENVERTEXARRAYSPROC);
	LOADGLFUNCTION(glGetProgramInfoLog, PFNGLGETPROGRAMINFOLOGPROC);
	LOADGLFUNCTION(glGetProgramiv, PFNGLGETPROGRAMIVPROC);
	LOADGLFUNCTION(glGetShaderInfoLog, PFNGLGETSHADERINFOLOGPROC);
	LOADGLFUNCTION(glGetShaderiv, PFNGLGETSHADERIVPROC);
	LOADGLFUNCTION(glGetUniformLocation, PFNGLGETUNIFORMLOCATIONPROC);
	LOADGLFUNCTION(glLinkProgram, PFNGLLINKPROGRAMPROC);
	LOADGLFUNCTION(glShaderSource, PFNGLSHADERSOURCEPROC);
	LOADGLFUNCTION(glUniform1fv, PFNGLUNIFORM1FVPROC);
	LOADGLFUNCTION(glUniform2fv, PFNGLUNIFORM2FVPROC);
	LOADGLFUNCTION(glUniform3fv, PFNGLUNIFORM3FVPROC);
	LOADGLFUNCTION(glUniform4fv, PFNGLUNIFORM4FVPROC);
	LOADGLFUNCTION(glUseProgram, PFNGLUSEPROGRAMPROC);
	LOADGLFUNCTION(glVertexAttribPointer, PFNGLVERTEXATTRIBPOINTERPROC);
	LOADGLFUNCTION(glCompressedTexImage2D, PFNGLCOMPRESSEDTEXIMAGE2DPROC);

	LOADGLFUNCTION(glUniform1f, PFNGLUNIFORM1FPROC);
	LOADGLFUNCTION(glUniform2f, PFNGLUNIFORM2FPROC);
	LOADGLFUNCTION(glUniform3f, PFNGLUNIFORM3FPROC);
	LOADGLFUNCTION(glUniform4f, PFNGLUNIFORM4FPROC);

	LOADGLFUNCTION(glUniform1i, PFNGLUNIFORM1IPROC);
	LOADGLFUNCTION(glUniform2i, PFNGLUNIFORM2IPROC);
	LOADGLFUNCTION(glUniform3i, PFNGLUNIFORM3IPROC);
	LOADGLFUNCTION(glUniform4i, PFNGLUNIFORM4IPROC);

	LOADGLFUNCTION(glUniform1ui, PFNGLUNIFORM1UIPROC);
	LOADGLFUNCTION(glUniform2ui, PFNGLUNIFORM2UIPROC);
	LOADGLFUNCTION(glUniform3ui, PFNGLUNIFORM3UIPROC);
	LOADGLFUNCTION(glUniform4ui, PFNGLUNIFORM4UIPROC);

	LOADGLFUNCTION(glUniform1fv, PFNGLUNIFORM1FVPROC);
	LOADGLFUNCTION(glUniform2fv, PFNGLUNIFORM2FVPROC);
	LOADGLFUNCTION(glUniform3fv, PFNGLUNIFORM3FVPROC);
	LOADGLFUNCTION(glUniform4fv, PFNGLUNIFORM4FVPROC);

	LOADGLFUNCTION(glUniform1iv, PFNGLUNIFORM1IVPROC);
	LOADGLFUNCTION(glUniform2iv, PFNGLUNIFORM2IVPROC);
	LOADGLFUNCTION(glUniform3iv, PFNGLUNIFORM3IVPROC);
	LOADGLFUNCTION(glUniform4iv, PFNGLUNIFORM4IVPROC);

	LOADGLFUNCTION(glUniform1uiv, PFNGLUNIFORM1UIVPROC);
	LOADGLFUNCTION(glUniform2uiv, PFNGLUNIFORM2UIVPROC);
	LOADGLFUNCTION(glUniform3uiv, PFNGLUNIFORM3UIVPROC);
	//LOADGLFUNCTION(glUnifrom4uiv, PFNGLUNIFORM4UIVPROC );

	LOADGLFUNCTION(glUniformMatrix4fv, PFNGLUNIFORMMATRIX4FVPROC);





#undef LOADGLFUNCTION

	return true;
}

// Helper Function Declarations
//=============================

namespace
{
	void* GetGlFunctionAddress(const char* i_functionName, std::string* o_errorMessage)
	{
		void* address = reinterpret_cast<void*>(wglGetProcAddress(i_functionName));
		// The documentation says that NULL will be returned if the function isn't found,
		// but according to https://www.opengl.org/wiki/Load_OpenGL_Functions
		// other values can be returned by some implementations
		if ((address != NULL)
			&& (address != reinterpret_cast<void*>(1)) && (address != reinterpret_cast<void*>(2))
			&& (address != reinterpret_cast<void*>(3)) && (address != reinterpret_cast<void*>(-1)))
		{
			return address;
		}
		std::string wglErrorMessage;
		if (address == NULL)
		{
			wglErrorMessage = WindowsUtil::GetLastWindowsError();
		}
		// wglGetProcAddress() won't return the address of any 1.1 or earlier OpenGL functions
		// that are built into Windows' Opengl32.dll
		// but an attempt can be made to load those manually
		// in case the user of this function has made a mistake
		{
			// This library should already be loaded,
			// and so this function will just retrieve a handle to it
			HMODULE glLibrary = LoadLibrary("Opengl32.dll");
			if (glLibrary != NULL)
			{
				// Look for an old OpenGL function
				void* address = reinterpret_cast<void*>(GetProcAddress(glLibrary, i_functionName));
				// Decrement the library's reference count
				FreeLibrary(glLibrary);
				// Return an address if it was found
				if (address != NULL)
				{
					return address;
				}
			}
		}

		// If this code is reached the OpenGL function wasn't found
		if (o_errorMessage)
		{
			std::stringstream errorMessage;
			errorMessage << "Windows failed to find the address of the OpenGL function \"" << i_functionName << "\"";
			if (!wglErrorMessage.empty())
			{
				errorMessage << ": " << wglErrorMessage;
			}
			*o_errorMessage = errorMessage.str();
		}

		return NULL;
	}
}
