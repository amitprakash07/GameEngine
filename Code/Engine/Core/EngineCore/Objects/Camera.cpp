#include "Camera.h"
#include "../../../Core/Utilities/HashedString.h"
#include "../../../Core/EngineCore/EngineCore.h"
#include "../../Maths/Functions.h"
#include "../../Utilities/IObjectController.h"


Engine::SharedPointer<Engine::Camera> Engine::Camera::CreateCamera(std::string i_name,
	Math::Vector3 i_position,
	Math::Quaternion i_orientation,
	float i_fieldofView,
	float i_aspectRatio)
{
	SharedPointer<Engine::Camera> tempCamera(new Engine::Camera(i_name, i_position, i_orientation, i_fieldofView, i_aspectRatio), "Engine::Camera");
	Engine::utils::StringHash temp(Engine::EngineCore::getStringPool()->findString("UpdateObject"));
	Engine::utils::StringHash tempOne(Engine::EngineCore::getStringPool()->findString("ActionOnMouseEvent"));
	Engine::EngineCore::getMessagingSystem()->addMessageHandler(temp, 
		tempCamera.CastSharedPointer<IMessageHandler>(), 
		Engine::typedefs::HIGH);
	Engine::EngineCore::getMessagingSystem()->addMessageHandler(tempOne, 
		tempCamera.CastSharedPointer<IMessageHandler>(), Engine::typedefs::HIGH);
	return tempCamera;
}


Engine::Math::Vector3 Engine::Camera::getForwardVector()const
{
	return(mTransform.getForwardVector());
}


Engine::Camera::Camera()
{
	mCameraName = "";
	mTransform.setOrientation(Engine::Math::Quaternion());
	mTransform.setPosition(Engine::Math::Vector3());
	fieldOfView = 0.0f;
	aspectRatio = 0.0f;
	active = false;
	nearPlane = 0.0f;
	farPlane = 0.0f;
	mInitialTransform = Math::Transform();
	isInitialTransform = true;
}


Engine::Camera::Camera(std::string i_name, Math::Vector3 i_position,
	Math::Quaternion i_orientation,
	float i_fieldOfView,
	float i_aspectRatio,
	float i_nearPlane,
	float i_farPlane
	)
{
	mTransform = Math::Transform();
	mCameraName = i_name;
	mTransform.setOrientation(i_orientation);
	mTransform.setPosition(i_position);
	fieldOfView = Engine::Math::ConvertDegreesToRadians(i_fieldOfView);
	aspectRatio = i_aspectRatio;
	active = false;
	nearPlane = i_nearPlane;
	farPlane = i_farPlane;
	isInitialTransform = true;
	isPlayer = false;
	mObjectType = ObjectType::NONE;
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


Engine::Math::Transform Engine::Camera::getTransform()
{
	return mTransform;
}

void Engine::Camera::setTransform(Engine::Math::Vector3 i_positionOffset,
	Engine::Math::Quaternion i_orientation)
{
	mTransform.setOrientation(i_orientation);
	mTransform.setPosition(i_positionOffset);
	if(isInitialTransform)
	{
		isInitialTransform = false;
		mInitialTransform = mTransform;
	}
}


void Engine::Camera::resetTransform()
{
	mTransform = mInitialTransform;
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




void Engine::Camera::HandleMessage(Engine::utils::StringHash& i_message, SharedPointer<RTTI> i_MessageSender, void* i_pMessageData)
{
	if (!i_MessageSender.isNull() && Engine::utils::StringHash("UpdateObject") == i_message && !mObjectController.isNull())
		mObjectController->updateObject(*this, *reinterpret_cast<Engine::typedefs::ActionWithKeyBound*>(i_pMessageData));
}

void Engine::Camera::updateObject()
{
	typedefs::ActionWithKeyBound action;
	action.action = typedefs::Default;
	action.keyVal = 0x00;
	if (!mObjectController.isNull())
		mObjectController->updateObject(*this, action);
}


void Engine::Camera::setObjectController(SharedPointer<IObjectController>i_objectController)
{
	if (!i_objectController.isNull())
		mObjectController = i_objectController;
}


bool Engine::Camera::isCollidable()
{
	return false;
}

bool Engine::Camera::isPhysicsEnabled()
{
	return false;
}

void Engine::Camera::enableCollision(bool)
{
	//Stub
}

void Engine::Camera::enablePhysics(bool)
{
	//Stub
}

void Engine::Camera::receiveShadow(bool)
{
	//Stub
}

void Engine::Camera::castShadow(bool, Graphics::ShadowMethod)
{
	//stub
}

bool Engine::Camera::castingShadowEnabled()
{
	return false;
}

bool Engine::Camera::receivingShadowEnabled()
{
	return false;
}


bool Engine::Camera::IsPlayer()
{
	return isPlayer;
}

void Engine::Camera::setPlayer(bool i_isPlayer)
{
	isPlayer = i_isPlayer;
}


Engine::ObjectType Engine::Camera::getObjectType()
{
	return mObjectType;
}


void Engine::Camera::setObjectType(ObjectType iObjectType)
{
	mObjectType = iObjectType;
}



















