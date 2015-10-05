#include "Mesh.h"
#include "../Windows/WindowsFunctions.h"
#include <fstream>
#include "Graphics.h"

typedef char BYTES;

Engine::Graphics::vertex* Engine::Graphics::Mesh::getVertex()
{
	if (mVertex)
		return mVertex;
	return nullptr;
}

uint32_t* Engine::Graphics::Mesh::getIndices()
{
	if (mIndices)
	{
		return mIndices;
	}
	return nullptr;
}

void Engine::Graphics::Mesh::setMeshFileName(std::string i_fileName)
{
	if (!i_fileName.empty())
	{
		meshFileName = i_fileName;
		//memcpy(meshFileName, i_fileName, sizeof(char)*strlen(i_fileName));
	}
}

std::string Engine::Graphics::Mesh::getMeshFileName()
{
	if (!meshFileName.empty())
		return meshFileName;
	return nullptr;
}

void Engine::Graphics::Mesh::setWinding(winding i_winding)
{
	mWinding = i_winding;
}

Engine::Graphics::winding Engine::Graphics::Mesh::getWinding()
{
	return mWinding;
}

bool Engine::Graphics::Mesh::LoadMesh()
{
	std::stringstream errormessage;

	std::ifstream readFile;

	if(!readFile.is_open())
		readFile.open(meshFileName.c_str(), std::ifstream::binary);
	
	readFile.seekg(0, readFile.end);
	size_t length = readFile.tellg();
	readFile.seekg(0, readFile.beg);

	BYTES * buffer = new BYTES[length];
	//Lets read evrything from asset binary file
	readFile.read(buffer, length);
	
	readFile.close();//Closing the file Pointer

	BYTES * currentPosition = buffer;
	/* My Binary Format
	vertexcount-4 byte-int triangleCount-4byte-int  winding order- sizeof(windingorder)
	vertices
	indices
	*/
	vertexCount = *reinterpret_cast<int*> (currentPosition); //vertexCount
	currentPosition += sizeof(int);

	triangleCount = *reinterpret_cast<int*>(currentPosition); //No of triangles
	currentPosition += sizeof(int);

	mWinding = *reinterpret_cast<winding*>(currentPosition); //winding order
	currentPosition += sizeof(winding);

	//creating vertex memmory
	if (!mVertex)
		mVertex = new vertex[vertexCount];
	//copying buffer data to the mVertex
	memcpy(mVertex, reinterpret_cast<vertex*>(currentPosition), sizeof(vertex)*vertexCount);
	currentPosition += sizeof(vertex)*vertexCount;

	//creating indices memory
	if (!mIndices)
		mIndices = new uint32_t[triangleCount * 3];
	//copying indices data from the memory
	memcpy(mIndices, reinterpret_cast<uint32_t*>(currentPosition), sizeof(uint32_t) * 3 * triangleCount);
	
	//Freeing memory
	currentPosition = nullptr;
	delete buffer;	


#ifdef PLATFORM_D3D
	//Changing Winding order
	if (mWinding == Engine::Graphics::RIGHT)
	{
		for (int i = 0; i < triangleCount;i++)
		{
			uint32_t temp = mIndices[i*3 + 2];
			mIndices[i * 3 + 2] = mIndices[i * 3 + 1];
			mIndices[i * 3 + 1] = temp;
		}
	}

	if(!createVertexBuffer())
	{
		errormessage << "Unable to Create VertexBuffer for the Mesh.";
		WindowsUtil::Print(errormessage.str());
		return false;
	}
	if(!createIndexBuffer())
	{
		errormessage << "Unable to create Index Buffer for the Mesh.";
		WindowsUtil::Print(errormessage.str());
		return false;
	}

#elif PLATFORM_OPEN_GL
	if (mWinding == Engine::Graphics::LEFT)
	{
		for (int i = 0; i < triangleCount; i++)
		{
			uint32_t temp = mIndices[i * 3 + 2];
			mIndices[i * 3 + 2] = mIndices[i * 3 + 1];
			mIndices[i * 3 + 1] = temp;
		}
	}
	if(! createVertexArray())
	{
		errormessage << "Unable to Create Vertex and Index Buffer for the Mesh.";
		WindowsUtil::Print(errormessage.str());
		return false;
	}
#endif
	
	return true;
}

Engine::Graphics::Mesh::~Mesh()
{
	if (mVertex)
	{
		delete mVertex;
		mVertex = nullptr;
	}

	if (mIndices)
	{
		delete mIndices;
		mIndices = nullptr;
	}

#ifdef PLATFORM_D3D
	
	if (s_vertexBuffer)
		s_vertexBuffer->Release();
	
	if (s_indexBuffer)
		s_indexBuffer->Release();
	
	if (s_vertexDeclaration)
	{
		GraphicsSystem::getDevice()->SetVertexDeclaration(nullptr);
		s_vertexDeclaration->Release();
	}

	s_vertexBuffer = nullptr;
	s_indexBuffer = nullptr;
	s_vertexDeclaration = nullptr;
#endif
}
