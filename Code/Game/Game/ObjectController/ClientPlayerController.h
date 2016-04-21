#ifndef __CLIENT_PLAYER_CONTROLLER_H
#define __CLIENT_PLAYER_CONTROLLER_H

#include "../../../Engine/Core/Utilities/IObjectController.h"

namespace Game
{
	class ClientPlayerController :public Engine::IObjectController
	{
	public:
		void updateObject(Engine::Object &,
			Engine::typedefs::ActionWithKeyBound iAction) override;
	};
}

#endif

