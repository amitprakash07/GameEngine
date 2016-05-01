#include "NetworkPlayer.h"
#include "../../../Externals/Raknet/src/PacketPriority.h"
#include "NetworkDefs.h"
#include "../../../Externals/Raknet/src/BitStream.h"
#include "../Utilities/StringUtil.h"
#include "../EngineCore/EngineCore.h"


Engine::SharedPointer<Engine::Networking::NetworkPlayer>
Engine::Networking::NetworkPlayer::CreateNetworkPlayer(
	std::string i_meshFileName,
	std::string i_materialName,
	Math::Transform clientPlayerTransform,
	Engine::Graphics::RGBAColor iColor)
{
	SharedPointer<NetworkPlayer> tempNetworkPlayer =
		SharedPointer<NetworkPlayer>(new NetworkPlayer(i_meshFileName,
			i_materialName,
			clientPlayerTransform,
			iColor), "NetworkPlayer");
	return tempNetworkPlayer;
}


Engine::SharedPointer<Engine::Networking::NetworkPlayer>
Engine::Networking::NetworkPlayer::CreateNetworkPlayer(
	SharedPointer<MeshObject> iMeshObject)
{
	SharedPointer<NetworkPlayer> tempPLayer =
		SharedPointer<NetworkPlayer>(new NetworkPlayer(iMeshObject), "NetworkPlayer");
	return tempPLayer;
}



Engine::SharedPointer<Engine::MeshObject>
Engine::Networking::NetworkPlayer::GetMeshObject() const
{
	return mMeshObject;
}


Engine::Networking::NetworkPlayer::NetworkPlayer(
	std::string i_meshFileName,
	std::string i_materialName,
	Math::Transform clientPlayerTransform,
	Engine::Graphics::RGBAColor iColor)
{
	SharedPointer<MeshObject> tempClientPlayer = MeshObject::CreateMeshObject(
		i_meshFileName, i_materialName, iColor);
	tempClientPlayer->setTransform(clientPlayerTransform.getPosition(),
		clientPlayerTransform.getOrientation());
	mMeshObject = tempClientPlayer;
}


Engine::Networking::NetworkPlayer::NetworkPlayer(
	SharedPointer<MeshObject> iMeshObject)
{
	mMeshObject = iMeshObject;
}


void Engine::Networking::NetworkPlayer::SendNewNetworkPlayer(
	RakNet::RakPeerInterface* iServer)
{
	std::string meshFileNameWithFullPath = mMeshObject->getMesh()->getMeshFileName();	
	std::string meshFileName = 
		Utils::RemoveString(meshFileNameWithFullPath, 
			EngineCore::getMeshFolderPath());

	std::string materialFileNameWithFullPath = mMeshObject->getMaterialName();
	std::string materialFileName = 
		Utils::RemoveString(materialFileNameWithFullPath,
			EngineCore::getMaterialFolderPath());

	Math::Transform networkPlayerTransform = mMeshObject->getTransform();

	Graphics::RGBAColor color = mMeshObject->GetVertexColor();

	RakNet::BitStream bsOut;
	bsOut.Write(static_cast<RakNet::MessageID>(ID_SPAWN_PLAYER));
	bsOut.Write(meshFileName.size());
	bsOut.Write(meshFileName);
	bsOut.Write(materialFileName.size());
	bsOut.Write(materialFileName);
	bsOut.Write(networkPlayerTransform.getPosition().x);
	bsOut.Write(networkPlayerTransform.getPosition().y);
	bsOut.Write(networkPlayerTransform.getPosition().z);
	bsOut.Write(networkPlayerTransform.getOrientation().w());
	bsOut.Write(networkPlayerTransform.getOrientation().x());
	bsOut.Write(networkPlayerTransform.getOrientation().y());
	bsOut.Write(networkPlayerTransform.getOrientation().z());
	bsOut.Write(color.r);
	bsOut.Write(color.g);
	bsOut.Write(color.b);
	bsOut.Write(color.a);
	bsOut.Write(GetNetworkID());
	iServer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0,
		RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}


void Engine::Networking::NetworkPlayer::SetControlPlayer(bool i_isControlPlayer)
{
	isControlPlayer = i_isControlPlayer;
}


bool Engine::Networking::NetworkPlayer::GetControlPlayerStatus() const
{
	return isControlPlayer;
}
