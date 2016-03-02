#include "CameraController.h"
#include "../../Engine/Core/EngineCore/Objects/Object.h"
#include "../../Engine/Core/Maths/Vector3.h"

void Application::CameraController::updateObject(Engine::Object& iObject, Engine::typedefs::Action iAction)
{
	Engine::Math::Transform Transform= iObject.getTransform();
	switch (iAction)
	{
	case Engine::typedefs::MoveForward:
		Transform.mPositionOffset += Engine::Math::Vector3(0.0f, 0.0f, -1.0f);
	break;
	case Engine::typedefs::MoveBackWard:
		Transform.mPositionOffset += Engine::Math::Vector3(0.0f, 0.0f, 1.0f);
	break;
	case Engine::typedefs::MoveLeft:
		Transform.mPositionOffset += Engine::Math::Vector3(-1.0f, 0.0f, 0.0f);
	break;
	case Engine::typedefs::MoveRight:
		Transform.mPositionOffset += Engine::Math::Vector3(1.0f, 0.0f, 0.0f);
	break;
	default:
	break;
	}
	iObject.setTransform(Transform.mPositionOffset, Transform.mOrientation);
}



