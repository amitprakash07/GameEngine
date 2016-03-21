#include "WalkController.h"
#include "../../Engine/Core/EngineCore/Objects/Object.h"
#include "../../Engine/Core/Maths/Vector3.h"
#include "../../Engine/Core/Maths/Functions.h"
#include "../../Engine/Core/EngineCore/Objects/Scene.h"

using namespace Engine::Math;
void Application::WalkController::updateObject(Engine::Object& iObject, Engine::typedefs::ActionWithKeyBound iAction)
{
	Engine::Math::Transform transform= iObject.getTransform();
	switch (iAction.keyVal)
	{
	case VK_UP:
		transform.setPosition(transform.getPosition() + Vector3(0, 0.5, 0));
		break;
	case VK_DOWN:
		transform.setPosition(transform.getPosition() + Vector3(0, -0.5, 0));
		break;
	case VK_LEFT:
		transform.setPosition(transform.getPosition() + Vector3(-0.5, 0, 0));
		break;
	case VK_RIGHT:
		transform.setPosition(transform.getPosition() + Vector3(0.5, 0, 0));
		break;
	}
	
	iObject.setTransform(transform.getPosition(), transform.getOrientation());
}



