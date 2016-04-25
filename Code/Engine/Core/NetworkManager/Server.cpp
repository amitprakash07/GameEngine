#include "Server.h"
#include "../../../Engine/Windows/WindowsFunctions.h"
#include "../../../Externals/Raknet/src/MessageIdentifiers.h"
#include "../../../Externals/Raknet/src/BitStream.h"
#include "NetworkDefs.h"
#include <iostream>

Engine::Networking::Server::Server(int iNumPlayers)
{
	mNumSockets = 1;
	mNumIPs = 1;
	mMaxPlayers = iNumPlayers;
	mServerPort = "60001";
}


void Engine::Networking::Server::CreateServerInterface()
{
	mServer = RakNet::RakPeerInterface::GetInstance();			
	WindowsUtil::Assert(mServer,"Unable to create the server interface");	
	mServer->SetIncomingPassword("admin",
		static_cast<int>(strlen("admin")));
	mServer->SetTimeoutTime(30000, RakNet::UNASSIGNED_SYSTEM_ADDRESS);	
}


void Engine::Networking::Server::ReceivePackets() //-- In game loop
{
	for (mPacket = mServer->Receive(); mPacket; mServer->DeallocatePacket(mPacket),
		mPacket = mServer->Receive())
	{
		mPacketIdentifier = GetPacketIdentifier(mPacket);
		RakNet::BitStream receiveBitStream(mPacket->data,
			mPacket->length, false);
		RakNet::BitStream sendBitStream;
		switch(mPacketIdentifier)
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
		case ID_SPAWN_PLAYER:
			break;
		default:
			break;
		}
	}
}

void Engine::Networking::Server::ServerStartUp()
{
	mSocketDescriptor.port = atoi(mServerPort.c_str()); //Set the port for the server
	mSocketDescriptor.socketFamily = AF_INET; //IPv4 Protocol
	bool serverStartUpStatus =
		mServer->Startup(mMaxPlayers, &mSocketDescriptor, 1)
		== RakNet::RAKNET_STARTED;
	WindowsUtil::Assert(serverStartUpStatus, 
		"Unable to start the server");
	mServer->SetMaximumIncomingConnections(mMaxPlayers);
	mServer->SetOccasionalPing(true);//Keep pinging still if nothing is send or receive
	mServer->SetUnreliableTimeout(1000);
	DebugServerInfo();
}

void Engine::Networking::Server::ShutDownServer()
{
	mServer->Shutdown(300);
	RakNet::RakPeerInterface::DestroyInstance(mServer);
}


void Engine::Networking::Server::DebugServerInfo()
{
	DataStructures::List<RakNet::RakNetSocket2*> sockets;
	mServer->GetSockets(sockets);
	WindowsUtil::displayToOutPutWindow("Server Started\n");

	for( unsigned int i=0; i< sockets.Size(); i++)
	{
		WindowsUtil::displayToOutPutWindow(sockets[i]->GetBoundAddress().ToString(true));
		mNumSockets++;
	}

	for(unsigned int i=0; i< mServer->GetNumberOfAddresses(); i++)
	{
		WindowsUtil::displayToOutPutWindow(mServer->GetLocalIP(i));
		mNumIPs++;
	}

	WindowsUtil::displayToOutPutWindow(mServer->GetGuidFromSystemAddress(
		RakNet::UNASSIGNED_SYSTEM_ADDRESS).ToString());
}




