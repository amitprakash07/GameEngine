#ifndef __INPUT_CONTROLLER_H
#define __INPUT_CONTROLLER_H

#include "../../Utilities/SharedPointer.h"
#include "../../Utilities/IMessageHandler.h"
#include "../../Utilities/RTTI.h"

namespace Engine
{
	class InputController : public IMessageHandler
	{
	public:
		static SharedPointer<InputController> getInputController();
		void HandleMessage(Engine::utils::StringHash &, SharedPointer<RTTI>, void* i_pMessageData) override;
		std::string getTypeInfo() const override;
		bool isBothSameType(SharedPointer<RTTI>, std::string) const override;
	private:
		static SharedPointer<InputController> mInputController;
		std::string mTypeName;
		InputController();
	};
}

#endif