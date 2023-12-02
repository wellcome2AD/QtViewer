#include "TextMessage.h"
#include "../Deserializer/DeserializerOperators.h"
#include "../Serializer/SerializerOperators.h"

void TextMessage::Serialize(Serializer& s) const
{
	s << _username << _password << _message;
}

TextMessage* TextMessage::Clone() const
{
	return new TextMessage(*this);
}

void TextMessage::Deserialize(Deserializer& d)
{
	d >> _username >> _password >> _message;
}

format TextMessage::GetFormat() const
{
	return text;
}
