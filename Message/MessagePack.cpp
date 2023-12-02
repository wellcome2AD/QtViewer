#include "MessagePack.h"
#include "../Deserializer/DeserializerOperators.h"
#include "../Serializer/SerializerOperators.h"

MessagePack::MessagePack(const MessagePack& other)
{
    for (auto&& m : other._msgs)
        _msgs.push_back(std::unique_ptr<IMessage>(m->Clone()));
}

MessagePack* MessagePack::Clone() const
{
    return new MessagePack(*this);
}

format MessagePack::GetFormat() const { return msgPack; }

std::string MessagePack::GetMsg() const { return std::string(); }

void MessagePack::SetMsg(const std::string& m) {}

void MessagePack::Deserialize(Deserializer& d)
{
    d >> _msgs;
}

void MessagePack::Serialize(Serializer& s) const
{
    s << _msgs;
}

void MessagePack::AddMsg(const IMessage& msg)
{
    _msgs.push_back(std::unique_ptr<IMessage>(msg.Clone()));
}

void MessagePack::AddMsg(std::unique_ptr<IMessage>&& msg)
{
    _msgs.push_back(std::move(msg));
}

const std::vector<std::unique_ptr<IMessage>>& MessagePack::GetMsgs() const
{
    return _msgs;
}
