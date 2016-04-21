#include "ClientPlayerController.h"
#include "../../../Engine/Core/EngineCore/Objects/Object.h"
#include "../../../Engine/Core/NetworkManager/NetworkManager.h"

void Game::ClientPlayerController::updateObject(Engine::Object& iObject, 
	Engine::typedefs::ActionWithKeyBound iAction)
{
	if(Engine::Networking::NetworkManager::isServerInstance()
		&& Engine::Networking::NetworkManager::getCurrentMessage()== 
		Engine::Networking::CLIENT_REQUEST_ACCEPTED)
	{
		iObject.setRenderable(true);
		Engine::Networking::NetworkPacket mTempNetworkPacket =
			Engine::Networking::NetworkManager::getReceivedNetworkPacket();
		iObject.setTransform(mTempNetworkPacket.mTransformData.getPosition(),
			mTempNetworkPacket.mTransformData.getOrientation());		
	}
}