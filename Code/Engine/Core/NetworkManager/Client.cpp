#include "Client.h"
#include "../../../Engine/Windows/WindowsFunctions.h"
#include "../../../Externals/Raknet/src/MessageIdentifiers.h"
#include "../../../Externals/Raknet/src/BitStream.h"
#include "NetworkDefs.h"
#include <iostream>

Engine::Networking::Client::Client(int iMaxPlayer)
{
	mNumSockets = 1;
	mNumIPs = 1;
	mMaxPlayers = iMaxPlayer;
	serverPort = "60001";
	mPacket = nullptr;
	client = nullptr;
}


void Engine::Networking::Client::ShutDownClient()
{
	client->Shutdown(300);
	RakNet::RakPeerInterface::DestroyInstance(client);
}


void Engine::Networking::Client::CreateClientInterface()
{
	client = RakNet::RakPeerInterface::GetInstance();
	if(!client)
	{
		WindowsUtil::Assert(client != nullptr, "Unable to create the client");
	}
	RakNet::SystemAddress clientID =
		RakNet::UNASSIGNED_SYSTEM_ADDRESS;
}


void Engine::Networking::Client::ClientStartup()
{
	mSocketDescriptor = RakNet::SocketDescriptor(
		atoi(clientPort.c_str()), 0);
	mSocketDescriptor.socketFamily = AF_INET;
	client->Startup(8, &mSocketDescriptor, 1);
	client->SetOccasionalPing(true);

	RakNet::ConnectionAttemptResult
		car = client->Connect(serverIP.c_str(), atoi(serverPort.c_str()),
			"admin", static_cast<int>(strlen("admin")));
	RakAssert(car == RakNet::CONNECTION_ATTEMPT_STARTED);
}


void Engine::Networking::Client::ReceivePackets() // in game loop
{
	for (mPacket = client->Receive(); mPacket; client->DeallocatePacket(mPacket),
		mPacket = client->Receive())
	{
		mPacketIdentifier = GetPacketIdentifier(mPacket);
		RakNet::BitStream receiveBitStream(mPacket->data,
			mPacket->length, false);
		RakNet::BitStream sendBitStream;
		switch (mPacketIdentifier)
		{
		case ID_DISCONNECTION_NOTIFICATION:
			WindowsUtil::displayToOutPutWindow("Network Disconnected\n");
			WindowsUtil::displayToOutPutWindow(
				mPacket->systemAddress.ToString(true));
			std::cout << "Network Disconnected  " << mPacket->systemAddress.ToString(true) << std::endl;;
			break;
		case ID_ALREADY_CONNECTED:
			WindowsUtil::displayToOutPutWindow("Already Conneccted\n");
			std::cout << "Already Connected\n";
			break;
		case ID_NEW_INCOMING_CONNECTION:
			WindowsUtil::displayToOutPutWindow("New Incoming Connection");
			std::cout << "New Incoming connection\n";
			break;
		case ID_INCOMPATIBLE_PROTOCOL_VERSION:
			WindowsUtil::displayToOutPutWindow("Incompatible Connection Protocol\n");
			std::cout << "Incompatible Connection Protocol\n";
			break;
		case ID_REMOTE_DISCONNECTION_NOTIFICATION:
			WindowsUtil::displayToOutPutWindow("Network Disconnected\n");
			std::cout << "Network Disconnected\n";
			break;
		case ID_REMOTE_NEW_INCOMING_CONNECTION:
			WindowsUtil::displayToOutPutWindow("New Incoming Connection\n");
			std::cout << "New Incoming Connection\n";
			break;
		case ID_CONNECTION_BANNED:
			WindowsUtil::displayToOutPutWindow("You are banned on this network\n");
			std::cout << "You are banned on this network\n";
			break;
		case ID_CONNECTION_ATTEMPT_FAILED:
			WindowsUtil::displayToOutPutWindow("Connection Attempt failed");
			std::cout << "Connection Attempt failed";
			break;
		case ID_CONNECTION_LOST:
			WindowsUtil::displayToOutPutWindow("Connection Lost  ");
			WindowsUtil::displayToOutPutWindow(mPacket->systemAddress.ToString(true));
			std::cout << "Connection Lost  ";
			std::cout << mPacket->systemAddress.ToString(true);
			break;
		case ID_NO_FREE_INCOMING_CONNECTIONS:
			//When server is full
			WindowsUtil::displayToOutPutWindow("Connection is Full");
			std::cout << "Connection is full\n";
			break;
		case ID_INVALID_PASSWORD:
			//Incorrect password
			WindowsUtil::displayToOutPutWindow("Incorrect Password\n");
			std::cout << "Incorrect Password\n";
			break;
		case ID_CONNECTION_REQUEST_ACCEPTED:
			WindowsUtil::displayToOutPutWindow("Your connection is established\n");
			std::cout << "Your connection is established\n";
			break;
		case ID_SPAWN_PLAYER:
			break;
		default:
			//for sending chat messages
			break;
		}
	}
}


void Engine::Networking::Client::SetIP()
{
	serverIP = "127.0.0.1";
	clientPort = "60000";
}





 