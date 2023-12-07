#pragma once

#include <AuthorizedMessage.h>

//#include "AuthorizedMessage.h"

class FileMessage : public AuthorizedMessage {
public:
	FileMessage() = default;
	virtual ~FileMessage() override = default;
	FileMessage(const std::string& username, const std::string& password, const std::string& extension, const std::string& message);
	
	virtual FileMessage *Clone() const override;

	virtual void Deserialize(Deserializer& d) override;
	virtual void Serialize(Serializer& s) const override;
	virtual format GetFormat() const override;

	std::string GetExtension() const;
	void SetExtension(const std::string& e);

private:
	std::string _extension;
};
