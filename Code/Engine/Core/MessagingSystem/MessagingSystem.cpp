#include "MessagingSystem.h"
#include <algorithm>
#include <assert.h>


Engine::SharedPointer<Engine::MessagingSystem> Engine::MessagingSystem::mMessagingSystem;

Engine::SharedPointer<Engine::MessagingSystem> Engine::MessagingSystem::getMessagingSystem()
{
	if (mMessagingSystem.isNull())
	{
		/*mMessagingSystem = EngineController::GameEngine::isEngineInitialized() ?
			new(EngineController::GameEngine::getMemoryManager()->__alloc(sizeof(MessagingSystem))) MessagingSystem() :
			new MessagingSystem();*/


		SharedPointer<Engine::MessagingSystem> temp(SharedPointer<MessagingSystem>(new MessagingSystem(), "Engine::MessagingSystem"));
		mMessagingSystem = temp;
	}
	return mMessagingSystem;
}

Engine::MessagingSystem::MessagingSystem()
{
	//Nothing Required
}

Engine::MessagingSystem::~MessagingSystem()
{
	//delete mMessagingSystem;
}

void Engine::MessagingSystem::addMessageHandler(Engine::utils::StringHash & i_message, IMessageHandler* i_pMessageHandler, Engine::typedefs::Priority i_priority)
{
	assert(i_pMessageHandler != nullptr); // != nullptr);
	assert(!i_message.isNil());
	MessageHandle temp{ i_pMessageHandler, i_priority };
	m_MessageHandlers[i_message].push_back(temp);
	std::vector<MessageHandle> tempList = m_MessageHandlers[i_message];
	std::sort(tempList.begin(), tempList.end());
}

void Engine::MessagingSystem::sendMessage(Engine::utils::StringHash & i_message, RTTI* i_messageSender, void* message_data)
{
	assert(i_messageSender!=nullptr); //!= nullptr);
	assert(!i_message.isNil());
	std::vector<MessageHandle> tempList = m_MessageHandlers[i_message];
	size_t handleCount = tempList.size();
	for (size_t i = 0; i < handleCount; i++)
	{
		tempList[i].mHandler->HandleMessage(i_message, i_messageSender, message_data);
	}
}

bool Engine::MessagingSystem::removeMessageHandler(Engine::utils::StringHash & i_message, IMessageHandler* i_messageHandler)
{
	//MessagedAssert(i_messageHandler != nullptr, "Null Message Handler - Removal not possible");
	std::vector<Engine::MessageHandle> temp = m_MessageHandlers[i_message];
	for (unsigned __int16 i = 0; i < temp.size(); i++)
	{
		if (temp[i].mHandler == i_messageHandler)
		{
			temp.erase(temp.begin() + i);
			return true;
		}
	}
	return false;
}


