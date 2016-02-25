#include "CameraController.h"
#include "../../Engine/Core/EngineCore/Objects/Object.h"
#include "../../Engine/Core/Maths/Vector3.h"

void Application::CameraController::updateObject(Engine::Object& iObject, Engine::typedefs::Action iAction)
{
	Engine::Math::Transformation transformation= iObject.getTransformation();
	switch (iAction)
	{
	case Engine::typedefs::MoveForward:
		transformation.mPositionOffset += Engine::Math::Vector3(0.0f, 0.0f, -1.0f);
	break;
	case Engine::typedefs::MoveBackWard:
		transformation.mPositionOffset += Engine::Math::Vector3(0.0f, 0.0f, 1.0f);
	break;
	case Engine::typedefs::MoveLeft:
		transformation.mPositionOffset += Engine::Math::Vector3(-1.0f, 0.0f, 0.0f);
	break;
	case Engine::typedefs::MoveRight:
		transformation.mPositionOffset += Engine::Math::Vector3(1.0f, 0.0f, 0.0f);
	break;
	default:
	break;
	}
	iObject.setTransformation(transformation.mPositionOffset, transformation.mOrientation);
}



