

//template <typename T>
//void Engine::MessagingSystem::sendMessage(Engine::utils::StringHash & i_message, SharedPointer<T> i_messageSender, void* message_data)
//{
//	assert(!i_messageSender.isNull()); //!= nullptr);
//	assert(!i_message.isNil());
//	std::vector<MessageHandle> tempList = m_MessageHandlers[i_message];
//	size_t handleCount = tempList.size();
//	for (size_t i = 0; i < handleCount; i++)
//	{
//		tempList[i].mHandler->HandleMessage(i_message, i_messageSender.getVoidPointer(), message_data);
//	}
//}