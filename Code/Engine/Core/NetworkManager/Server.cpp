#include "Server.h"
#include "../../../Engine/Windows/WindowsFunctions.h"
#include "../../../Externals/Raknet/src/MessageIdentifiers.h"
#include "../../../Externals/Raknet/src/BitStream.h"
#include "NetworkDefs.h"
#include <iostream>
#include "../EngineCore/Objects/Scene.h"
#include "../EngineCore/EngineCore.h"
#include "../Utilities/StringUtil.h"

Engine::Networking::Server::Server(int iNumPlayers)
{
	mNumSockets = 1;
	mNumIPs = 1;
	mMaxPlayers = iNumPlayers;
	mServerPort = "60001";
	mServer = nullptr;
	mPacket = nullptr;
}

Engine::Networking::Server::Server()
{
	mNumSockets = 1;
	mNumIPs = 1;
	mMaxPlayers = 8;
	mServerPort = "60001";
	mServer = nullptr;
	mPacket = nullptr;
}


void Engine::Networking::Server::CreateServerInterface()
{
	mServer = RakNet::RakPeerInterface::GetInstance();			
	WindowsUtil::Assert(mServer!=nullptr,"Unable to create the server interface");	
	mServer->SetIncomingPassword("admin",
		static_cast<int>(strlen("admin")));
	mServer->SetTimeoutTime(30000, RakNet::UNASSIGNED_SYSTEM_ADDRESS);	
}


void Engine::Networking::Server::ReceivePackets() 
{
	for (mPacket = mServer->Receive(); mPacket; mServer->DeallocatePacket(mPacket),
		mPacket = mServer->Receive())
	{
		mPacketIdentifier = GetPacketIdentifier(mPacket);
		RakNet::BitStream receiveBitStream(mPacket->data,
			mPacket->length, false);		
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
		{
			WindowsUtil::displayToOutPutWindow("New Incoming Connection");
			std::cout << "New Incoming connection\n";
			RakNet::BitStream bsOut;
			bsOut.Write(static_cast<RakNet::MessageID>(ID_LOAD_CURRENT_PLAYERS));
			bsOut.Write(mPlayerLists.size());
			for (std::map<RakNet::NetworkID, SharedPointer<NetworkPlayer>>::iterator i = mPlayerLists.begin();
				i != mPlayerLists.end(); ++i)
			{
				SharedPointer<MeshObject> tempMeshObject = i->second->GetMeshObject();				
				
				std::string meshFileNameWithFullPath = tempMeshObject->getMesh()->getMeshFileName();
				std::string meshFileName =
					Utils::RemoveString(meshFileNameWithFullPath,
						EngineCore::getMeshFolderPath());

				std::string materialFileNameWithFullPath = tempMeshObject->getMaterial()->getMaterialName();
				std::string materialFileName =
					Utils::RemoveString(materialFileNameWithFullPath,
						EngineCore::getMaterialFolderPath());


				Math::Transform tempTransform = tempMeshObject->getTransform();
				Engine::Graphics::RGBAColor iColor = tempMeshObject->GetVertexColor();
				bool debugStatus = tempMeshObject->isDebugObject();
				Math::Vector3 objectScale = tempMeshObject->getScale();
				
				//Mesh File Name
				bsOut.Write(meshFileName.size());
				bsOut.Write(meshFileName.c_str(), meshFileName.size());

				//Material Name
				bsOut.Write(materialFileName.size());
				bsOut.Write(materialFileName.c_str(), materialFileName.size());

				//Poistion
				bsOut.Write(tempTransform.getPosition().x);
				bsOut.Write(tempTransform.getPosition().y);
				bsOut.Write(tempTransform.getPosition().z);

				//Orientation
				bsOut.Write(tempTransform.getOrientation().w());
				bsOut.Write(tempTransform.getOrientation().x());
				bsOut.Write(tempTransform.getOrientation().y());
				bsOut.Write(tempTransform.getOrientation().z());

				//Scale
				bsOut.Write(objectScale.x);
				bsOut.Write(objectScale.y);
				bsOut.Write(objectScale.z);

				//Vertex Color
				bsOut.Write(iColor.r);
				bsOut.Write(iColor.g);
				bsOut.Write(iColor.b);
				bsOut.Write(iColor.a);

				//WireFrame Info
				bsOut.Write(debugStatus);

				//NetworkID
				bsOut.Write(i->second->GetNetworkID());
			}
			mServer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0,
				mPacket->systemAddress, false);
		}
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
		{
			receiveBitStream.IgnoreBytes(sizeof(RakNet::MessageID));			
			Math::Transform tempTransform;
			Engine::Graphics::RGBAColor tempColor;
			size_t materialNameSize;
			size_t meshNameSize;

			//Mesh File Name
			char * meshName;
			receiveBitStream.Read(meshNameSize);
			meshName = new char[meshNameSize + 1];
			receiveBitStream.Read(meshName, meshNameSize);
			meshName[meshNameSize] = '\0';

			//material File 
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

			//VertexColor
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
			Scene::getRenderableScene()->addObjectToScene(tempMeshObject);
			tempMeshObject->setScale(xScale, yScale, zScale);
			tempMeshObject->EnableDebugging(wireFrameStatus);
			tempNetworkPlayer->SetNetworkIDManager(&mNetworkIDManager);
			tempNetworkPlayer->SetNetworkID(networkID);
			tempNetworkPlayer->SetControlPlayer(false);
			mPlayerLists[networkID] = tempNetworkPlayer;

			//Sending to other clients on the network
			RakNet::BitStream bsOut;
			bsOut.Write(static_cast<RakNet::MessageID>(ID_SPAWN_PLAYER));

			//Mesh Name
			bsOut.Write(tempMeshName.size());
			bsOut.Write(tempMeshName.c_str(), tempMeshName.size());

			//Material Name
			bsOut.Write(tempMaterialName.size());
			bsOut.Write(tempMaterialName.c_str(), tempMaterialName.size());

			//Position
			bsOut.Write(tempTransform.getPosition().x);
			bsOut.Write(tempTransform.getPosition().y);
			bsOut.Write(tempTransform.getPosition().z);

			//orientation
			bsOut.Write(tempTransform.getOrientation().w());
			bsOut.Write(tempTransform.getOrientation().x());
			bsOut.Write(tempTransform.getOrientation().y());
			bsOut.Write(tempTransform.getOrientation().z());

			//Scale
			bsOut.Write(xScale);
			bsOut.Write(yScale);
			bsOut.Write(zScale);

			//Vertex Color
			bsOut.Write(tempColor.r);
			bsOut.Write(tempColor.g);
			bsOut.Write(tempColor.b);
			bsOut.Write(tempColor.a);

			//WireFrameInfo
			bsOut.Write(wireFrameStatus);

			//NetworkID
			bsOut.Write(networkID);
			
			mServer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, mPacket->systemAddress, true);
		}		
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


Engine::SharedPointer<Engine::Networking::NetworkPlayer> 
	Engine::Networking::Server::InstantiateNetworkPlayer(
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


void Engine::Networking::Server::addToNetworkPlayerList(
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
Engine::Networking::Server::GetControlPlayer()
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
Engine::Networking::Server::GetNetworkPlayer(
	RakNet::NetworkID i_networkID)
{
	for (std::map<RakNet::NetworkID, SharedPointer<Networking::NetworkPlayer>>::iterator i = mPlayerLists.begin();
		i != mPlayerLists.end(); ++i)
	{
		if (i->first == i_networkID)
			return i->second;
	}
	return SharedPointer<Networking::NetworkPlayer>();
}






