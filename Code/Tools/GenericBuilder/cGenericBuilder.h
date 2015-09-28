/*
	This is an example builder program that just copies the source file to the target path
	(as opposed to actually "building" it in some way so that the target is different than the source)
*/

#ifndef __GENERICBUILDER_H
#define __GENERICBUILDER_H

// Header Files
//=============

#include "../BuilderHelper/cbBuilder.h"

// Class Declaration
//==================

namespace Tools
{
	namespace AssetBuilder
	{
		class cGenericBuilder : public cbBuilder
		{
			// Interface
			//==========

		public:
			virtual bool Build(const std::vector<std::string>& i_arguments) override;
		};
	}
}

#endif	// __GENERICBUILDER_H
