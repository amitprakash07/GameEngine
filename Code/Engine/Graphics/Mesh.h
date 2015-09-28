#ifndef __MESH_H
#define __MESH_H

#ifdef PLATFORM_OPEN_GL
#include "../../Externals/OpenGLExtensions/OpenGlExtensions.h"
#elif PLATFORM_D3D
#include <d3d9.h>
#endif

#include <stdint.h>
#include "MeshLoadFromLua.h"
#include <vector>


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
#ifdef PLATFORM_D3D
			uint8_t B, G, R, A;
#elif PLATFORM_OPEN_GL
			uint8_t R, G, B, A;
#endif
		};
		struct triangleIndex
		{
			uint8_t first, second, third;
		};
		
		
		class Mesh
		{
		public:
			bool drawMesh();
			bool LoadMesh();
			vertex* getVertex();
			uint32_t* getIndices();
			triangleIndex* getTriangleIndicesList();
			void setWinding(winding);
			winding getWinding();
			void setMeshFileName(std::string);
			std::string getMeshFileName();	
			~Mesh();
		private:
			vertex *mVertex;
			triangleIndex *mIndices;
			winding mWinding;
			int triangleCount;
			int vertexCount;
			std::string meshFileName;
#ifdef PLATFORM_OPEN_GL
			GLuint s_vertexArrayID;
			bool createVertexArray();
#elif PLATFORM_D3D
			IDirect3DVertexBuffer9* s_vertexBuffer;
			IDirect3DIndexBuffer9* s_indexBuffer;
			IDirect3DVertexDeclaration9* s_vertexDeclaration;
			bool createVertexBuffer();
			bool createIndexBuffer();
#endif
			
		};
	}
}
#endif