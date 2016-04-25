#ifndef __CLIENT_H
#define __CLIENT_H
#include "../../../Externals/Raknet/src/RakPeerInterface.h"
#include "../../../Externals/Raknet/src/NetworkIDManager.h"
#include <string>

namespace Engine
{
	namespace Networking
	{
		class Client
		{
		public:
			Client(int);
			void CreateClientInterface();
			void SetIP();
			void ClientStartup();
			void ShutDownClient();
			void ReceivePackets();

			RakNet::RakPeerInterface * client;
			std::string serverPort;
			std::string clientPort;
			std::string serverIP;

		private:
			int mNumSockets;
			int mNumIPs;
			int mMaxPlayers;
			unsigned char mPacketIdentifier;

			RakNet::SocketDescriptor mSocketDescriptor;
			RakNet::NetworkIDManager mNetworkIDManager;
			RakNet::NetworkID playerNetworkID;
			RakNet::MessageID typeID;
			RakNet::Packet * mPacket;
		};
	}
}

#endif