#ifndef __CAMERA_H
#define __CAMERA_H

#include "../../../Core/Utilities/IMessageHandler.h"
#include "../../../Core/Utilities/SharedPointer.h"
#include "../../Utilities/IObjectController.h"
#include "Object.h"

namespace Engine
{
	class Camera: public IMessageHandler, Object
	{
	public:
		static SharedPointer<Camera> CreateCamera(std::string, Math::cVector, 
			Math::cQuaternion,float i_fieldofView = 60.0f,
			float i_aspectRatio = static_cast<float>(800 / 600));
		Transformation getTransformation() override;
		void setTransformation(Engine::Math::cVector, 
			Engine::Math::cQuaternion = Engine::Math::cQuaternion()) override;
		void HandleMessage(Engine::utils::StringHash &, RTTI* i_MessageSender, void* i_pMessageData) override;
		void setCameraController(IObjectController*);
		void setFieldOfView(float);
		float getFieldOfView();
		void setAspectRatio(float);
		float getAspectRatio();
		bool isBothSameType(RTTI*, std::string) override { return true; }
		void activateCamera(bool);
		bool isActive();
		std::string getTypeInfo() override { return ""; }
	private:
		Engine::Transformation mTransformation;
		std::string mCameraName;
		IObjectController* mObjectController;
		float fieldOfView;
		float aspectRatio;
		bool active;
		Camera(std::string, Math::cVector, Math::cQuaternion,
			float ,
			float );
		Camera();
	};
}

#endif