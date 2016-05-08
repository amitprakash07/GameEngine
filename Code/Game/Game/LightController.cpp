#include "LightController.h"
#include "../../Engine/Core/EngineCore/Objects/Object.h"
#include "../../Engine/Core/Maths/Vector3.h"
#include "../../Engine/Core/EngineCore/Objects/Scene.h"
#include "../../Engine/Core/Maths/Vec4.h"


using namespace Engine::Math;
void Game::LightController::updateObject(Engine::Object& iObject, Engine::typedefs::ActionWithKeyBound iAction)
{
	Engine::Graphics::Data lightPosition;
	Vector3 vecLightPosition = iObject.getTransform().getPosition();
	memcpy(&lightPosition.vec3, &vecLightPosition, 3 * sizeof(float));

	auto getMainLight = []()->Engine::SharedPointer<Engine::Graphics::Light>
	{
		std::vector<Engine::SharedPointer<Engine::Graphics::Light>> tempLightList
			= Engine::Scene::getRenderableScene()->getLightList();
		for (std::vector<Engine::SharedPointer<Engine::Graphics::Light>>::iterator i = tempLightList.begin();
			i != tempLightList.end(); ++i)
		{
			if ((*i)->getName() == "mainLight")
			{
				return (*i);
			}
		}
		return Engine::SharedPointer<Engine::Graphics::Light>();
	};

	Engine::SharedPointer<Engine::Graphics::Light> mainLight = getMainLight();
	mainLight->setLightParameterValue("lightPosition", 
		Engine::Graphics::DataTypes::vec3, lightPosition);

	float mainLightIntensity = mainLight->getLightIntensity();


	Engine::Math::Transform transform = iObject.getTransform();
	switch (iAction.keyVal)
	{
	case VK_UP:
		transform.setPosition(transform.getPosition() + Vector3(0, 0.5f, 0));
		iObject.setTransform(transform.getPosition(), transform.getOrientation());
		break;
	case VK_DOWN:
		transform.setPosition(transform.getPosition() + Vector3(0, -0.5f, 0));
		iObject.setTransform(transform.getPosition(), transform.getOrientation());
		break;
	case VK_LEFT:
		transform.setPosition(transform.getPosition() + Vector3(-0.5f, 0, 0));
		iObject.setTransform(transform.getPosition(), transform.getOrientation());
		break;
	case VK_RIGHT:
		transform.setPosition(transform.getPosition() + Vector3(0.5f, 0, 0));
		iObject.setTransform(transform.getPosition(), transform.getOrientation());
		break;
	case 0x57:
		//w key
		transform.setPosition(transform.getPosition() + Vector3(0, 0, -0.5f));
		iObject.setTransform(transform.getPosition(), transform.getOrientation());
		break;
	case 0x53:
		//S key
		transform.setPosition(transform.getPosition() + Vector3(0, 0, 0.5f));
		iObject.setTransform(transform.getPosition(), transform.getOrientation());
		break;
	case 0x52:
		//R Key
		iObject.resetTransform();
		break;
	case 0x4C:
		//L key
		mainLightIntensity += 0.2f;
		break;
	case 0x4B:
		//K Key
		mainLightIntensity -= 0.2f;
		break;
	}

	mainLight->setIntensity(mainLightIntensity);
}



