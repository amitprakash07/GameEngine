#ifndef __CAMERA_H
#define __CAMERA_H

#include "../../../Core/Utilities/IMessageHandler.h"
#include "../../../Core/Utilities/SharedPointer.h"
//#include "../../Utilities/IObjectController.h"
#include "Object.h"
#include "../enginedefs.h"

namespace Engine
{
	class Camera : public IMessageHandler, Object
	{
	public:
		static SharedPointer<Camera> CreateCamera(std::string, Math::Vector3,
			Math::Quaternion, float i_fieldofView = 60.0f,
			float i_aspectRatio = static_cast<float>(800 / 600));
		Math::Transform getTransform() override;
		void setTransform(Engine::Math::Vector3,
			Engine::Math::Quaternion = Engine::Math::Quaternion()) override;
		void resetTransform() override;
		void draw(bool) override {}
		void HandleMessage(Engine::utils::StringHash &, RTTI* i_MessageSender, void* i_pMessageData) override;
		//void setCameraController(IObjectController*);
		void setFieldOfView(float);
		float getFieldOfView() const;
		void setAspectRatio(float);
		float getAspectRatio() const;
		bool isBothSameType(RTTI*, std::string) const override { return true; }
		void activateCamera(bool);
		bool isActive() const;
		std::string getTypeInfo() const override { return ""; }
		void setNearPlane(float i_nearPlane);
		void setFarPlane(float i_farPlane);
		float getNearPlane() const;
		float getFarPlane() const;
		std::string getCameraName() const;
		bool isRenderable() const override { return false; }
		bool isDebugObject() const override { return false; }
		Engine::Math::Vector3 getForwardVector()const;
		void updateObject() override;
		void setScale(float x = 1.0f, float y = 1.0f, float z = 1.0f) override{/*Stub*/};
		void setObjectController(IObjectController* objectController) override;

	private:
		Engine::Math::Transform mTransform;
		Math::Transform mInitialTransform;
		bool isInitialTransform;
		std::string mCameraName;
		IObjectController* mObjectController;
		float fieldOfView;
		float aspectRatio;
		bool active;
		float nearPlane;
		float farPlane;
		MouseEventAndPosition mMouseCurrentStateAndPosition;
		MouseEventAndPosition mMousePreviousStateAndPosition;
		Camera(std::string, Math::Vector3, Math::Quaternion,
			float,
			float,
			float i_nearPlane = 0.1f,
			float u_farPlane = 10000.0f);
		Camera();
	};
}

#endif