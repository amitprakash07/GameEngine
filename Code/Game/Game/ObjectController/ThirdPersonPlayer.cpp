#include "ThirdPersonPlayer.h"
#include "../../../Engine/Core/EngineCore/Objects/Scene.h"
#include "../../../Engine/Core/Maths/Functions.h"
#include "../../../Engine/Windows/WindowsFunctions.h"
#include "../../../Engine/Core/Physics/RayIntersection.h"
#include "../../../Engine/Core/Physics/PhysicsSystem.h"

Engine::SharedPointer<Engine::Graphics::Line>
		Game::ThirdPersonPlayerController::shootRay;
Engine::Math::Transform Game::ThirdPersonPlayerController::transformBeforeTemporaryControl;
Engine::Math::Transform Game::ThirdPersonPlayerController::transformBeforeFlyCam;
float Game::ThirdPersonPlayerController::maxDistanceForTemporaryControl;
bool Game::ThirdPersonPlayerController::flyCam;
Engine::Math::Vector3 Game::ThirdPersonPlayerController::cameraOffset;


void Game::ThirdPersonPlayerController::updateObject(
	Engine::Object& iObject, 
	Engine::typedefs::ActionWithKeyBound iAction)
{
	Engine::SharedPointer<Engine::Camera> lazyCamera =
		Engine::Scene::getRenderableScene()->getActiveCamera();
	Engine::Math::Transform cameraTransform = lazyCamera->getTransform();
	Engine::Math::Vector3 lazyCameraPosition = cameraTransform.getPosition();
	Engine::Math::Quaternion oldRotation = cameraTransform.getOrientation();

	cameraOffset += Engine::Math::Vector3(0, 100, 100);	

	Engine::Math::Transform playerTransform = iObject.getTransform();
	Engine::Math::Vector3 playerPosition = playerTransform.getPosition();

	float delta = Engine::Scene::getRenderableScene()->getTimer()->getdeltaTime();
	float offset = 200.0f;
	float groundOffset = 10.0f;
	float heightOffset = 10.0f;
	float distanceToMainTainFromCollidable = 50.0f;
	float distanceThreshold = 100.0f;
	float rotationOffset = 0.0f;

	Engine::Math::Vector3 moveTowardsGround = Engine::Math::Vector3(0.0f);
	Engine::Math::Vector3 moveTowardsForward = Engine::Math::Vector3(0.0f);


	if (shootRay.isNull())
	{
		Engine::SharedPointer<Engine::Graphics::Line>
			tempRayLine = Engine::Graphics::Line::AddLine(
				Engine::Math::Vector3(), Engine::Math::Vector3(),
				Engine::Graphics::RGBAColor(1, 1, 1, 1));
		shootRay = tempRayLine;
	}

	if(!flyCam)
	{
		Engine::Physics::HitInfo groundHitInfo;
		Engine::Math::Vector3 currentObjectPosition = playerTransform.getPosition();
		bool handleKeyThisFrame = true;
		
		//Handle Gravity
		{
			shootRay->mLineStruct.startPoint = currentObjectPosition;
			shootRay->mLineStruct.endPoint = currentObjectPosition
				+ Engine::Math::Vector3(0, -1, 0) * groundOffset; //arbitray Value

			if (!Engine::Physics::PhysicsSystem::GetPhysicsSystem()->CheckCollision(
				shootRay->mLineStruct.startPoint,
				shootRay->mLineStruct.endPoint,
				groundHitInfo))
			{
				std::string tempName = "ray";
				WindowsUtil::displayToOutPutWindow("Intersection Happening");
				moveTowardsGround = Engine::Math::Vector3(0, -delta*offset, 0);
			}
		}

		shootRay->mLineStruct.startPoint = currentObjectPosition + playerTransform.getUpVector() * heightOffset;
		shootRay->mLineStruct.endPoint = shootRay->mLineStruct.startPoint +
			playerTransform.getForwardVector() * distanceToMainTainFromCollidable;

		switch(iAction.keyVal)
		{
		case VK_LEFT:
			rotationOffset = -45;
			break;
		case VK_RIGHT:
			rotationOffset = 45;
			break;
		case  VK_UP:
			playerTransform.MoveForward(delta*offset);//think
			break;
		case VK_DOWN:
			playerTransform.MoveBackWard(delta*offset);//think
			break;
		case 0x57:
			//w key
		{
			//W - key				
			Engine::Physics::HitInfo forWardHitInfo;
			forWardHitInfo.distance = BIG_FLOAT;
			if (Engine::Physics::PhysicsSystem::GetPhysicsSystem()->CheckCollision(
				shootRay->mLineStruct.startPoint,
				shootRay->mLineStruct.endPoint,
				forWardHitInfo))
			{
				Engine::Math::Vector3 checkNextPosition = currentObjectPosition
					+ playerTransform.getForwardVector() * (delta *offset);

				bool collisionResolutionRequiredThisFrame =
					(forWardHitInfo.hitPoint - shootRay->mLineStruct.endPoint).GetLength() > distanceToMainTainFromCollidable ? false : true;

				if (collisionResolutionRequiredThisFrame)
				{
					Engine::Math::Vector3 forwardVector =
						playerTransform.getForwardVector() - forWardHitInfo.normal *
						playerTransform.getForwardVector().dot(forWardHitInfo.normal);
					forwardVector.Normalize();
					moveTowardsForward = forwardVector*delta*offset;
				}
				else
					moveTowardsForward = playerTransform.getForwardVector() * (delta*offset);
			}
			else
			{
				moveTowardsForward = playerTransform.getForwardVector() * (delta*offset);
			}
		}
			break;
		case 0x53:
			//S Key - 			
			moveTowardsForward = -playerTransform.getForwardVector() * (delta*offset);
			break;
		case 0x41:
			//A key - Rotate			
			cameraTransform.Rotate(Engine::Math::ConvertDegreesToRadians(-3), Engine::Math::Up);
			break;
		case 0x44:
			//D key - Rotate
			cameraTransform.Rotate(Engine::Math::ConvertDegreesToRadians(3), Engine::Math::Up);
			break;
		case 0x46:
			flyCam = true;
			transformBeforeFlyCam = cameraTransform;
			break;	
		default:
			rotationOffset = 0;
		}

		playerTransform.setPosition(currentObjectPosition + moveTowardsGround + moveTowardsForward);		
		iObject.setTransform(playerTransform.getPosition(),
			playerTransform.getOrientation());
		lazyCamera->setTransform(cameraTransform.getPosition(), oldRotation);
	}
	else
	{
		switch (iAction.keyVal)
		{
		case 0x57:
			//w key
			cameraTransform.MoveForward(delta * offset);
			break;
		case 0x53:
			//S Key - 			
			cameraTransform.MoveBackWard(delta*offset);
			break;
		case 0x41:
			//A key - Rotate			
			cameraTransform.MoveLeft(delta*offset);
			break;
		case 0x44:
			//D key - Rotate
			cameraTransform.MoveRight(delta*  offset);
			break;
		case VK_LEFT:
			cameraTransform.Rotate(Engine::Math::ConvertDegreesToRadians(-3), Engine::Math::Up);
			break;
		case VK_RIGHT:
			cameraTransform.Rotate(Engine::Math::ConvertDegreesToRadians(3), Engine::Math::Up);
			break;
		case 0x46:
			//FKey
			flyCam = false;		
			cameraTransform = transformBeforeFlyCam;
			break;
		}
		iObject.setTransform(playerTransform.getPosition(), playerTransform.getOrientation());
		lazyCamera->setTransform(cameraTransform.getPosition(), cameraTransform.getOrientation());
	}

	
}
