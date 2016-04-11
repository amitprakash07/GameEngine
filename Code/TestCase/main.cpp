//#include <iostream>
//#include "../Engine/Windows/WindowsFunctions.h"
//#include "../Engine/Core/Maths/Transform.h"
//#include "../Engine/Core/Maths/Functions.h"
//#include "../Engine/Core/EngineCore/EngineCore.h"
//
//#include "../Externals/OpenGLExtensions/OpenGlExtensions.h"
//using namespace Engine::Math;
//
//int WINAPI WinMain(HINSTANCE i_thisInstanceOfTheProgram, HINSTANCE, char* i_commandLineArguments, int i_initialWindowDisplayState)
//{
//	/*Vector3 a = Vector3(-1.0f, -1.0f, 1.0f);
//	Vector3 b = Vector3(1.0f, -1.0f, 1.0f);
//	Vector3 c = Vector3(1.0f, 1.0f, 1.0f);
//	Vector3 d = Vector3(-1.0f, 1.0f, 1.0f);
//
//	Vector3 e = Vector3(-1.0f, -1.0f, -1.0f);
//	Vector3 f = Vector3(1.0f, -1.0f, -1.0f);
//	Vector3 g = Vector3(1.0f, 1.0f, -1.0f);
//	Vector3 h = Vector3(-1.0f, 1.0f, -1.0f);
//
//	Matrix4x4 changeMatrix = Matrix4x4(Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(45.0f),
//		Engine::Math::Vector3(0.0f, 1.0f, 0.0f)));
//
//	changeMatrix.mul(a).printVector();
//	changeMatrix.mul(b).printVector();
//	changeMatrix.mul(c).printVector();
//	changeMatrix.mul(d).printVector();
//
//	changeMatrix.mul(e).printVector();
//	changeMatrix.mul(f).printVector();
//	changeMatrix.mul(g).printVector();
//	changeMatrix.mul(h).printVector();*/
//
//	Engine::EngineCore::Initialize(i_thisInstanceOfTheProgram, i_initialWindowDisplayState);
//	glEnable(GL_STENCIL_TEST);
//	glStencilMask(0xFF);
//	while(1)
//	{		
//
//	}
//}

#include <stdio.h>
#include <string.h>
#include "../Externals/Raknet/src/MessageIdentifiers.h"
#include "../Externals/Raknet/src/RakNetSocket2.h"
#include "../Externals/Raknet/src/RakPeerInterface.h"

#define MAX_CLIENTS 10
#define SERVER_PORT 60000

int main(void)
{
	char str[512];

	RakNet::RakPeerInterface *peer = RakNet::RakPeerInterface::GetInstance();
	bool isServer;
	RakNet::Packet *packet;

	printf("(C) or (S)erver?\n");
	gets_s(str);

	if ((str[0] == 'c') || (str[0] == 'C'))
	{
		RakNet::SocketDescriptor sd;
		peer->Startup(1, &sd, 1);
		isServer = false;
	}
	else {
		RakNet::SocketDescriptor sd(SERVER_PORT, 0);
		peer->Startup(MAX_CLIENTS, &sd, 1);
		isServer = true;
	}


	if (isServer)
	{
		printf("Starting the server.\n");
		// We need to let the server accept incoming connections from the clients
		peer->SetMaximumIncomingConnections(MAX_CLIENTS);
	}
	else {
		printf("Enter server IP or hit enter for 127.0.0.1\n");
		gets_s(str);
		if (str[0] == 0) {
			strcpy(str, "127.0.0.1");
		}
		printf("Starting the client.\n");
		peer->Connect(str, SERVER_PORT, 0, 0);

	}

	while (1)
	{
		for (packet = peer->Receive(); packet; peer->DeallocatePacket(packet), packet = peer->Receive())
		{
			switch (packet->data[0])
			{
			case ID_REMOTE_DISCONNECTION_NOTIFICATION:
				printf("Another client has disconnected.\n");
				break;
			case ID_REMOTE_CONNECTION_LOST:
				printf("Another client has lost the connection.\n");
				break;
			case ID_REMOTE_NEW_INCOMING_CONNECTION:
				printf("Another client has connected.\n");
				break;
			case ID_CONNECTION_REQUEST_ACCEPTED:
				printf("Our connection request has been accepted.\n");
				break;
			case ID_NEW_INCOMING_CONNECTION:
				printf("A connection is incoming.\n");
				break;
			case ID_NO_FREE_INCOMING_CONNECTIONS:
				printf("The server is full.\n");
				break;
			case ID_DISCONNECTION_NOTIFICATION:
				if (isServer) {
					printf("A client has disconnected.\n");
				}
				else {
					printf("We have been disconnected.\n");
				}
				break;
			case ID_CONNECTION_LOST:
				if (isServer) {
					printf("A client lost the connection.\n");
				}
				else {
					printf("Connection lost.\n");
				}
				break;
			default:
				printf("Message with identifier %i has arrived.\n", packet->data[0]);
				break;
			}
		}
	}


	RakNet::RakPeerInterface::DestroyInstance(peer);
	
	return 0;
}


