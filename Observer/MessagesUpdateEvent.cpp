#include "MessagesUpdateEvent.h"

MessagesUpdateEvent::MessagesUpdateEvent(size_t client_num, const IMessage& msg)
	: 
	 _client_num(client_num),
	 _msg(msg)
{}

eventType MessagesUpdateEvent::GetEventType() const
{
	return messagesUpdate;
}

size_t MessagesUpdateEvent::GetClientNum() const
{
	return _client_num;
}

const IMessage& MessagesUpdateEvent::GetMsg() const
{
	return _msg;
}
