#include "ServerPlayerController.h"
#include "../../../Engine/Core/NetworkManager/NetworkManager.h"
#include "../../../Engine/Core/EngineCore/Objects/Scene.h"
#include "../../../Engine/Windows/WindowsFunctions.h"

void Game::ServerPlayerController::updateObject(Engine::Object& iObject, 
	Engine::typedefs::ActionWithKeyBound iAction)
{
	iObject.setRenderable(!iObject.isRenderable());	
}
