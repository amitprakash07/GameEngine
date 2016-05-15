#include "../../../Engine/Core/Utilities/IObjectController.h"
#include "../../../Engine/Core/Maths/Vector3.h"


namespace Game
{
	class CameraController : public Engine::IObjectController
	{
	public:
		static bool flyCam;
		static bool thirdPerson;
		static Engine::Math::Vector3 mForwardVector;
		void updateObject(Engine::Object &, 
			Engine::typedefs::ActionWithKeyBound iAction) override;
	};
}
