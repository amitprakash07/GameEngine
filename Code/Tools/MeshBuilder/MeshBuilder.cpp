// Header Files
//=============

#include "MeshBuilder.h"
#include "Mesh.h"
#include "../../Engine/Windows/WindowsFunctions.h"
#include <fstream>

// Interface
//==========

// Build
//------
typedef char BYTES;

bool Tools::AssetBuilder::MeshBuilder::Build(const std::vector<std::string>&)
{
	bool wereThereErrors = false;
	Mesh *m = new Mesh();
	m->setMeshFileName(m_path_source);
	if(m->LoadMesh())
	{
#ifdef BUILD_DEBUG
		m->displayVertices();
#endif
		std::ofstream writeToFile;
		writeToFile.open(m_path_target, std::ofstream::binary);
		/* My Binary Format
		vertexcount triangleCount
		vertices
		indices
		*/
		
		{
			//Writing vertexCount - First write
			BYTES *bytes = new BYTES[sizeof(int)];
			int * vCount = new int;
			*vCount = m->getVertexCount();
			memcpy(bytes, vCount, sizeof(int));
			writeToFile.write(bytes, sizeof(int));
			delete vCount;
			vCount = nullptr;
			delete bytes;
			bytes = nullptr;
		}
		
		{
			//Writing TriangleCount  
			BYTES * bytes = new BYTES[sizeof(int)];
			int * triCount = new int;
			*triCount = m->getTriangleCount();
			memcpy(bytes, triCount, sizeof(int));
			writeToFile.write(bytes, sizeof(int));
			delete triCount;
			delete bytes;
			triCount = nullptr;			
			bytes = nullptr;			
		}
		
	
		{
			//Writing vertices - Third Write
			BYTES * bytes = new BYTES[sizeof(vertex)* m->getVertexCount()];
			memcpy(bytes, m->getVertex(), sizeof(vertex)* m->getVertexCount());
			writeToFile.write(bytes, sizeof(vertex)* m->getVertexCount());
			delete bytes;
			bytes = nullptr;
		}
		
		{
			//writing indices - Fourth Write
			BYTES *bytes = new BYTES[sizeof(triangleIndex) * m->getTriangleCount()];
			memcpy(bytes, m->getIndices(), sizeof(uint32_t)* m->getTriangleCount() * 3);
			writeToFile.write(bytes, sizeof(triangleIndex)* m->getTriangleCount());
			delete bytes;
			bytes = nullptr;
		}
		writeToFile.close();
	}

	delete m; //deleting mesh pointer

	return !wereThereErrors;
}