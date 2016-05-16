#include "../../../Engine/Core/EngineCore/Objects/Object.h"
#include "../../../Engine/Core/Maths/Transform.h"
#include "../../../Engine/Core/Maths/Functions.h"
#include "../../../Engine/Core/Physics/PhysicsSystem.h"
#include "../../../Engine/Windows/WindowsFunctions.h"
#include "../../../Engine/Core/Debugging/DebugShapes.h"
#include "../../../Engine/Core/EngineCore/Objects/Scene.h"
#include "../../../Engine/Core/NetworkManager/NetworkManager.h"
#include "ServerPlayerController.h"

bool Game::ServerPlayerController::isLineInitialized = false;
Engine::Math::Vector3 Game::ServerPlayerController::velocity = Engine::Math::Vector3(0.0f);
Engine::Math::Vector3 Game::ServerPlayerController::acceleration = Engine::Math::Vector3(0.0f);
float Game::ServerPlayerController::mass = 10.0f;
Engine::Math::Vector3 Game::ServerPlayerController::gravity = Engine::Math::Vector3(0.0f, -9.8f, 0.0f);
Engine::Math::Vector3 Game::ServerPlayerController::Force = Engine::Math::Vector3(0.0f, 0.0f, 0.0f);
float Game::ServerPlayerController::heightOffset = 10.0f;
Engine::SharedPointer<Engine::Graphics::Line>
Game::ServerPlayerController::shootRay;
float Game::ServerPlayerController::groundOffset = 10.0f;
float Game::ServerPlayerController::cameraHeightOffset = 150.0f;
float Game::ServerPlayerController::cameraDistanceToMaintainFromPlayer = 350.0f;
bool Game::ServerPlayerController::flyCam = false;
Engine::Math::Transform Game::ServerPlayerController::leftPlayerCameraTransform;

using namespace Engine::Math;
void Game::ServerPlayerController::updateObject(Engine::Object& iObject, Engine::typedefs::ActionWithKeyBound iAction)
{
	Engine::SharedPointer<Engine::Camera> followUpCamera =
		Engine::Scene::getRenderableScene()->getActiveCamera();
	Engine::Math::Transform cameraTransform = followUpCamera->getTransform();
	Engine::Math::Vector3 cameraPosition = cameraTransform.getPosition();

	Transform currentObjectTransform =
		iObject.getTransform();
	bool isUpdate = false;

	float  delta = Engine::Scene::getRenderableScene()->getTimer()->getdeltaTime();
	float offset = 200.0f;
	float distanceToMainTainFromCollidable = 50.0f;

	if (shootRay.isNull())
	{
		Engine::SharedPointer<Engine::Graphics::Line>
			tempRayLine = Engine::Graphics::Line::AddLine(
				Vector3(), Vector3(),
				Engine::Graphics::RGBAColor(1, 1, 1, 1));
		shootRay = tempRayLine;
	}

	Engine::Physics::HitInfo groundHitInfo;
	Vector3 currentObjectPosition = currentObjectTransform.getPosition();
	bool handleKeyThisFrame = true;
	Vector3 moveTowardsGround = Vector3(0.0f);
	Vector3 moveTowardsForward = Vector3(0.0f);
	//Handle Gravity
	{
		shootRay->mLineStruct.startPoint = currentObjectPosition;
		shootRay->mLineStruct.endPoint = currentObjectPosition
			+ Vector3(0, -1, 0) * groundOffset; //arbitray Value

		if (!Engine::Physics::PhysicsSystem::GetPhysicsSystem()->CheckCollision(
			shootRay->mLineStruct.startPoint,
			shootRay->mLineStruct.endPoint,
			groundHitInfo))
		{
			std::string tempName = "ray";
			WindowsUtil::displayToOutPutWindow("Intersection Happening");
			moveTowardsGround = Vector3(0, -delta*offset, 0);
		}
	}


	if (handleKeyThisFrame)
	{
		shootRay->mLineStruct.startPoint = currentObjectPosition + currentObjectTransform.getUpVector() * heightOffset;
		shootRay->mLineStruct.endPoint = shootRay->mLineStruct.startPoint +
			currentObjectTransform.getForwardVector() * distanceToMainTainFromCollidable;
		switch (iAction.keyVal)
		{
		case 0x57:
		{
			//W - key				
			Engine::Physics::HitInfo forWardHitInfo;
			forWardHitInfo.distance = BIG_FLOAT;
			if (Engine::Physics::PhysicsSystem::GetPhysicsSystem()->CheckCollision(
				shootRay->mLineStruct.startPoint,
				shootRay->mLineStruct.endPoint,
				forWardHitInfo))
			{
				Vector3 checkNextPosition = currentObjectPosition
					+ currentObjectTransform.getForwardVector() * (delta *offset);

				bool collisionResolutionRequiredThisFrame =
					(forWardHitInfo.hitPoint - shootRay->mLineStruct.endPoint).GetLength() > distanceToMainTainFromCollidable ? false : true;

				if (collisionResolutionRequiredThisFrame)
				{
					Engine::Math::Vector3 forwardVector =
						currentObjectTransform.getForwardVector() - forWardHitInfo.normal *
						currentObjectTransform.getForwardVector().dot(forWardHitInfo.normal);
					forwardVector.Normalize();
					moveTowardsForward = forwardVector*delta*offset;
				}
				else
					moveTowardsForward = currentObjectTransform.getForwardVector() * (delta*offset);
			}
			else
			{
				moveTowardsForward = currentObjectTransform.getForwardVector() * (delta*offset);
			}
			isUpdate = true;
		}
		break;
		case 0x53:
			//S Key - 
			moveTowardsForward = -currentObjectTransform.getForwardVector() * (delta*offset);
			isUpdate = true;
			break;
		case 0x41:
			//A key - forward
			currentObjectTransform.Rotate(Engine::Math::ConvertDegreesToRadians(-3), Up);			
			isUpdate = true;
			break;
		case 0x44:
			//D key - backward
			currentObjectTransform.Rotate(Engine::Math::ConvertDegreesToRadians(3), Up);			
			isUpdate = true;
			break;
		case VK_LEFT:
			cameraTransform.Rotate(Engine::Math::ConvertDegreesToRadians(-3), Up);
			break;
		case VK_RIGHT:
			cameraTransform.Rotate(Engine::Math::ConvertDegreesToRadians(3), Up);
			break;
		
		}
	}

	currentObjectTransform.setPosition(currentObjectPosition + moveTowardsGround + moveTowardsForward);
	cameraPosition = currentObjectTransform.getPosition() +
		Vector3(0, cameraHeightOffset, 0) + Vector3(0, 0, cameraDistanceToMaintainFromPlayer);
	cameraTransform.setPosition(cameraPosition);
	followUpCamera->setTransform(cameraTransform.getPosition(), cameraTransform.getOrientation());
	iObject.setTransform(currentObjectTransform.getPosition(),
		currentObjectTransform.getOrientation());

	if (isUpdate)
	{
		RakNet::RakPeerInterface *tempPeer;
		if (Engine::Networking::NetworkManager::isServerInstance())
		{
			tempPeer = Engine::Networking::NetworkManager::GetHandler().mServer->mServer;
			Engine::Networking::NetworkManager::GetHandler().mServer->GetControlPlayer()->SendNetworkPlayerUpdates(tempPeer);
		}
		else
		{
			tempPeer = Engine::Networking::NetworkManager::GetHandler().mClient->client;
			std::vector<Engine::SharedPointer<Engine::Networking::NetworkPlayer>> networkPlayerList =
				Engine::Networking::NetworkManager::GetHandler().mClient->GetControlPlayer();
			for(std::vector<Engine::SharedPointer<Engine::Networking::NetworkPlayer>>::iterator i = networkPlayerList.begin();
				i!= networkPlayerList.end(); ++i)
			{
				(*i)->SendNewNetworkPlayer(tempPeer);
			}
		}
	}
}



