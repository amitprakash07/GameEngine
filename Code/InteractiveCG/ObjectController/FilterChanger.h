#include "../../Engine/Core/Utilities/IObjectController.h"


namespace Application
{
	class TextureFilterChanger : public Engine::IObjectController
	{
		void updateObject(Engine::Object &, Engine::typedefs::ActionWithKeyBound iAction) override;
	};
}