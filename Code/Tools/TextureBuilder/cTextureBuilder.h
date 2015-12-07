/*
	This class builds textures
*/

#ifndef _CTEXTUREBUILDER_H
#define _CTEXTUREBUILDER_H

// Header Files
//=============

#include "../BuilderHelper/cbBuilder.h"

// Class Declaration
//==================

namespace Tools
{
	namespace AssetBuilder
	{
		class cTextureBuilder : public cbBuilder
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

#endif	// EAE6320_CTEXTUREBUILDER_H
