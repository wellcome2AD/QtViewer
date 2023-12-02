#pragma once

enum eventType
{
	messagesUpdate, connReset
};

class Event
{
public:
	virtual ~Event() = default;
	virtual eventType GetEventType() const = 0;
};
