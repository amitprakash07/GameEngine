#ifndef __INPUT_CONTROLLER_H
#define __INPUT_CONTROLLER_H

#include "../../Utilities/SharedPointer.h"
#include "../../MessagingSystem/IMessageHandler.h"
#include "../../Utilities/RTTI.h"

namespace Engine
{
	class InputController: public IMessageHandler, public Engine::RTTI
	{
	public:
		static SharedPointer<InputController> getInputController();
		void HandleMessage(Engine::utils::StringHash &, RTTI* i_MessageSender, void* i_pMessageData) override;
		std::string getTypeInfo() override;
		bool isBothSameType(SharedPointer<RTTI>, std::string) override;
	private:
		static InputController* mInputController;
		std::string mTypeName;
		InputController();
	};
}

#endif