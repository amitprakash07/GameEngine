#ifndef __WALK_CONTROLLER_H
#define __WALK_CONTROLLER_H

#include "../../Utilities/IObjectController.h"


namespace Engine
{
	class WalkController:public IObjectController
	{
	public:
		void updateGameObject(Object &i_gameObject, Engine::typedefs::Direction i_dir) override;
		std::string getTypeInfo() override { return ""; }
		bool isBothSameType(RTTI*, std::string) override { return true; }
		WalkController(){}
		~WalkController(){}
	private:
		
	};
}

#endif