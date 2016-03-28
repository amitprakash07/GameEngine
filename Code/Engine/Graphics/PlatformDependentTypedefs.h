//#ifndef __PLATFORM_DEPENDENT_DEF_H
//#define __PLATFORM_DEPENDENT_DEF_H
//
//#include "../Windows/WindowsIncludes.h"
//#include "../../Externals/OpenGLExtensions/31597/glext.h"
//
//#ifdef PLATFORM_D3D
//#include <d3dx9shader.h>
//#elif PLATFORM_OPEN_GL
//#include <gl/GLU.h>
//#endif
//
//
//namespace Engine
//{
//	namespace Graphics
//	{
//		typedef
//#ifdef PLATFORM_D3D 
//			D3DXHANDLE
//#elif PLATFORM_OPEN_GL
//			GLint
//#endif
//			UniformHandle;
//
//		typedef
//#ifdef PLATFORM_D3D
//			DWORD
//#elif PLATFORM_OPEN_GL
//			GLint
//#endif
//			SamplerID;
//
//		typedef
//#ifdef PLATFORM_D3D
//			IDirect3DTexture9*
//#elif PLATFORM_OPEN_GL
//			GLuint
//#endif
//			TextureResource;
//
//		typedef
//#ifdef PLATFORM_D3D
//			ID3DXConstantTable*
//#elif PLATFORM_OPEN_GL
//			GLuint
//#endif
//			ConstantTable;
//
//
//		typedef
//#ifdef PLATFORM_D3D
//			DWORD
//#elif PLATFORM_OPEN_GL
//			GLenum
//#endif
//			CullingMode;
//
//		enum class TextureType
//		{
//#ifdef PLATFORM_OPEN_GL
//			TEXTURE_2D = GL_TEXTURE_2D,
//			TEXTURE_CUBE = GL_TEXTURE_CUBE_MAP,
//			TEXTURE_3D = GL_TEXTURE_3D
//#endif
//		};
//
//		enum class MinFilter
//		{
//#ifdef PLATFORM_OPEN_GL
//			NEAREST_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
//			LINEAR_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
//			NEAREST_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
//			LINEAR_LINEAR = GL_LINEAR_MIPMAP_LINEAR
//#endif
//		};
//
//		enum class MagFilter
//		{
//#ifdef PLATFORM_OPEN_GL
//			LINEAR = GL_LINEAR,
//			NEAREST = GL_NEAREST,
//#endif
//		};
//
//#endif