#include "CameraController.h"
#include "../../../Engine/Core/EngineCore/Objects/Object.h"
#include "../../../Engine/Core/Maths/Transform.h"
#include "../../../Engine/Core/Maths/Functions.h"
#include "../../../Engine/Core/EngineCore/Objects/Scene.h"

bool Game::CameraController::flyCam = false;
bool Game::CameraController::thirdPerson = true;
Engine::Math::Vector3 Game::CameraController::mForwardVector = Engine::Math::Vector3(0,0,-1);

void Game::CameraController::updateObject(Engine::Object& iObject,
	Engine::typedefs::ActionWithKeyBound iAction)
{
	Engine::Math::Vector3 cameraOffset;

	float angleRotation = 0.0f;	

	cameraOffset.x = cameraOffset.z = 0.0f;

	// Get the direction
	switch (iAction.keyVal)
	{
	case 0x57:
		//W
		cameraOffset.z -= 10.0f;
		thirdPerson = true;
		break;
	case 0x41:
		//A key
		angleRotation -= 0.0174533f;
		thirdPerson = true;
		break;
	case 0x53:
		//S Key
		cameraOffset.z += 10.0f;
		thirdPerson = true;
		break;
	case 0x44:
		//D Key
		angleRotation += 0.0174533f;
		thirdPerson = true;
		break;
	case 0x46:
		//F key
		flyCam = !flyCam;
		thirdPerson = false;
		break;
	}

	const float unitsToMove = Engine::Scene::getRenderableScene()->getTimer()->getdeltaTime();	
	cameraOffset.x *= unitsToMove;
	cameraOffset.y *= unitsToMove;
	cameraOffset.z *= unitsToMove;

	Engine::Math::Transform cameraTransform = iObject.getTransform();
	Engine::Math::Quaternion rotation = Engine::Math::Quaternion(angleRotation, Engine::Math::Vector3(0, 1, 0));
	rotation = cameraTransform.getOrientation() *  rotation;
	iObject.setTransform(cameraTransform.getPosition(), rotation);

	if(angleRotation != 0.0f)
	{
		Engine::Math::Matrix4x4 nonTranslationMatrix = Engine::Math::Matrix4x4(rotation, Engine::Math::Vector3(0.0f));
		Engine::Math::Vector3 forwardVector = Engine::Math::Vector3(0,0,-1);
		mForwardVector = nonTranslationMatrix.mul(mForwardVector); //forward Vector is 0,0,-1 -- Work On this
	}
	
	if(!flyCam)
	{
		Engine::Math::Transform playerTransform =
			Engine::Scene::getRenderableScene()->GetPlayer()->getTransform();
		Engine::Math::Vector3 oldLocation = playerTransform.getPosition();

		Engine::Math::Vector3 position = cameraOffset;
		position.y -= 5.0f;
		Engine::Math::Vector3 Zero = Engine::Math::Vector3(0.0f);
		Engine::Math::Matrix4x4 nonTranslationMatrix(iObject.getTransform().getOrientation(), Zero);
		Engine::Math::Vector3 movementVector = nonTranslationMatrix.mul(position);

		oldLocation += movementVector;
		playerTransform.setPosition(oldLocation);
		Engine::Scene::getRenderableScene()->GetPlayer()->setTransform(playerTransform.getPosition(), playerTransform.getOrientation());

		Engine::Math::Transform mTransform = iObject.getTransform();
		if(thirdPerson)
		{
			Engine::Math::Matrix4x4 i_localToWorldTransformBB8 = Engine::Math::Matrix4x4(mTransform.getOrientation(), mTransform.getPosition());
			Engine::Math::Vector3 camOffset = Engine::Math::Vector3(0, 10, 100);
			Engine::Math::Vector3 val = i_localToWorldTransformBB8.mul(camOffset);

			Engine::Math::Vector3 newPosition = mTransform.getPosition() + (val - mTransform.getPosition()) * unitsToMove * 5;
			mTransform.setPosition(newPosition);
		}
		else
		{
			Engine::Math::Vector3 temp = Engine::Math::Vector3(0.0f);
			Engine::Math::Matrix4x4 anotherNonTranslationMatrix = Engine::Math::Matrix4x4(mTransform.getOrientation(), temp);

			Engine::Math::Vector3 anotherMovementVector = nonTranslationMatrix.mul(mTransform.getPosition());
			Engine::Math::Vector3 newPosition = mTransform.getPosition() + movementVector;
			mTransform.setPosition(newPosition);
		}

		iObject.setTransform(mTransform.getPosition(), mTransform.getOrientation());
	}	
}



