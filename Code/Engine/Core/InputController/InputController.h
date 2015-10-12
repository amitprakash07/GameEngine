#ifndef __INPUT_CONTROLLER_H
#define __INPUT_CONTROLLER_H

#include "../Utilities/SharedPointer.h"
#include "../MessagingSystem/IMessageHandler.h"
#include "../EngineCore/RTTI.h"

namespace Engine
{
	class InputController: public IMessageHandler, public Engine::RTTI
	{
	public:
		static SharedPointer<InputController> getINputController();
		void HandleMessage(Engine::utils::StringHash &, RTTI *i_MessageSender, void* i_pMessageData) override;
	private:
		static InputController* mInputController;
		InputController();
	};
}

#endif