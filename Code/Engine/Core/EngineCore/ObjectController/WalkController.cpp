#include "WalkController.h"
#include "../../Maths/cVector.h"
#include "../Objects/GameObject.h"
#include "../Objects/Scene.h"
#include "../../../Windows/WindowsFunctions.h"

void Engine::WalkController::updateGameObject(GameObject &i_gameObject, Engine::typedefs::Direction i_dir)
{
	Engine::Math::cVector tempOffset = i_gameObject.getOffsetPosition();
	std::stringstream errormessage;
		switch (i_dir)
		{
		case Engine::typedefs::NONE:
			break;
		case Engine::typedefs::UP:
			/*errormessage << Engine::Scene::getTimer()->getdeltaTime();
			WindowsUtil::Print(errormessage.str());*/
			tempOffset += Engine::Math::cVector(0.0f, 0.02f, 0.0f);// *Engine::Scene::getTimer()->getdeltaTime();
			break;
		case Engine::typedefs::DOWN:
			tempOffset += Engine::Math::cVector(0.0f, -0.02f, 0.0f);// *Engine::Scene::getTimer()->getdeltaTime();
			break;
		case Engine::typedefs::LEFT:
			tempOffset += Engine::Math::cVector(-0.02f, 0.0f, 0.0f);// *Engine::Scene::getTimer()->getdeltaTime();
			break;
		case Engine::typedefs::RIGHT:
			tempOffset += Engine::Math::cVector(0.02f, 0.0f, 0.0f);/** Engine::Scene::getTimer()->getdeltaTime();*/
			break;
		}
		i_gameObject.setPositionOffset(tempOffset);
}

//Engine::SharedPointer<Engine::IObjectController> Engine::WalkController::getObjectController()
//{
//	SharedPointer<IObjectController> temp(new WalkController());
//	return temp;
//}

