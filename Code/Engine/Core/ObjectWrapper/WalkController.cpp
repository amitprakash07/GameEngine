#include "WalkController.h"
#include "../Maths/cVector.h"
#include "GameObject.h"

void Engine::WalkController::updateGameObject(Engine::SharedPointer<GameObject>& i_gameObject, Engine::typedefs::Direction i_dir)
{
	Engine::Math::cVector tempOffset = i_gameObject->getOffsetPosition();
		switch (i_dir)
		{
		case Engine::typedefs::UP:
			tempOffset += Engine::Math::cVector(0.0f, 1.0f, 0.0f);
			break;
		case Engine::typedefs::DOWN:
			tempOffset += Engine::Math::cVector(0.0f, -1.0f, 0.0f);
			break;
		case Engine::typedefs::LEFT:
			tempOffset += Engine::Math::cVector(-1.0f, 0.0f, 0.0f);
			break;
		case Engine::typedefs::RIGHT:
			tempOffset += Engine::Math::cVector(1.0f, 0.0f, 0.0f);
			break;
		}
		i_gameObject->setOffset(tempOffset);
}
