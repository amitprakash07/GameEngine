#include "Client.h"
#include "../../../Engine/Windows/WindowsFunctions.h"
#include "../../../Externals/Raknet/src/MessageIdentifiers.h"
#include "../../../Externals/Raknet/src/BitStream.h"
#include "NetworkDefs.h"
#include <iostream>
#include "../EngineCore/Objects/Scene.h"

Engine::Networking::Client::Client(int iMaxPlayer)
{
	mNumSockets = 1;
	mNumIPs = 1;
	mMaxPlayers = iMaxPlayer;
	serverPort = "6001";
	mPacket = nullptr;
	client = nullptr;
}


Engine::Networking::Client::Client()
{
	mNumSockets = 1;
	mNumIPs = 1;
	mMaxPlayers = 8;
	serverPort = "6001";
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
	if (!client)
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


void Engine::Networking::Client::ReceivePackets() 
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
		{
			WindowsUtil::displayToOutPutWindow("Your connection is established\n");			
		}
		break;
		case ID_SPAWN_PLAYER:
		{
			receiveBitStream.IgnoreBytes(sizeof(RakNet::MessageID));
			Math::Transform tempTransform;
			Engine::Graphics::RGBAColor tempColor;
			size_t materialNameSize;
			size_t meshNameSize;

			//Mesh Name
			char * meshName;
			receiveBitStream.Read(meshNameSize);
			meshName = new char[meshNameSize + 1];
			receiveBitStream.Read(meshName, meshNameSize);
			meshName[meshNameSize] = '\0';

			//material Name
			char *materialName;
			receiveBitStream.Read(materialNameSize);
			materialName = new char[materialNameSize + 1];
			receiveBitStream.Read(materialName, materialNameSize);
			materialName[materialNameSize] = '\0';

			//Position
			float posX, posY, posZ;
			receiveBitStream.Read(posX);
			receiveBitStream.Read(posY);
			receiveBitStream.Read(posZ);

			//Orientation
			float rotW, rotX, rotY, rotZ;
			receiveBitStream.Read(rotW);
			receiveBitStream.Read(rotX);
			receiveBitStream.Read(rotY);
			receiveBitStream.Read(rotZ);			

			//Scale
			float xScale, yScale, zScale;
			receiveBitStream.Read(xScale);
			receiveBitStream.Read(yScale);
			receiveBitStream.Read(zScale);

			//Vertex Color
			receiveBitStream.Read(tempColor.r);
			receiveBitStream.Read(tempColor.g);
			receiveBitStream.Read(tempColor.b);
			receiveBitStream.Read(tempColor.a);

			//WireFrame Info
			bool wireFrameStatus;
			receiveBitStream.Read(wireFrameStatus);

			//Network ID
			RakNet::NetworkID networkID;
			receiveBitStream.Read(networkID);


			std::string tempMeshName = meshName;
			std::string tempMaterialName = materialName;
			delete[]meshName;
			delete[]materialName;

			tempTransform.setPosition(Math::Vector3(posX, posY, posZ));
			Math::Quaternion tempQuaternion;
			tempQuaternion.w(rotW);
			tempQuaternion.x(rotX);
			tempQuaternion.y(rotY);
			tempQuaternion.z(rotZ);
			tempTransform.setOrientation(tempQuaternion);

			SharedPointer<NetworkPlayer> tempNetworkPlayer =
				NetworkPlayer::CreateNetworkPlayer(
					tempMeshName,
					tempMaterialName,
					tempTransform,
					tempColor);

			SharedPointer<MeshObject> tempMeshObject =
				tempNetworkPlayer->GetMeshObject();
			tempMeshObject->setScale(xScale, yScale, zScale);
			tempMeshObject->EnableDebugging(wireFrameStatus);
			Scene::getRenderableScene()->addObjectToScene(tempMeshObject);
			tempNetworkPlayer->SetNetworkIDManager(&mNetworkIDManager);
			tempNetworkPlayer->SetNetworkID(networkID);
			tempNetworkPlayer->SetControlPlayer(false);
			mPlayerLists[networkID] = tempNetworkPlayer;
		}
			break;
		case ID_LOAD_CURRENT_PLAYERS:
		{
			WindowsUtil::displayToOutPutWindow("Loading Players\n");
			receiveBitStream.IgnoreBytes(sizeof(RakNet::MessageID));
			Math::Transform tempTransform;
			Engine::Graphics::RGBAColor tempColor;
			size_t materialNameSize;
			size_t meshNameSize;
			size_t playerCount;
			receiveBitStream.Read(playerCount);
			for (uint8_t i = 0; i<playerCount; i++)
			{
				//Mesh File Name
				char * meshName;
				receiveBitStream.Read(meshNameSize);
				meshName = new char[meshNameSize + 1];
				receiveBitStream.Read(meshName, meshNameSize);
				meshName[meshNameSize] = '\0';

				//Material File Name
				char *materialName;
				receiveBitStream.Read(materialNameSize);
				materialName = new char[materialNameSize + 1];
				receiveBitStream.Read(materialName, materialNameSize);
				materialName[materialNameSize] = '\0';

				//Position
				float posX, posY, posZ;
				receiveBitStream.Read(posX);
				receiveBitStream.Read(posY);
				receiveBitStream.Read(posZ);

				//Orientation
				float rotW, rotX, rotY, rotZ;
				receiveBitStream.Read(rotW);
				receiveBitStream.Read(rotX);
				receiveBitStream.Read(rotY);
				receiveBitStream.Read(rotZ);			
				
				//Scale
				float xScale, yScale, zScale;
				receiveBitStream.Read(xScale);
				receiveBitStream.Read(yScale);
				receiveBitStream.Read(zScale);

				//Vertex Color
				receiveBitStream.Read(tempColor.r);
				receiveBitStream.Read(tempColor.g);
				receiveBitStream.Read(tempColor.b);
				receiveBitStream.Read(tempColor.a);

				//WireFrameInfo
				bool wireFramStatus;
				receiveBitStream.Read(wireFramStatus);

				//Network ID
				RakNet::NetworkID networkID;
				receiveBitStream.Read(networkID);

				std::string tempMeshName = meshName;
				std::string tempMaterialName = materialName;
				delete[]meshName;
				delete[]materialName;

				tempTransform.setPosition(Math::Vector3(posX, posY, posZ));
				Math::Quaternion tempQuaternion;
				tempQuaternion.w(rotW);
				tempQuaternion.x(rotX);
				tempQuaternion.y(rotY);
				tempQuaternion.z(rotZ);
				tempTransform.setOrientation(tempQuaternion);

				SharedPointer<NetworkPlayer> tempNetworkPlayer =
					NetworkPlayer::CreateNetworkPlayer(
						tempMeshName,
						tempMaterialName,
						tempTransform,
						tempColor);
				
				mPlayerLists[networkID] = tempNetworkPlayer;
				SharedPointer<MeshObject> tempMeshObject = 
					tempNetworkPlayer->GetMeshObject();
				tempMeshObject->setScale(xScale, yScale, zScale);
				tempMeshObject->EnableDebugging(wireFramStatus);
				Scene::getRenderableScene()->addObjectToScene(tempMeshObject);

				tempNetworkPlayer->SetNetworkIDManager(&mNetworkIDManager);
				tempNetworkPlayer->SetNetworkID(networkID);
				tempNetworkPlayer->SetControlPlayer(false);
			}

			GetControlPlayer()->SendNewNetworkPlayer(client);
		}
		break;
		case ID_SYNC_KEY_PRESS:
		{
			receiveBitStream.IgnoreBytes(sizeof(RakNet::MessageID));
			RakNet::NetworkID incomingNetworkID;
			receiveBitStream.Read(incomingNetworkID);
			SharedPointer<NetworkPlayer> incomingNetworkPlayer
				= mPlayerLists[incomingNetworkID];

			//Position
			float posX, posY, posZ;
			receiveBitStream.Read(posX);
			receiveBitStream.Read(posY);
			receiveBitStream.Read(posZ);

			//Orientation
			float rotW, rotX, rotY, rotZ;
			receiveBitStream.Read(rotW);
			receiveBitStream.Read(rotX);
			receiveBitStream.Read(rotY);
			receiveBitStream.Read(rotZ);

			//Update position and orientation
			Math::Quaternion tempQuaternion;
			tempQuaternion.w(rotW);
			tempQuaternion.x(rotX);
			tempQuaternion.y(rotY);
			tempQuaternion.z(rotZ);			
			incomingNetworkPlayer->GetMeshObject()->setTransform(
				Math::Vector3(posX, posY, posZ), tempQuaternion);
		}
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
	clientPort = "6000";
}


Engine::SharedPointer<Engine::Networking::NetworkPlayer>
Engine::Networking::Client::InstantiateNetworkPlayer(
	RakNet::NetworkID iNetworkID,
	std::string i_meshFileName,
	std::string i_materialName,
	Math::Transform clientPlayerTransform,
	Engine::Graphics::RGBAColor iColor)
{
	SharedPointer<NetworkPlayer> newPlayer =
		NetworkPlayer::CreateNetworkPlayer(i_meshFileName,
			i_materialName, clientPlayerTransform, iColor);
	newPlayer->SetNetworkIDManager(&mNetworkIDManager);
	newPlayer->SetNetworkID(iNetworkID);
	mPlayerLists[newPlayer->GetNetworkID()] = newPlayer;
	SharedPointer<MeshObject> tempMeshObject = newPlayer->GetMeshObject();
	Scene::getRenderableScene()->addObjectToScene(tempMeshObject);
	return newPlayer;
}


void Engine::Networking::Client::addToNetworkPlayerList(
	SharedPointer<MeshObject> IObject, 
	bool i_isControlPlayer)
{
	SharedPointer<NetworkPlayer> tempNetworkPlayer =
		NetworkPlayer::CreateNetworkPlayer(IObject);
	tempNetworkPlayer->SetNetworkIDManager(&mNetworkIDManager);
	mPlayerLists[tempNetworkPlayer->GetNetworkID()] =
		tempNetworkPlayer;
	tempNetworkPlayer->SetControlPlayer(i_isControlPlayer);
}


Engine::SharedPointer<Engine::Networking::NetworkPlayer> 
Engine::Networking::Client::GetControlPlayer()
{
	for (std::map<RakNet::NetworkID, SharedPointer<Networking::NetworkPlayer>>::iterator i = mPlayerLists.begin();
		i != mPlayerLists.end(); ++i)
	{
		if (i->second->GetControlPlayerStatus())
			return i->second;
	}
	return SharedPointer<Networking::NetworkPlayer>();
}


Engine::SharedPointer<Engine::Networking::NetworkPlayer> 
Engine::Networking::Client::GetNetworkPlayer(
	RakNet::NetworkID i_networkID)
{
	for(std::map<RakNet::NetworkID, SharedPointer<Networking::NetworkPlayer>>::iterator i = mPlayerLists.begin();
		i!=mPlayerLists.end(); ++i)
	{
		if (i->first == i_networkID)
			return i->second;
	}
	return SharedPointer<Networking::NetworkPlayer>();
}










