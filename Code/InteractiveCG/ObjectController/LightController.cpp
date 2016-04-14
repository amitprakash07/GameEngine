#include "LightController.h"
#include "../../Engine/Core/EngineCore/Objects/Object.h"
#include "../../Engine/Core/Maths/Vector3.h"
#include "../../Engine/Core/Maths/Functions.h"
#include "../../Engine/Core/EngineCore/Objects/Scene.h"


using namespace Engine::Math;
void Application::LightController::updateObject(Engine::Object& iObject, Engine::typedefs::ActionWithKeyBound iAction)
{
	Engine::Math::Transform transform = iObject.getTransform();	
	switch (iAction.keyVal)
	{
	case VK_UP:
		transform.setPosition(transform.getPosition() + Vector3(0, 0.5, 0));
		iObject.setTransform(transform.getPosition(), transform.getOrientation());		
		break;
	case VK_DOWN:
		transform.setPosition(transform.getPosition() + Vector3(0, -0.5, 0));
		iObject.setTransform(transform.getPosition(), transform.getOrientation());
		break;
	case VK_LEFT:
		transform.setPosition(transform.getPosition() + Vector3(-0.5, 0, 0));
		iObject.setTransform(transform.getPosition(), transform.getOrientation());
		break;
	case VK_RIGHT:
		transform.setPosition(transform.getPosition() + Vector3(0.5, 0, 0));
		iObject.setTransform(transform.getPosition(), transform.getOrientation());
		break;
	case 0x57:
		//w key
		transform.setPosition(transform.getPosition() + Vector3(0, 0, -0.5));
		iObject.setTransform(transform.getPosition(), transform.getOrientation());
		break;
	case 0x53:
		//S key
		transform.setPosition(transform.getPosition() + Vector3(0, 0, 0.5));
		iObject.setTransform(transform.getPosition(), transform.getOrientation());
		break;	
	case 0x52:
		//R Key
		iObject.resetTransform();
	}
	

	Engine::Graphics::Data lightPosition;	
	Vector3 vecLightPosition = iObject.getTransform().getPosition();
	memcpy(&lightPosition.vec3, &vecLightPosition, 3 * sizeof(float));

	std::vector<Engine::SharedPointer<Engine::Graphics::Light>> tempLightList
		= Engine::Scene::getRenderableScene()->getLightList();
	for (std::vector<Engine::SharedPointer<Engine::Graphics::Light>>::iterator i = tempLightList.begin();
	i!=tempLightList.end(); ++i)
	{
		if((*i)->getName() == "mainLight")
		{
			(*i)->setLightParameterValue("lightPosition", Engine::Graphics::DataTypes::vec3,
				lightPosition);
		}
	}
	
}



