#pragma once

#include <vector>
#include <memory>

#include "IMessage.h"

class IMessagePack : public IMessage
{
public:
	virtual ~IMessagePack() override = default;
	virtual IMessagePack* Clone() const override = 0;
	virtual void AddMsg(const IMessage& msg) = 0;
	virtual const std::vector<std::unique_ptr<IMessage>>& GetMsgs() const = 0;
};
