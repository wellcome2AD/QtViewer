#pragma once

#include <memory>

#include "Event.h"
#include "../Message/IMessagePack.h"

class ConnResetEvent : public Event
{
public:
	ConnResetEvent(size_t client_num);
	virtual ~ConnResetEvent() override = default;
	virtual eventType GetEventType() const override;
	size_t GetNumber() const;

private:
	size_t _con_num;
};
