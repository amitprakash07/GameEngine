#include "../../../Engine/Core/Utilities/IObjectController.h"

namespace Game
{
	class WalkController : public Engine::IObjectController
	{
		void updateObject(Engine::Object &, Engine::typedefs::ActionWithKeyBound iAction) override;
	};
}
