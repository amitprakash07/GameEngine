#include "Camera.h"
#include "../../../Core/Utilities/HashedString.h"
#include "../../../Core/EngineCore/EngineCore.h"
#include "../../Maths/Functions.h"


Engine::SharedPointer<Engine::Camera> Engine::Camera::CreateCamera(std::string i_name, 
	Math::cVector i_position, 
	Math::cQuaternion i_orientation, 
	float i_fieldofView,
	float i_aspectRatio)
{
	SharedPointer<Engine::Camera> tempCamera(new Engine::Camera(i_name, i_position, i_orientation, i_fieldofView, i_aspectRatio), "Engine::Camera");
	Engine::utils::StringHash temp(Engine::EngineCore::getStringPool()->findString("MoveCamera"));
	Engine::EngineCore::getMessagingSystem()->addMessageHandler(temp, reinterpret_cast<IMessageHandler*>(tempCamera.getRawPointer()), Engine::typedefs::HIGH);
	return tempCamera;
}


Engine::Camera::Camera()
{
	mObjectController = nullptr;
	mCameraName = "";
	mTransformation.mOrientation = Engine::Math::cQuaternion();
	mTransformation.mPositionOffset = Engine::Math::cVector();
	fieldOfView = 0.0f;
	aspectRatio = 0.0f;
	active = false;
}


Engine::Camera::Camera(std::string i_name, Math::cVector i_position, 
	Math::cQuaternion i_orientation,
	float i_fieldOfView,
	float i_aspectRatio)
{
	mObjectController = nullptr;
	mTransformation = Transformation();
	mCameraName = i_name;
	mTransformation.mOrientation = i_orientation;
	mTransformation.mPositionOffset = i_position;
	fieldOfView = Engine::Math::ConvertDegreesToRadians(i_fieldOfView);
	aspectRatio = i_aspectRatio;
	active = false;
}

void Engine::Camera::setFieldOfView(float i_fieldOfView)
{
	fieldOfView = Engine::Math::ConvertDegreesToRadians(i_fieldOfView);
}

float Engine::Camera::getFieldOfView()
{
	return fieldOfView;
}


void Engine::Camera::setAspectRatio(float i_aspectRatio)
{
	aspectRatio = i_aspectRatio;
}


float Engine::Camera::getAspectRatio()
{
	return aspectRatio;
}


void Engine::Camera::activateCamera(bool i_activate)
{
	active = i_activate;
}

bool Engine::Camera::isActive()
{
	return active;
}


Engine::Transformation Engine::Camera::getTransformation()
{
	return mTransformation;
}

void Engine::Camera::setTransformation(Engine::Math::cVector i_positionOffset, Engine::Math::cQuaternion i_orientation)
{
	mTransformation.mOrientation = i_orientation;
	mTransformation.mPositionOffset = i_positionOffset;
}


void Engine::Camera::setCameraController(IObjectController* i_objectController)
{
	mObjectController = i_objectController;
}


void Engine::Camera::HandleMessage(Engine::utils::StringHash& i_message, RTTI* i_MessageSender, void* i_pMessageData)
{
	if (i_MessageSender != nullptr)
	{
		if (Engine::utils::StringHash("MoveCamera") == i_message)
		{
			//Engine::SharedPointer<Engine::GameObject> temp= SharedPointer<GameObject>(this); //Need to think about this
			switch (*(reinterpret_cast<Engine::typedefs::Direction*>(i_pMessageData)))
			{
			case Engine::typedefs::NONE:
				break;
			case Engine::typedefs::UP:
				if (mObjectController)
					mObjectController->updateGameObject(*this, Engine::typedefs::UP);
				break;
			case Engine::typedefs::DOWN:
				if (mObjectController)
					mObjectController->updateGameObject(*this, Engine::typedefs::DOWN);
				break;
			case Engine::typedefs::LEFT:
				if (mObjectController)
					mObjectController->updateGameObject(*this, Engine::typedefs::LEFT);
				break;
			case Engine::typedefs::RIGHT:
				if (mObjectController)
					mObjectController->updateGameObject(*this, Engine::typedefs::RIGHT);
				break;
			}
		}
	}
}




