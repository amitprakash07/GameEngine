#include "NetworkManager.h"
#include "../../../Externals/Raknet/src/BitStream.h"
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
			mNetworkManager->mNetworkDetail.serverPort = SERVER_PORT;
			mNetworkManager->mSocketDetail = 
				RakNet::SocketDescriptor(mNetworkManager->mNetworkDetail.serverPort, 0);
			mNetworkManager->mPeerInterface->Startup(MAX_CLIENTS, &mNetworkManager->mSocketDetail, 1);
			mNetworkManager->mPeerInterface->SetMaximumIncomingConnections(MAX_CLIENTS);
			break;
		case false:
			mNetworkManager->mNetworkDetail.maxClient = MAX_CLIENTS;
			mNetworkManager->mSocketDetail = RakNet::SocketDescriptor();
			mNetworkManager->mPeerInterface->Startup(1, &mNetworkManager->mSocketDetail, 1);
			mNetworkManager->mPeerInterface->Connect(iServerAddress.c_str(), SERVER_PORT, 0, 0);			
		}
	}
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
	RakNet::Packet* tempPacket;
	
	for(tempPacket = mNetworkManager->mPeerInterface->Receive();
		tempPacket; tempPacket = mNetworkManager->mPeerInterface->Receive())
	{
		switch (tempPacket->data[0])
		{
			case ID_CONNECTION_REQUEST_ACCEPTED:
			{
				//when client gets connected by Server
				WindowsUtil::Assert(false, "Packet Received");
				RakNet::BitStream sendingStream;
				sendingStream.Write(RECEIVE_TRANSFORM);
				Math::Vector3 tempPosition = 
					mNetworkManager->sendingNetworkPacket.mTransformData.getPosition();
				Math::Quaternion tempOrientation = 
					mNetworkManager->sendingNetworkPacket.mTransformData.getOrientation();

				//position
				sendingStream.Write(tempPosition.x);
				sendingStream.Write(tempPosition.y);
				sendingStream.Write(tempPosition.z);
				//Orientation
				sendingStream.Write(tempOrientation.w());
				sendingStream.Write(tempOrientation.x());
				sendingStream.Write(tempOrientation.y());
				sendingStream.Write(tempOrientation.z());
				mNetworkManager->currentGameMessage = CLIENT_REQUEST_ACCEPTED;
				mNetworkManager->mPeerInterface->Send(&sendingStream,
					HIGH_PRIORITY, UNRELIABLE, 0, tempPacket->systemAddress, false);
			}
			break;
			case RECEIVE_TRANSFORM:
			{
				//Receiving Data - from client or server
				RakNet::BitStream receivingStream(tempPacket->data, tempPacket->length, false);
				receivingStream.IgnoreBytes(sizeof(RakNet::MessageID));
				Math::Vector3 tempReceivePosition;
				Math::Quaternion tempReceiveOrientation;
				float x, y, z;				
				receivingStream.Read(x);
				receivingStream.Read(y);
				receivingStream.Read(z);
				float mW, mX, mY, mZ;
				receivingStream.Read(mW);
				receivingStream.Read(mX);
				receivingStream.Read(mY);
				receivingStream.Read(mZ);
				tempReceivePosition = Math::Vector3(x, y, z);
				tempReceiveOrientation.w(mW);
				tempReceiveOrientation.x(mX);
				tempReceiveOrientation.y(mY);
				tempReceiveOrientation.z(mZ);
				
				mNetworkManager->receivingNetworkPacket = NetworkPacket(tempReceivePosition,
					tempReceiveOrientation);

				//Sending Data - Client or Server
				RakNet::BitStream sendingStream;
				sendingStream.Write(RECEIVE_TRANSFORM);
				Math::Vector3 tempPosition = 
					mNetworkManager->sendingNetworkPacket.mTransformData.getPosition();
				Math::Quaternion tempOrientation = 
					mNetworkManager->sendingNetworkPacket.mTransformData.getOrientation();

				//position
				sendingStream.Write(tempPosition.x);
				sendingStream.Write(tempPosition.y);
				sendingStream.Write(tempPosition.z);
				//Orientation
				sendingStream.Write(tempOrientation.w());
				sendingStream.Write(tempOrientation.x());
				sendingStream.Write(tempOrientation.y());
				sendingStream.Write(tempOrientation.z());

				mNetworkManager->currentGameMessage = RECEIVE_TRANSFORM;
				mNetworkManager->mPeerInterface->Send(&sendingStream,
					HIGH_PRIORITY, UNRELIABLE, 0, tempPacket->systemAddress, false);

			}
		}
	}
}


Engine::Networking::GameMessages Engine::Networking::NetworkManager::getCurrentMessage()
{
	return mNetworkManager->currentGameMessage;
}


void Engine::Networking::NetworkManager::ShutDownNetwork()
{
	RakNet::RakPeerInterface::DestroyInstance(
		reinterpret_cast<RakNet::RakPeerInterface*>(
			mNetworkManager->mPeerInterface.getRawPointer()));
}


Engine::Networking::NetworkManager::NetworkManager()
{
	mIsServer = false;
	SharedPointer<RakNet::RakPeerInterface> temp = SharedPointer<RakNet::RakPeerInterface>(
		RakNet::RakPeerInterface::GetInstance(), "RakNet::Network");
	mPeerInterface = temp;
	currentGameMessage = UNKNOWN;
}


