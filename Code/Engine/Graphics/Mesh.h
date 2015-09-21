#ifndef __MESH_H
#define __MESH_H

#ifdef PLATFORM_OPEN_GL
#include "../../Externals/OpenGLExtensions/OpenGlExtensions.h"
#elif PLATFORM_D3D
#include <d3d9.h>
#endif

#include <stdint.h>



namespace Engine
{
	namespace Graphics
	{
		enum indiceWinding
		{
			RIGHT = 0,
			LEFT = 1
		};
		typedef indiceWinding winding;
		
		struct vertex
		{
			float X;
			float Y;
			uint8_t R, G, B, A;
		};
		struct triangleIndex
		{
			uint8_t first, second, third;
		};
		
		
		class Mesh
		{
		public:
			static bool drawMesh();
			static bool LoadMesh();
			static vertex* getVertex();
			static uint32_t* getIndices();
			static triangleIndex* getTriangleIndicesList();
			static void setWinding(winding);
			static winding getWinding();
#ifdef PLATFORM_D3D
			static IDirect3DVertexBuffer9* getVertexBuffer();
			static IDirect3DIndexBuffer9* getIndexBuffer();
			static IDirect3DVertexDeclaration9* getVertexDeclaration();
			static void setVertexBuffer(IDirect3DVertexBuffer9*);
			static void setIndexBuffer(IDirect3DIndexBuffer9*);
			static void setVertexDeclaration(IDirect3DVertexDeclaration9*);
#elif PLATFORM_OPEN_GL
			static void setVertexID(GLuint i_vertexArrayID) { s_vertexArrayID = i_vertexArrayID; }
#endif
		private:
			static vertex *mVertex;
			static triangleIndex *mIndices;
			static winding mWinding;
#ifdef PLATFORM_OPEN_GL
			static GLuint s_vertexArrayID;
#elif PLATFORM_D3D
			static IDirect3DVertexBuffer9* s_vertexBuffer;
			static IDirect3DIndexBuffer9* s_indexBuffer;
			static IDirect3DVertexDeclaration9* s_vertexDeclaration;
#endif
			
			
		};
	}
}
#endif