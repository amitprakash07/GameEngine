// Header Files
//=============

#include "MeshBuilder.h"
#include "Mesh.h"
#include "../../Engine/Windows/WindowsFunctions.h"
#include <iostream>

// Interface
//==========

// Build
//------

bool Tools::AssetBuilder::MeshBuilder::Build(const std::vector<std::string>&)
{
	bool wereThereErrors = false;
	Mesh *m = new Mesh();
	m->setMeshFileName(m_path_source);
	m->LoadMesh();
	std::cout << "Loaded Mesh Successfully";
	std::cout << "Winding order of the Mesh is" << m->getWinding();
	//// Copy the source to the target
	//{
	//	const bool dontFailIfTargetAlreadyExists = false;
	//	const bool updateTheTargetFileTime = true;
	//	std::string errorMessage;
	//	if (!WindowsUtil::CopyFile(m_path_source, m_path_target, dontFailIfTargetAlreadyExists, updateTheTargetFileTime, &errorMessage))
	//	{
	//		wereThereErrors = true;
	//		std::stringstream decoratedErrorMessage;
	//		decoratedErrorMessage << "Windows failed to copy \"" << m_path_source << "\" to \"" << m_path_target << "\": " << errorMessage << "in File" << __FILE__;
	//		WindowsUtil::Print(decoratedErrorMessage.str().c_str());
	//	}
	//}
	return !wereThereErrors;
}