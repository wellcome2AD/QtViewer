#include "AuthorizedMessage.h"

AuthorizedMessage::AuthorizedMessage(const std::string& username, const std::string& password, const std::string& message)
{
	_username = username;
	_password = password;
	_message = message;
}

std::string AuthorizedMessage::GetUsername() const { return _username; }

void AuthorizedMessage::SetUsername(const std::string& n) { _username = n; }

std::string AuthorizedMessage::GetPassword() const { return _password; }

void AuthorizedMessage::SetPassword(const std::string& p) { _password = p; }

std::string AuthorizedMessage::GetMsg() const { return _message; }

void AuthorizedMessage::SetMsg(const std::string& m) { _message = m; }
