#ifndef __INPUT_CONTROLLER_H
#define __INPUT_CONTROLLER_H

#include "../../Utilities/SharedPointer.h"
#include "../../Utilities/IMessageHandler.h"
#include "../../Utilities/RTTI.h"

namespace Engine
{
	class InputController: public IMessageHandler
	{
	public:
		static SharedPointer<InputController> getInputController();
		void HandleMessage(Engine::utils::StringHash &, RTTI*, void* i_pMessageData) override;
		std::string getTypeInfo() override;
		bool isBothSameType(RTTI*, std::string) override;
	private:
		static SharedPointer<InputController> mInputController;
		std::string mTypeName;
		InputController();
	};
}

#endif