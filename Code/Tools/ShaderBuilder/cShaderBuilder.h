/*
	This class builds shaders
*/

#ifndef _CSHADERBUILDER_H
#define _CSHADERBUILDER_H

// Header Files
//=============

#include "../BuilderHelper/cbBuilder.h"

// Class Declaration
//==================

namespace Tools
{
	namespace AssetBuilder
	{
		class cShaderBuilder : public cbBuilder
		{
			// Interface
			//==========

		public:

			// Build
			//------

			virtual bool Build(const std::vector<std::string>& i_arguments) override;
		};
	}
}

#endif	// _CSHADERBUILDER_H
