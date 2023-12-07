#pragma once

#include <AuthorizedMessage.h>

//#include "AuthorizedMessage.h"

class TextMessage : public AuthorizedMessage {
public:
	virtual ~TextMessage() override = default;
	using AuthorizedMessage::AuthorizedMessage;

	virtual TextMessage* Clone() const override;

	virtual void Deserialize(Deserializer& d) override;
	virtual void Serialize(Serializer& s) const override;
	virtual format GetFormat() const override;
};
