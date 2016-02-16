#include "Mesh.h"
#include "../Windows/WindowsFunctions.h"
#include <fstream>
#include "../../Engine/Core/Utilities/HashedString.h"
#include "Effect.h"


typedef char BYTES;

std::map<std::string, Engine::SharedPointer<Engine::Graphics::Mesh>> Engine::Graphics::Mesh::meshList;

bool Engine::Graphics::Mesh::addToMeshList(std::string i_fileName)
{
	if (!i_fileName.empty())
	{
		if (!isMeshExist(i_fileName))
		{
			Engine::SharedPointer<Mesh> newMesh(new Mesh(i_fileName), "Engine::Graphics::Mesh");
			if (!newMesh.isNull())
			{
				if (newMesh->LoadMesh() && newMesh->createBuffers())
					meshList[i_fileName] = newMesh;
			}
		}
		return true;
	}

	std::stringstream errormessage;
	errormessage << "Unable to load Mesh. FileName is null. Load Mesh again";
	WindowsUtil::Print(errormessage.str());
	return false;
}

Engine::SharedPointer<Engine::Graphics::Mesh> Engine::Graphics::Mesh::getMesh(std::string i_fileName)
{
	if (!i_fileName.empty())
	{
		return (meshList[i_fileName]);
	}
	return (Engine::SharedPointer<Engine::Graphics::Mesh>());
}

Engine::Graphics::vertex* Engine::Graphics::Mesh::getVertex() const
{
	if (mVertex)
		return mVertex;
	return nullptr;
}

uint32_t* Engine::Graphics::Mesh::getIndices() const
{
	if (mIndices)
	{
		return mIndices;
	}
	return nullptr;
}

std::string Engine::Graphics::Mesh::getMeshFileName() const
{
	if (!meshFileName.empty())
		return meshFileName;
	return nullptr;
}

void Engine::Graphics::Mesh::setWinding(winding i_winding)
{
	mWinding = i_winding;
}

Engine::Graphics::winding Engine::Graphics::Mesh::getWinding() const
{
	return mWinding;
}

bool Engine::Graphics::Mesh::LoadMesh()
{
	std::stringstream errormessage;

	std::ifstream readFile;

	if (!readFile.is_open())
		readFile.open(meshFileName.c_str(), std::ifstream::binary);

	readFile.seekg(0, readFile.end);
	size_t length = static_cast<size_t>(readFile.tellg());
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

	return true;
}

void Engine::Graphics::Mesh::deleteAllMesh()
{
	for (std::map<std::string, Engine::SharedPointer<Engine::Graphics::Mesh>>::iterator i = meshList.begin(); i != meshList.end(); ++i)
		i->second.deleteObject();
}

bool Engine::Graphics::Mesh::isMeshExist(std::string i_fileName)
{
	if (!i_fileName.empty())
	{
		for (std::map<std::string, SharedPointer<Mesh>>::iterator i = meshList.begin(); i != meshList.end(); ++i)
		{
			if (Engine::utils::StringHash(i->first.c_str()) == Engine::utils::StringHash(i_fileName.c_str()))
				return true;
		}
		return false;
	}
	return false;
}

//void Engine::Graphics::Mesh::addUniform(std::string iUniformName, ShaderType iShaderType)
//{
//	SharedPointer<Uniform> tempUniform = Uniform::createUniform();
//	tempUniform->setShaderType(iShaderType);
//	uniformNames[iUniformName] = tempUniform;
//}
//
//void Engine::Graphics::Mesh::setUniformHandle(std::string uniformName,
//	std::string effectName)
//{
//	SharedPointer<Uniform> tempUniform = uniformNames[uniformName];
//	tempUniform->setHandle(Engine::Graphics::Effect::getEffect(effectName)->getUniformHandle(
//		tempUniform->getUniformName(), tempUniform->getShaderType()));
//}

