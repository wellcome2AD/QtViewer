#include "FileMessage.h"
#include "../Serializer/SerializerOperators.h"
#include "../Deserializer/DeserializerOperators.h"

FileMessage::FileMessage(const std::string& username, const std::string& password, const std::string& extension, const std::string& message)
	:
	  AuthorizedMessage(username, password, message),
	  _extension(extension)
{}

FileMessage* FileMessage::Clone() const
{
	return new FileMessage(*this);
}

void FileMessage::Deserialize(Deserializer& d)
{
	d >> _username >> _password >> _extension >> _message;
}

void FileMessage::Serialize(Serializer& s) const
{

	s << _username << _password << _extension << _message;
}

format FileMessage::GetFormat() const { return file; }

std::string FileMessage::GetExtension() const { return _extension; }

void FileMessage::SetExtension(const std::string& e) { _extension = e; }
