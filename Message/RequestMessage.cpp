#include "RequestMessage.h"
#include "../Serializer/Serializer.h"

RequestMessage::RequestMessage(const std::string& message) : _message(message) {}

RequestMessage* RequestMessage::Clone() const
{
    return new RequestMessage(*this);
}

format RequestMessage::GetFormat() const { return getReq; }

std::string RequestMessage::GetMsg() const { return _message; }

void RequestMessage::SetMsg(const std::string& m) { _message = m; }

void RequestMessage::Deserialize(Deserializer& d) {}

void RequestMessage::Serialize(Serializer& s) const {}
