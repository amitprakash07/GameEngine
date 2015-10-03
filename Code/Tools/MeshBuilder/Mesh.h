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
		};
	}
}
#endif