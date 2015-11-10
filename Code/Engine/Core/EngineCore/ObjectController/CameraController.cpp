#include "../../Maths/cVector.h"
#include "../Objects/GameObject.h"
#include "../Objects/Scene.h"
#include "../../../Windows/WindowsFunctions.h"
#include "CameraController.h"


void Engine::CameraController::updateGameObject(Object &i_Object, Engine::typedefs::Direction i_dir)
{
	Transformation tempTransformation = i_Object.getTransformation();
	std::stringstream errormessage;
	switch (i_dir)
	{
	case Engine::typedefs::NONE:
		break;
	case Engine::typedefs::UP:
		/*errormessage << Engine::Scene::getTimer()->getdeltaTime();
		WindowsUtil::Print(errormessage.str());*/
		tempTransformation.mPositionOffset += Engine::Math::cVector(0.0f, 0.0f, -0.1f);// *Engine::Scene::getTimer()->getdeltaTime();
		break;
	case Engine::typedefs::DOWN:
		tempTransformation.mPositionOffset += Engine::Math::cVector(0.0f, 0.0f, 0.1f);// *Engine::Scene::getTimer()->getdeltaTime();
		break;
	case Engine::typedefs::LEFT:
		tempTransformation.mPositionOffset += Engine::Math::cVector(0.1f, 0.0f, 0.0f);// *Engine::Scene::getTimer()->getdeltaTime();
		break;
	case Engine::typedefs::RIGHT:
		tempTransformation.mPositionOffset += Engine::Math::cVector(-0.1f, 0.0f, 0.0f);/** Engine::Scene::getTimer()->getdeltaTime();*/
		break;
	}
	i_Object.setTransformation(tempTransformation.mPositionOffset);
}

