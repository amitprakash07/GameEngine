#include "WalkController.h"
#include "../../../Engine/Core/EngineCore/Objects/Object.h"
#include "../../../Engine/Core/Maths/Vector3.h"
#include "../../../InteractiveCG/ObjectController/WalkController.h"
#include "../../../Engine/Core/Maths/Transform.h"
#include "../../../Engine/Core/Maths/Functions.h"
#include "../../../Engine/Graphics/SSAO.h"
#include "../../../Engine/Core/NetworkManager/NetworkManager.h"

using namespace Engine::Math;
void Game::WalkController::updateObject(Engine::Object& iObject, Engine::typedefs::ActionWithKeyBound iAction)
{
	Engine::Math::Transform transform = iObject.getTransform();
	Quaternion leftRotor = Quaternion(ConvertDegreesToRadians(-3), Vector3(0, 1, 0));
	Quaternion rightRotor = Quaternion(ConvertDegreesToRadians(3), Vector3(0, 1, 0));
	Quaternion upRotor = Quaternion(ConvertDegreesToRadians(-3), Vector3(1, 0, 0));
	Quaternion downRotor = Quaternion(ConvertDegreesToRadians(3), Vector3(1, 0, 0));
	Vector3 forwardVector = Matrix4x4(transform.getOrientation(),
		transform.getPosition()).getInverse().mul(Vector3(0.0f, 0.0f, 1.0f)).CreateNormalized();
	bool isUpdate = false;
	switch (iAction.keyVal)
	{
	case VK_PRIOR:
		//Page up - camera up
		transform.setPosition(transform.getPosition() + Vector3(0, 2.0, 0));
		iObject.setTransform(transform.getPosition(), transform.getOrientation());
		isUpdate = true;
		break;
	case VK_NEXT:
		//Page Down - camera down
		transform.setPosition(transform.getPosition() + Vector3(0, -2.0, 0));
		iObject.setTransform(transform.getPosition(), transform.getOrientation());
		isUpdate = true;
		break;
	case 0x5A:
		//z - key - camera left
		transform.setPosition(transform.getPosition() + Vector3(-2.0, 0, 0));
		iObject.setTransform(transform.getPosition(), transform.getOrientation());
		isUpdate = true;
		break;
	case 0x58:
		//X Key - right
		transform.setPosition(transform.getPosition() + Vector3(2.0, 0, 0));
		iObject.setTransform(transform.getPosition(), transform.getOrientation());
		isUpdate = true;
		break;
	case 0x46:
		//f key - forward
		transform.setPosition(transform.getPosition() + Vector3(0, 0, -2.0));
		iObject.setTransform(transform.getPosition(), transform.getOrientation());
		isUpdate = true;
		break;
	case 0x42:
		//B key - backward
		transform.setPosition(transform.getPosition() + Vector3(0, 0, 2.0));
		iObject.setTransform(transform.getPosition(), transform.getOrientation());
		isUpdate = true;
		break;
	case 0x41:
		//A key
		leftRotor = leftRotor * transform.getOrientation();
		transform.setOrientation(leftRotor);
		iObject.setTransform(transform.getPosition(), transform.getOrientation());
		isUpdate = true;
		break;
	case 0x44:
		//D Key
		rightRotor = rightRotor * transform.getOrientation();
		transform.setOrientation(rightRotor);
		iObject.setTransform(transform.getPosition(), transform.getOrientation());
		isUpdate = true;
		break;
	case 0x51:
		//Q Key
		upRotor = upRotor * transform.getOrientation();
		transform.setOrientation(upRotor);
		iObject.setTransform(transform.getPosition(), transform.getOrientation());
		isUpdate = true;
		break;
	case 0x45:
		//E Key
		downRotor = downRotor * transform.getOrientation();
		transform.setOrientation(downRotor);
		iObject.setTransform(transform.getPosition(), transform.getOrientation());
		isUpdate = true;
		break;
	case 0x52:
		//R Key
		iObject.resetTransform();
		isUpdate = true;
	case VK_OEM_PLUS:
		//+ key - increasr radius
		Engine::Graphics::SSAO::IncreaseRadius();
		isUpdate = false;
		break;
	case VK_OEM_MINUS:
		// - Key - decrease radius
		Engine::Graphics::SSAO::DecreaseRadius();
		isUpdate = false;
		break;
	case VK_INSERT:
		//insert Key -- increase ambient light Intensity
		Engine::Graphics::SSAO::IncreaseAmbientIntensity();
		isUpdate = false;
		break;
	case VK_DELETE:
		//Delete Key -- decrease ambient light intensity
		Engine::Graphics::SSAO::DecreaseAmbientIntensity();
		isUpdate = false;
		break;
	case 0x54:
		//T Key - Toggle occlusion image only
		Engine::Graphics::SSAO::ToggleColorToOnlyAmbient();
		isUpdate = false;
		break;
	}
	if (isUpdate)
	{
		RakNet::RakPeerInterface *tempPeer;
		if (Engine::Networking::NetworkManager::isServerInstance())
		{
			tempPeer = Engine::Networking::NetworkManager::GetHandler().mServer->mServer;
			Engine::Networking::NetworkManager::GetHandler().mClient->GetControlPlayer()->SendNetworkPlayerUpdates(tempPeer);
		}
		else
		{
			tempPeer = Engine::Networking::NetworkManager::GetHandler().mClient->client;
			Engine::Networking::NetworkManager::GetHandler().mClient->GetControlPlayer()->SendNetworkPlayerUpdates(tempPeer);
		}
	}
}



