#ifndef __MESSAGING_SYSTEM_H
#define __MESSAGING_SYSTEM_H

#include "../Utilities/IMessageHandler.h"
#include "../Utilities/HashedString.h"
#include <map>
#include <vector>
#include "../Utilities/SharedPointer.h"
#include "../Utilities/RTTI.h"

namespace Engine
{	
	class MessagingSystem:public RTTI
	{
	public:
		static SharedPointer<MessagingSystem> getMessagingSystem();
		void addMessageHandler(Engine::utils::StringHash &, IMessageHandler*, Engine::typedefs::Priority);
		bool removeMessageHandler(Engine::utils::StringHash&, IMessageHandler*);
		~MessagingSystem();
		
		//template<typename T>
		void sendMessage(Engine::utils::StringHash&, RTTI* , void* message_data = nullptr);
		std::string getTypeInfo() const override { return ""; }
		bool isBothSameType(RTTI*, std::string)const  override { return true; }
	private:
		static SharedPointer<MessagingSystem> mMessagingSystem;
		std::map<Engine::utils::StringHash, std::vector<Engine::MessageHandle>>  m_MessageHandlers;
		MessagingSystem();
	};
}

#include "MessagingSystem.inl"

#endif