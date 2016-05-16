#ifndef __CLIENT_H
#define __CLIENT_H
#include "../../../Externals/Raknet/src/RakPeerInterface.h"
#include "../../../Externals/Raknet/src/NetworkIDManager.h"
#include <string>
#include "../EngineCore/Objects/MeshObject.h"
#include "NetworkPlayer.h"

namespace Engine
{
	namespace Networking
	{
		class Client
		{
		public:
			Client();
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

			void addToNetworkPlayerList(
				SharedPointer<MeshObject> IObject,
				bool i_isControlPlayer = true);

			SharedPointer<NetworkPlayer> InstantiateNetworkPlayer(
				RakNet::NetworkID iNetowrkID,
				std::string i_meshFileName,
				std::string i_materialName,
				Math::Transform clientPlayerTransform = Math::Transform(),
				Engine::Graphics::RGBAColor = { 1.0f,1.0f,1.0f,1.0f });

			std::vector<SharedPointer<NetworkPlayer>> GetControlPlayer();
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