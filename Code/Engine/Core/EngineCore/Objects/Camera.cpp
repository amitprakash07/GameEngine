#include "Camera.h"
#include "../../../Core/Utilities/HashedString.h"
#include "../../../Core/EngineCore/EngineCore.h"
#include "../../Maths/Functions.h"


Engine::SharedPointer<Engine::Camera> Engine::Camera::CreateCamera(std::string i_name,
	Math::Vector3 i_position,
	Math::Quaternion i_orientation,
	float i_fieldofView,
	float i_aspectRatio)
{
	SharedPointer<Engine::Camera> tempCamera(new Engine::Camera(i_name, i_position, i_orientation, i_fieldofView, i_aspectRatio), "Engine::Camera");
	Engine::utils::StringHash temp(Engine::EngineCore::getStringPool()->findString("UpdateObject"));
	Engine::utils::StringHash tempOne(Engine::EngineCore::getStringPool()->findString("MouseEvent"));
	Engine::EngineCore::getMessagingSystem()->addMessageHandler(temp, reinterpret_cast<IMessageHandler*>(tempCamera.getRawPointer()), Engine::typedefs::HIGH);
	Engine::EngineCore::getMessagingSystem()->addMessageHandler(tempOne, reinterpret_cast<IMessageHandler*>(tempCamera.getRawPointer()), Engine::typedefs::HIGH);
	return tempCamera;
}


Engine::Camera::Camera()
{
	mObjectController = nullptr;
	mCameraName = "";
	mTransformation.mOrientation = Engine::Math::Quaternion();
	mTransformation.mPositionOffset = Engine::Math::Vector3();
	fieldOfView = 0.0f;
	aspectRatio = 0.0f;
	active = false;
}


Engine::Camera::Camera(std::string i_name, Math::Vector3 i_position,
	Math::Quaternion i_orientation,
	float i_fieldOfView,
	float i_aspectRatio,
	float i_nearPlane,
	float i_farPlane
	)
{
	mObjectController = nullptr;
	mTransformation = Math::Transformation();
	mCameraName = i_name;
	mTransformation.mOrientation = i_orientation;
	mTransformation.mPositionOffset = i_position;
	fieldOfView = Engine::Math::ConvertDegreesToRadians(i_fieldOfView);
	aspectRatio = i_aspectRatio;
	active = false;
	nearPlane = i_nearPlane;
	farPlane = i_farPlane;
}

void Engine::Camera::setFieldOfView(float i_fieldOfView)
{
	fieldOfView = Engine::Math::ConvertDegreesToRadians(i_fieldOfView);
}

float Engine::Camera::getFieldOfView() const
{
	return fieldOfView;
}


void Engine::Camera::setAspectRatio(float i_aspectRatio)
{
	aspectRatio = i_aspectRatio;
}


float Engine::Camera::getAspectRatio() const
{
	return aspectRatio;
}


void Engine::Camera::activateCamera(bool i_activate)
{
	active = i_activate;
}

bool Engine::Camera::isActive() const
{
	return active;
}


Engine::Math::Transformation Engine::Camera::getTransformation()
{
	return mTransformation;
}

void Engine::Camera::setTransformation(Engine::Math::Vector3 i_positionOffset,
	Engine::Math::Quaternion i_orientation)
{
	mTransformation.mOrientation = i_orientation;
	mTransformation.mPositionOffset = i_positionOffset;
}


void Engine::Camera::setCameraController(IObjectController* i_objectController)
{
	mObjectController = i_objectController;
}

float Engine::Camera::getNearPlane() const
{
	return nearPlane;
}

float Engine::Camera::getFarPlane() const
{
	return farPlane;
}


std::string Engine::Camera::getCameraName() const
{
	return mCameraName;
}



void Engine::Camera::setFarPlane(float i_farPlane)
{
	farPlane = i_farPlane;
}


void Engine::Camera::setNearPlane(float i_nearPlane)
{
	nearPlane = i_nearPlane;
}




void Engine::Camera::HandleMessage(Engine::utils::StringHash& i_message, RTTI* i_MessageSender, void* i_pMessageData)
{
	if (i_MessageSender != nullptr && Engine::utils::StringHash("UpdateObject") == i_message && mObjectController)
		mObjectController->updateObject(*this, *reinterpret_cast<Engine::typedefs::Action*>(i_pMessageData));
}




