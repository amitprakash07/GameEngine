#include "RotateObject.h"
#include "../../Engine/Core/EngineCore/Objects/Object.h"
#include "../../Engine/Core/EngineCore/Objects/Scene.h" 
#include "../../Engine/Core/Maths/Functions.h"


void Application::ObjectRotateController::updateObject(Engine::Object& iObject, Engine::typedefs::ActionWithKeyBound iAction)
{

	Engine::Math::Transform transform = iObject.getTransform();
	Engine::Math::Vector3 tempPosition = transform.getPosition();
	Engine::SharedPointer<Engine::Time::FrameTime> timer = Engine::Scene::getTimer();
	Engine::Math::Vector3 upVector = Engine::Math::Matrix4x4(transform.getOrientation(), transform.getPosition()).getInverse().mul(Engine::Math::Vector3(0,1,0));
	transform.rotate(Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(timer->getdeltaTime()*100.0f), 
		Engine::Math::Vector3(0, 1, 0)));

	iObject.setTransform(tempPosition, transform.getOrientation());
}



