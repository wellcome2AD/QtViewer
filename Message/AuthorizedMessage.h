#pragma once

#include "IMessage.h"

class AuthorizedMessage : public IMessage {
public:
	AuthorizedMessage() = default;
	virtual ~AuthorizedMessage() override = default;
	AuthorizedMessage(const std::string& username, const std::string& password, const std::string& message);

	virtual AuthorizedMessage *Clone() const override = 0;

	virtual std::string GetMsg() const override;
	virtual void SetMsg(const std::string& m) override;

	virtual std::string GetUsername() const;
	virtual void SetUsername(const std::string& n);
	virtual std::string GetPassword() const;
	virtual void SetPassword(const std::string& p);

protected:
	std::string _username, _password, _message;
};
