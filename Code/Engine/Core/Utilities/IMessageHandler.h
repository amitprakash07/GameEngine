#ifndef __I_MESSAGE_HANDLER_H
#define __I_MESSAGE_HANDLER_H

#include "../Utilities/HashedString.h"
#include "../Utilities/SharedPointer.h"
#include "../Utilities/additionaltypes.h"
#include "../Utilities/RTTI.h"


namespace Engine
{
	class IMessageHandler : public RTTI
	{
	public:
		virtual void HandleMessage(Engine::utils::StringHash &, RTTI* i_MessageSender, void* i_pMessageData) = 0; //Do not delete i_messageSenderPointer
		virtual std::string getTypeInfo() const override = 0;
		virtual bool isBothSameType(RTTI*, std::string) const override = 0;
		virtual  ~IMessageHandler() {};
		IMessageHandler() {};

	};

	struct _IMessageHandle
	{
		IMessageHandler* mHandler;
		Engine::typedefs::Priority mMessagePriority;

		_IMessageHandle(IMessageHandler* i_handler, Engine::typedefs::Priority i_priority)
		{
			//MessagedAssert(i_handler != nullptr, "Handle Pointer is NUll");
			mHandler = i_handler;
			mMessagePriority = i_priority;
		}

		bool operator<(_IMessageHandle i_other) const
		{
			return(mMessagePriority < i_other.mMessagePriority ? true : false);
		}
	};
	typedef _IMessageHandle MessageHandle;
}

#endif