#include "ServerPlayerController.h"
#include "../../../Engine/Core/NetworkManager/NetworkManager.h"
#include "../../../Engine/Core/EngineCore/Objects/Scene.h"
#include "../../../Engine/Windows/WindowsFunctions.h"

void Game::ServerPlayerController::updateObject(Engine::Object& iObject, 
	Engine::typedefs::ActionWithKeyBound iAction)
{
	//WindowsUtil::Assert(false, Engine::Networking::NetworkManager::getCurrentMessageString());
	/*if (!Engine::Networking::NetworkManager::isServerInstance()
		&& Engine::Networking::NetworkManager::getCurrentMessage() ==
		Engine::Networking::RECEIVE_TRANSFORM)
	{
		if (!iObject.isRenderable())
			iObject.setRenderable(true);
		Engine::Networking::NetworkPacket mTempNetworkPacket =
			Engine::Networking::NetworkManager::getReceivedNetworkPacket();
		iObject.setTransform(mTempNetworkPacket.mTransformData.getPosition(),
			mTempNetworkPacket.mTransformData.getOrientation());
	}*/
}
