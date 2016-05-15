#ifndef __THIRD_PERSON_PLAYER_CONTROLLER_H
#define __THIRD_PERSON_PLAYER_CONTROLLER_H


#include "../../../Engine/Core/Utilities/IObjectController.h"
#include "../../../Engine/Graphics/Line.h"

namespace Game
{
	class ThirdPersonPlayerController : public Engine::IObjectController
	{
	public:	
		static Engine::SharedPointer<Engine::Graphics::Line> shootRay;
		static Engine::Math::Transform transformBeforeTemporaryControl;
		static Engine::Math::Transform transformBeforeFlyCam;
		static float maxDistanceForTemporaryControl;
		static Engine::Math::Vector3 cameraOffset;

		static bool flyCam;
		void updateObject(Engine::Object &,
			Engine::typedefs::ActionWithKeyBound iAction) override;
	};
}


#endif
