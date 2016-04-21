#include "../../Engine/Core/EngineCore/Objects/Object.h"
#include "../../Engine/Core/Maths/Vector3.h"
#include "../../Engine/Core/Maths/Functions.h"
#include "../../Engine/Core/EngineCore/Objects/Scene.h"
#include "BumpToToon.h"


using namespace Engine::Math;
void Application::BumpToToon::updateObject(Engine::Object& iObject, Engine::typedefs::ActionWithKeyBound iAction)
{
	Engine::Math::Transform transform = iObject.getTransform();
	switch (iAction.keyVal)
	{
	case 0x54:
		iObject.setRenderable(!iObject.isRenderable());
		break;
	default:
		break;
	}


	

}



