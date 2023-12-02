#pragma once

#include <vector>
#include <memory>
#include "IMessagePack.h"

class MessagePack : public IMessagePack
{
public:
	MessagePack() = default;
	MessagePack(const MessagePack& other);
	virtual ~MessagePack() override = default;
	virtual MessagePack* Clone() const override;	
	virtual format GetFormat() const override;
	virtual void Deserialize(Deserializer& d) override;
	virtual void Serialize(Serializer& s) const override;
	virtual void AddMsg(const IMessage& msg) override;
	virtual void AddMsg(std::unique_ptr<IMessage>&& msg);
	virtual const std::vector<std::unique_ptr<IMessage>>& GetMsgs() const override;

private:
	virtual std::string GetMsg() const override;
	virtual void SetMsg(const std::string& m) override;

private:
	std::vector<std::unique_ptr<IMessage>> _msgs;
};
