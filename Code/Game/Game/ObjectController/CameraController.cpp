#include "CameraController.h"
#include "../../../Engine/Core/EngineCore/Objects/Object.h"
#include "../../../Engine/Core/Maths/Transform.h"

#include "../../../Engine/Core/EngineCore/Objects/Scene.h"
#include "../../../Engine/Core/Maths/Functions.h"


void Game::CameraController::updateObject(Engine::Object& iObject,
	Engine::typedefs::ActionWithKeyBound iAction)
{
	Engine::Math::Transform transform = iObject.getTransform();
	Engine::Math::Quaternion leftRotor = 
		Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(-3), 
			Engine::Math::Vector3(0, 1, 0));

	Engine::Math::Quaternion rightRotor = 
		Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(3), 
			Engine::Math::Vector3(0, 1, 0));
	
	Engine::Math::Quaternion upRotor = 
		Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(-3), 
			Engine::Math::Vector3(1, 0, 0));
	
	Engine::Math::Quaternion downRotor = 
		Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(3),
			Engine::Math::Vector3(1, 0, 0));

	switch (iAction.keyVal)
	{
	case VK_UP:
		//Page up - camera up
		transform.setPosition(transform.getPosition() + Engine::Math::Vector3(0, 0.5, 0));
		iObject.setTransform(transform.getPosition(), transform.getOrientation());
		break;
	case VK_DOWN:
		//Page Down - camera down
		transform.setPosition(transform.getPosition() + Engine::Math::Vector3(0, -0.5, 0));
		iObject.setTransform(transform.getPosition(), transform.getOrientation());
		break;
	case VK_LEFT:
		//z - key - camera left
		transform.setPosition(transform.getPosition() + Engine::Math::Vector3(-0.5, 0, 0));
		iObject.setTransform(transform.getPosition(), transform.getOrientation());
		break;
	case VK_RIGHT:
		//X Key - right
		transform.setPosition(transform.getPosition() + Engine::Math::Vector3(0.5, 0, 0));
		iObject.setTransform(transform.getPosition(), transform.getOrientation());
		break;
	case 0x57:
		//f key - forward
		transform.setPosition(transform.getPosition() + Engine::Math::Vector3(0, 0, -0.5));
		iObject.setTransform(transform.getPosition(), transform.getOrientation());
		break;
	case 0x53:
		//B key - backward
		transform.setPosition(transform.getPosition() + Engine::Math::Vector3(0, 0, 0.5));
		iObject.setTransform(transform.getPosition(), transform.getOrientation());
		break;
	case 0x41:
		//A key
		leftRotor = leftRotor * transform.getOrientation();
		transform.setOrientation(leftRotor);
		iObject.setTransform(transform.getPosition(), transform.getOrientation());
		break;
	case 0x44:
		//D Key
		rightRotor = rightRotor * transform.getOrientation();
		transform.setOrientation(rightRotor);
		iObject.setTransform(transform.getPosition(), transform.getOrientation());
		break;
	case 0x51:
		//Q Key
		upRotor = upRotor * transform.getOrientation();
		transform.setOrientation(upRotor);
		iObject.setTransform(transform.getPosition(), transform.getOrientation());
		break;
	case 0x45:
		//E Key
		downRotor = downRotor * transform.getOrientation();
		transform.setOrientation(downRotor);
		iObject.setTransform(transform.getPosition(), transform.getOrientation());
		break;
	case 0x52:
		//R Key
		iObject.resetTransform();
	}
}



