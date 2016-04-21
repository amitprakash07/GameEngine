#ifndef __NETWORK_MANAGER_H
#define __NETWORK_MANAGER_H

#include "../../../Externals/Raknet/src/RakPeerInterface.h"
#include "../../Core/Utilities/SharedPointer.h"
#include "NetworkDefs.h"

namespace Engine
{
	
	namespace Networking
	{
		class NetworkManager
		{
		public:
			static void CreateNetworkManager(bool i_isServer, 
				std::string iServerAddress = "127.0.0.1");
			static void updateNetwork();
			static void ShutDownNetwork();	
			static bool isServerInstance();
			static NetworkPacket getReceivedNetworkPacket();
			static void setSendingNetworkPacket(NetworkPacket iSendingNetworkPacket);	
			static GameMessages getCurrentMessage();
		private:
			static SharedPointer<NetworkManager> mNetworkManager;
			NetworkManager();
			SharedPointer<RakNet::RakPeerInterface> mPeerInterface;
			bool mIsServer;
			ServerPort_Or_MAxClent mNetworkDetail;
			RakNet::SocketDescriptor mSocketDetail;
			NetworkPacket receivingNetworkPacket;
			NetworkPacket sendingNetworkPacket;
			GameMessages currentGameMessage;
		};
	}
}


#endif