#ifndef __MESH_H
#define __MESH_H

#ifdef PLATFORM_OPEN_GL
#include "../../Externals/OpenGLExtensions/OpenGlExtensions.h"
#elif PLATFORM_D3D
#include <d3d9.h>
#endif

#include <stdint.h>
#include <vector>
#include <map>
#include "../Core/Utilities/SharedPointer.h"


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
				
		class Mesh
		{
		public:
			static bool addToMeshList(std::string, std::string);
			static SharedPointer<Mesh> getMesh(std::string);
			static void deleteAllMesh();
			bool drawMesh();
			bool LoadMesh();
			vertex* getVertex();
			uint32_t* getIndices();
			void setWinding(winding);
			winding getWinding();
			std::string getMeshFileName();	
			~Mesh();
		private:
			static std::map<std::string, SharedPointer<Mesh>> meshList;
			vertex *mVertex;
			uint32_t *mIndices;
			winding mWinding;
			int triangleCount;
			int vertexCount;
			std::string meshFileName;
			std::string meshName;
			static bool isMeshExist(std::string);
			Mesh(std::string, std::string);
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