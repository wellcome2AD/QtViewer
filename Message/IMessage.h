#pragma once

#include <string>
#include <assert.h>
#include <IClonable.h>

//#include "../Client/IClonable.h"

#define SIZE_OF_FORMAT 4

class Deserializer;
class Serializer;

enum format {
	text, file, getReq, msgPack
};

inline std::string toString(format f) {
	char res[SIZE_OF_FORMAT + 1];
	memset(res, 0, (SIZE_OF_FORMAT + 1) * sizeof(char));
	switch (f)
	{
	case text:
		strncpy(res, "text", SIZE_OF_FORMAT);
		break;
	case file:
		strncpy(res, "file", SIZE_OF_FORMAT);
		break;
	case getReq:
		strncpy(res, "GET ", SIZE_OF_FORMAT);
		break;
	case msgPack:
		strncpy(res, "mpck", SIZE_OF_FORMAT);
		break;
	default:
		assert(0);
		break;
	}
	return std::string(res);
}

inline format fromString(std::string f)
{
	if (f == "text")
		return text;
	else if (f == "file")
		return file;
	else if (f == "GET ")
		return getReq;
	else if(f == "mpck")
		return msgPack;
	assert(0);
	return text;
}

class IMessage : public IClonable {
public:
	virtual ~IMessage() = default;
	virtual IMessage* Clone() const override = 0;
	virtual format GetFormat() const = 0;
	virtual std::string GetMsg() const = 0;
	virtual void SetMsg(const std::string& m) = 0;
	virtual void Deserialize(Deserializer& d) = 0;
	virtual void Serialize(Serializer& s) const = 0;
};
