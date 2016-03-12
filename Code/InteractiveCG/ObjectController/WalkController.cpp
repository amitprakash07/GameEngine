#include "WalkController.h"
#include "../../Engine/Core/EngineCore/Objects/Object.h"
#include "../../Engine/Core/Maths/Vector3.h"
#include "../../Engine/Core/Maths/Functions.h"
#include "../../Engine/Core/EngineCore/Objects/Scene.h"

using namespace Engine::Math;
void Application::WalkController::updateObject(Engine::Object& iObject, Engine::typedefs::ActionWithKeyBound iAction)
{
	Engine::Math::Transform transform= iObject.getTransform();
	switch (iAction.action)
	{
	case Engine::typedefs::MoveForward:
		transform.setPosition(transform.getPosition() + Vector3(0,1,0));
		break;
	case Engine::typedefs::MoveBackWard:
		transform.setPosition(transform.getPosition() + Vector3(0, -1,0));		
		break;
	case Engine::typedefs::MoveLeft:
		transform.setPosition(transform.getPosition() + Vector3(1, 0, 0));		
		break;
	case Engine::typedefs::MoveRight:
		transform.setPosition(transform.getPosition() + Vector3(-1, 0, 0));		
		break;
	default:
		break;
	}
	
	switch(iAction.keyVal)
	{
	case 0x41:
		break;
	case 0x44:
		break;
	}
	
	/*Engine::SharedPointer<Engine::Time::FrameTime> timer = Engine::Scene::getTimer();
	Engine::Math::Vector3 upVector = Engine::Math::Matrix4x4(transform.getOrientation(), 
		transform.getPosition()).getInverse().mul(Engine::Math::Vector3(0, 1, 0));
	transform.rotate(Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(timer->getdeltaTime()*2.0f),
		Engine::Math::Vector3(0, 1, 0)));*/
	iObject.setTransform(transform.getPosition(), transform.getOrientation());
}



