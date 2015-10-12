#ifndef __MESSAGING_SYSTEM_H
#define __MESSAGING_SYSTEM_H

#include "IMessageHandler.h"
#include "../Utilities/HashedString.h"
#include <map>
#include <vector>
#include "../Utilities/SharedPointer.h"

namespace Engine
{
	class MessagingSystem
	{
	public:
		static SharedPointer<MessagingSystem> getMessagingSystem();
		void addMessageHandler(Engine::utils::StringHash &, IMessageHandler *, Engine::typedefs::Priority);
		bool removeMessageHandler(Engine::utils::StringHash&, IMessageHandler*);
		void sendMessage(Engine::utils::StringHash, RTTI *, void* message_data = nullptr);
		~MessagingSystem();
	private:
		static MessagingSystem* mMessagingSystem;
		std::map<Engine::utils::StringHash, std::vector<Engine::MessageHandle>>  m_MessageHandlers;
		MessagingSystem();
	};
}

#endif