#include "NetworkManager.h"
#include "../../Windows/WindowsFunctions.h"

Engine::SharedPointer<Engine::Networking::NetworkManager>
	Engine::Networking::NetworkManager::mNetworkManager;

void Engine::Networking::NetworkManager::CreateNetworkManager(bool i_isServer,
	std::string iServerAddress)
{
	if(mNetworkManager.isNull())
	{
		SharedPointer<NetworkManager> temp = SharedPointer<NetworkManager>(
			new NetworkManager(), "NetworkManager");
		mNetworkManager = temp;
		mNetworkManager->mIsServer = i_isServer;

		switch(i_isServer)
		{
		case true:	
			mNetworkManager->mSystem.mServer->CreateServerInterface();
			mNetworkManager->mSystem.mServer->ServerStartUp();
			break;
		case false:
			mNetworkManager->mSystem.mClient->CreateClientInterface();
			mNetworkManager->mSystem.mClient->SetIP();
			mNetworkManager->mSystem.mClient->ClientStartup();			
			break;						
		}
	}
}

Engine::Networking::Handler Engine::Networking::NetworkManager::GetHandler()
{
	return mNetworkManager->mSystem;
}


Engine::Networking::NetworkPacket Engine::Networking::NetworkManager::getReceivedNetworkPacket()
{
	return mNetworkManager->receivingNetworkPacket;
}

void Engine::Networking::NetworkManager::setSendingNetworkPacket(NetworkPacket iSendingNetworkPacket)
{
	mNetworkManager->sendingNetworkPacket = iSendingNetworkPacket;
}

bool Engine::Networking::NetworkManager::isServerInstance()
{
	return mNetworkManager->mIsServer;
}

void Engine::Networking::NetworkManager::updateNetwork()
{	
	switch (mNetworkManager->isServerInstance())
	{
	case true:
		mNetworkManager->mSystem.mServer->ReceivePackets();
		break;
	case false:
		mNetworkManager->mSystem.mClient->ReceivePackets();
		break;
	}
}

Engine::Networking::GameMessages Engine::Networking::NetworkManager::getCurrentMessage()
{
	return mNetworkManager->currentGameMessage;
}

std::string Engine::Networking::NetworkManager::getCurrentMessageString()
{
	return "";
}

void Engine::Networking::NetworkManager::ShutDownNetwork()
{
	
}

Engine::Networking::NetworkManager::NetworkManager()
{
	mIsServer = false;		
	isConnected = false;
	Handler tempHandler = Handler();
	mSystem = tempHandler;
}


