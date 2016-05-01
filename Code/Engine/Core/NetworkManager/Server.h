#ifndef __SERVER_H
#define __SERVER_H

#include "NetworkPlayer.h"
#include "../../../Externals/Raknet/src/NetworkIDManager.h"

namespace Engine
{
	namespace Networking
	{
		class Server
		{
		public:
			Server();
			Server(int iNumPlayers);
			void CreateServerInterface();
			void ServerStartUp();
			void ShutDownServer();
			void ReceivePackets();
			void DebugServerInfo();

			void addToNetworkPlayerList(
				SharedPointer<MeshObject> IObject,
				bool i_isControlPlayer = true);

			RakNet::RakPeerInterface* mServer;
			std::string mServerPort;			
			std::string serverIP;
			std::string mRelayString;

			SharedPointer<NetworkPlayer> InstantiateNetworkPlayer(
				RakNet::NetworkID iNetowrkID,
				std::string i_meshFileName,
				std::string i_materialName,
				Math::Transform clientPlayerTransform = Math::Transform(),
				Engine::Graphics::RGBAColor = { 1.0f,1.0f,1.0f,1.0f });

			SharedPointer<NetworkPlayer> GetControlPlayer();
			SharedPointer<NetworkPlayer> GetNetworkPlayer(
				RakNet::NetworkID i_networkID);

		private:			
			int mNumSockets;
			int mNumIPs;
			int mMaxPlayers;
			unsigned char mPacketIdentifier;
			std::map<RakNet::NetworkID, SharedPointer<NetworkPlayer>> mPlayerLists;
			RakNet::SocketDescriptor mSocketDescriptor;
			RakNet::NetworkIDManager mNetworkIDManager;
			RakNet::NetworkID playerNetworkID;
			RakNet::MessageID typeID;
			RakNet::Packet * mPacket;			
		};		
	}
}


#endif