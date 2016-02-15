#ifndef __CAMERA_CONTROLLER_H
#define __CAMERA_CONTROLLER_H

#include "../../Utilities/IObjectController.h"

namespace Engine
{
	class CameraController :public IObjectController
	{
	public:
		void updateObject(Object &i_Object, Engine::typedefs::Direction i_dir) override;
		std::string getTypeInfo() const override { return ""; }
		bool isBothSameType(RTTI*, std::string) const override { return true; }
		CameraController() {}
		~CameraController() {}
	private:


	};
}

#endif