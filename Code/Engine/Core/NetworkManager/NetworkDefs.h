#ifndef __NETWORK_DEFS_H
#define __NETWORK_DEFS_H
#include "../../../Externals/Raknet/src/MessageIdentifiers.h"
#include "../Maths/Transform.h"

#define MAX_CLIENTS 10
#define SERVER_PORT 60000

namespace Engine
{
	namespace Networking
	{
		enum GameMessages
		{
			UNKNOWN,
			CLIENT_REQUEST_ACCEPTED = ID_CONNECTION_REQUEST_ACCEPTED,
			RECEIVE_TRANSFORM = ID_USER_PACKET_ENUM + 1
		};

		union ServerPort_Or_MAxClent
		{
			unsigned int serverPort;
			unsigned int maxClient;
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
		};

	}
}


#endif
