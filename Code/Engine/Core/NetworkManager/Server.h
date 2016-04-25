#ifndef __SERVER_H
#define __SERVER_H
#include <string>
#include "../../../Externals/Raknet/src/RakPeerInterface.h"
#include "../../../Externals/Raknet/src/NetworkIDManager.h"




namespace Engine
{
	namespace Networking
	{
		class Server
		{
		public:
			Server(int iNumPlayers);
			void CreateServerInterface();
			void ServerStartUp();
			void ShutDownServer();
			void ReceivePackets();
			void DebugServerInfo();
			
			
			RakNet::RakPeerInterface* mServer;
			std::string mServerPort;
			std::string mClientPort;
			std::string serverIP;
			std::string mRelayString;

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