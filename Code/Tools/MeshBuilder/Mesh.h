#ifndef __MESH_H
#define __MESH_H

#include <stdint.h>
#include <vector>


namespace Tools
{
	namespace AssetBuilder
	{
		enum indiceWinding
		{
			RIGHT = 0,
			LEFT = 1
		};
		typedef indiceWinding winding;
		
		struct vertex
		{
			/*float X;
			float Y;
			float Z;*/
			float X, Y, Z;
			// Normal
			float nx, ny, nz;
			// Tangent
			float tx, ty, tz;
			// Bitangent
			float btx, bty, btz;
			// Texture coordinates
			float u, v;
#ifdef PLATFORM_D3D
			uint8_t B, G, R, A;
#elif PLATFORM_OPEN_GL
			uint8_t R, G, B, A;
#endif
		};
		
		struct triangleIndex
		{
			uint32_t first, second, third;
		};
		
		
		class Mesh
		{
		public:
			bool LoadMesh();
			vertex* getVertex();
			uint32_t* getIndices();
			triangleIndex* getTriangleIndicesList();
			void setWinding(winding);
			winding getWinding();
			void setMeshFileName(std::string);
			std::string getMeshFileName();
			int getVertexCount();
			int getTriangleCount();
#ifdef BUILD_DEBUG
			void displayVertices();
#endif
			~Mesh();
		private:
			vertex *mVertex;
			triangleIndex *mIndices;
			winding mWinding;
			int triangleCount;
			int vertexCount;
			std::string meshFileName;
		};
	}
}
#endif