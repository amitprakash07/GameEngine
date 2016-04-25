#ifndef __NETWORK_DEFS_H
#define __NETWORK_DEFS_H
#include "../../../Externals/Raknet/src/MessageIdentifiers.h"
#include "../Maths/Transform.h"
#include "Client.h"
#include "Server.h"
#include "../Utilities/SharedPointer.h"

#define MAX_CLIENTS 10
#define SERVER_PORT 60000

namespace Engine
{
	namespace Networking
	{
		enum GameMessages
		{
			UNKNOWN,
			ID_SPAWN_PLAYER = ID_USER_PACKET_ENUM +1,
			ID_LOAD_CURRENT_PLAYERS = ID_USER_PACKET_ENUM +2,
			ID_RE_SYNC_PLAYERS = ID_USER_PACKET_ENUM + 3,
			ID_SYNC_KEY_PRESS = ID_USER_PACKET_ENUM + 4		
		};

		union ServerPort_Or_MAxClent
		{
			unsigned int serverPort;
			unsigned int maxClient;
		};

		union System
		{
			Client* mClient;
			Server* mServer;		

			System()
			{
				mClient = new Client(8);
				mServer = new Server(8);
			}
			~System()
			{
				delete mClient;
				delete mServer;
			}
		};

		struct NetworkPacket
		{
			Engine::Math::Transform mTransformData;		

			NetworkPacket()
			{
				mTransformData = Math::Transform();
			}

			NetworkPacket(Math::Transform iTransform)
			{
				mTransformData = iTransform;
			}

			NetworkPacket(Math::Vector3 iPosition,
				Math::Quaternion iOrientation)
			{
				mTransformData = Math::Transform();
				mTransformData.setPosition(iPosition);
				mTransformData.setOrientation(iOrientation);
			}

			std::string toString()
			{
				
			}			
		};

		inline unsigned char GetPacketIdentifier(RakNet::Packet* iPacket)
		{
			if (iPacket == 0)
				return 255;

			if (static_cast<unsigned char>(iPacket->data[0]) == ID_TIMESTAMP)
			{
				RakAssert(iPacket->length >
					sizeof(RakNet::MessageID) + sizeof(RakNet::Time));
				return static_cast<unsigned char>(
					iPacket->data[sizeof(RakNet::MessageID) + sizeof(RakNet::Time)]);
			}
			else
				return static_cast<unsigned char>(iPacket->data[0]);
		}
		

	}
}


#endif
