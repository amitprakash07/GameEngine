#ifndef __SERVER_PLAYER_CONTROLLER_H
#define __SERVER_PLAYER_CONTROLLER_H

#include "../../../Engine/Core/Utilities/IObjectController.h"

namespace Game
{
	class ServerPlayerController:public Engine::IObjectController
	{
	public:
		void updateObject(Engine::Object &,
			Engine::typedefs::ActionWithKeyBound iAction) override;
	};
}

#endif