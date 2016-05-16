#ifndef __SERVER_PLAYER_CONTROLLER_H
#define __SERVER_PLAYER_CONTROLLER_H

#include "../../../Engine/Core/Utilities/IObjectController.h"

namespace Game
{
	class ServerPlayerController:public Engine::IObjectController
	{
	public:
		static bool isLineInitialized;
		static Engine::Math::Vector3 gravity;
		static float mass;
		static float heightOffset;
		static Engine::Math::Vector3 Force;
		static float groundOffset;

		static float cameraHeightOffset;
		static float cameraDistanceToMaintainFromPlayer;
		static bool flyCam;
		static Engine::Math::Transform leftPlayerCameraTransform;

		//static Engine::SharedPointer<Engine::Graphics::Line> forwardVector;
		//static Engine::SharedPointer<Engine::Graphics::Line> rightVector;
		//static Engine::SharedPointer<Engine::Graphics::Line> upVector;
		static Engine::Math::Vector3 velocity;
		static Engine::Math::Vector3 acceleration;
		static Engine::SharedPointer<Engine::Graphics::Line> shootRay;
		void updateObject(Engine::Object &,
			Engine::typedefs::ActionWithKeyBound iAction) override;
	};
}

#endif