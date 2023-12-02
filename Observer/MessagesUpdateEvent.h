#pragma once

#include <memory>

#include "Event.h"
#include "../Message/IMessagePack.h"
#include "../Message/MessagePack.h"

class MessagesUpdateEvent : public Event
{
public:
	MessagesUpdateEvent(size_t client_num, const IMessage& msg);
	virtual ~MessagesUpdateEvent() override = default;
	virtual eventType GetEventType() const override;
	size_t GetClientNum() const;
	const IMessage& GetMsg() const;

private:
	size_t _client_num;
	const IMessage& _msg;
};
