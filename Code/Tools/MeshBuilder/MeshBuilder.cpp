// Header Files
//=============

#include "MeshBuilder.h"

#include "../../Engine/Windows/WindowsFunctions.h"

// Interface
//==========

// Build
//------

bool Tools::AssetBuilder::MeshBuilder::Build(const std::vector<std::string>&)
{
	bool wereThereErrors = false;

	// Copy the source to the target
	{
		const bool dontFailIfTargetAlreadyExists = false;
		const bool updateTheTargetFileTime = true;
		std::string errorMessage;
		if (!WindowsUtil::CopyFile(m_path_source, m_path_target, dontFailIfTargetAlreadyExists, updateTheTargetFileTime, &errorMessage))
		{
			wereThereErrors = true;
			std::stringstream decoratedErrorMessage;
			decoratedErrorMessage << "Windows failed to copy \"" << m_path_source << "\" to \"" << m_path_target << "\": " << errorMessage << "in File" << __FILE__;
			WindowsUtil::Print(decoratedErrorMessage.str().c_str());
		}
	}
	return !wereThereErrors;
}