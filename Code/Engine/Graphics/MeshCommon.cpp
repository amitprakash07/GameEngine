#include "Mesh.h"
#include "../Windows/WindowsFunctions.h"
#include <fstream>


typedef char BYTES;

std::map<std::string, Engine::SharedPointer<Engine::Graphics::Mesh>> Engine::Graphics::Mesh::meshList;

bool Engine::Graphics::Mesh::addToMeshList(std::string i_meshName, std::string i_fileName)
{
	if (!i_fileName.empty())
	{
		Engine::SharedPointer<Mesh> newMesh(new Mesh(i_meshName, i_fileName));
		newMesh->LoadMesh();
		meshList[i_fileName] = newMesh; 
		return true;
	}

	std::stringstream errormessage;
	errormessage << "Unable to add Scene. Mesh Pointer is null. Load Mesh again";
	WindowsUtil::Print(errormessage.str());
	return false;
}

Engine::SharedPointer<Engine::Graphics::Mesh> Engine::Graphics::Mesh::getMesh(std::string i_fileName)
{
	if(!i_fileName.empty())
	{
		return (meshList[i_fileName]);
	}
	return (Engine::SharedPointer<Engine::Graphics::Mesh>());
}

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
	vertexcount-4 byte-int triangleCount-4byte-int
	vertices
	indices
	*/
	vertexCount = *reinterpret_cast<int*> (currentPosition); //vertexCount
	currentPosition += sizeof(int);

	triangleCount = *reinterpret_cast<int*>(currentPosition); //No of triangles
	currentPosition += sizeof(int);

	//creating vertex memmory
	if (!mVertex)
		mVertex = new vertex[vertexCount];
	//copying buffer data to the mVertex
	memcpy(mVertex, reinterpret_cast<vertex*>(currentPosition), sizeof(vertex)*vertexCount); //Vertices
	currentPosition += sizeof(vertex)*vertexCount;

	//creating indices memory
	if (!mIndices)
		mIndices = new uint32_t[triangleCount * 3];
	//copying indices data from the memory
	memcpy(mIndices, reinterpret_cast<uint32_t*>(currentPosition), sizeof(uint32_t) * 3 * triangleCount); //Indices
	
	//Freeing memory
	currentPosition = nullptr;
	delete buffer;	


#ifdef PLATFORM_D3D
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
	if(! createVertexArray())
	{
		errormessage << "Unable to Create Vertex and Index Buffer for the Mesh.";
		WindowsUtil::Print(errormessage.str());
		return false;
	}
#endif
	
	return true;
}

void Engine::Graphics::Mesh::deleteAllMesh()
{
	for (std::map<std::string, Engine::SharedPointer<Engine::Graphics::Mesh>>::iterator i = meshList.begin(); i != meshList.end(); ++i)
		i->second.deleteObject();
}



