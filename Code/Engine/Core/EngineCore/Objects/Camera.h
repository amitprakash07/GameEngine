#ifndef __CAMERA_H
#define __CAMERA_H

#include "../../../Core/Utilities/IMessageHandler.h"
#include "../../../Core/Utilities/SharedPointer.h"
#include "../../Utilities/IObjectController.h"
#include "Object.h"
#include "../enginedefs.h"

namespace Engine
{
	class Camera : public IMessageHandler, Object
	{
	public:
		static SharedPointer<Camera> CreateCamera(std::string, Math::cVector,
			Math::cQuaternion, float i_fieldofView = 60.0f,
			float i_aspectRatio = static_cast<float>(800 / 600));
		Transformation getTransformation() override;
		void setTransformation(Engine::Math::cVector,
			Engine::Math::cQuaternion = Engine::Math::cQuaternion()) override;
		void draw() override {}
		void HandleMessage(Engine::utils::StringHash &, RTTI* i_MessageSender, void* i_pMessageData) override;
		void setCameraController(IObjectController*);
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
	private:
		Engine::Transformation mTransformation;
		std::string mCameraName;
		IObjectController* mObjectController;
		float fieldOfView;
		float aspectRatio;
		bool active;
		float nearPlane;
		float farPlane;
		MouseEventAndPosition mMouseCurrentStateAndPosition;
		MouseEventAndPosition mMousePreviousStateAndPosition;
		Camera(std::string, Math::cVector, Math::cQuaternion,
			float,
			float,
			float i_nearPlane = 0.1f,
			float u_farPlane = 100.0f);
		Camera();
	};
}

#endif