#pragma once

#include <memory>
#include <Deserializer.h>
#include <IMessage.h>
#include <TextMessage.h>
#include <FileMessage.h>
#include <RequestMessage.h>
#include <MessagePack.h>
#include <UtilString.h>

//#include "Deserializer.h"
//#include "../Message/IMessage.h"
//#include "../Message/TextMessage.h"
//#include "../Message/FileMessage.h"
//#include "../Message/RequestMessage.h"
//#include "../Message/MessagePack.h"
//#include "../helpers/UtilString.h"

typedef size_t MSG_FIELD_SIZE_TYPE;

inline Deserializer& operator>>(Deserializer&  d, MSG_FIELD_SIZE_TYPE& size)
{
	char data[sizeof(MSG_FIELD_SIZE_TYPE)];
	for (size_t i = 0; i < sizeof(MSG_FIELD_SIZE_TYPE); ++i)
	{
		data[i] = d.GetChar();
	}
	size = *((MSG_FIELD_SIZE_TYPE*)data);

	return d;
}

inline Deserializer& operator>>(Deserializer& d, std::string& str)
{
	MSG_FIELD_SIZE_TYPE size;
	d >> size;

	for (size_t i = 0; i < size; ++i)
	{
		str.push_back(d.GetChar());
	}

	return d;
}

inline Deserializer& operator>>(Deserializer& d, IMessage*& m)
{
	std::string type;
	for (size_t i = 0; i < SIZE_OF_FORMAT; ++i)
	{
		type.push_back(d.GetChar());
	}
	format f = fromString(type);
	switch (f)
	{
	case text:
	{
		m = new TextMessage();
		break;
	}
	case file:
	{
		m = new FileMessage();
		break;
	}
	case getReq:
	{
		char c;
		std::vector<char> message;
		while ((c = d.GetChar()) != ' ')
		{
			message.push_back(c);
		}
		message.push_back('\0');
		const std::string& filename = join(split(std::string(message.data()), "/"), "\\");
		m = new RequestMessage(filename);
		break;
	}
	case msgPack:
	{
		m = new MessagePack();
		break;
	}
	default:
		assert(0);
		break;
	}

	if (m)
	{
		m->Deserialize(d);
	}

	return d;
}

template <class T>
inline Deserializer& operator>>(Deserializer& d, std::vector<T>& v)
{
	size_t size;
	d >> size;
	v = std::vector<T>(size);
	for (size_t i = 0; i < size; ++i)
	{
		d >> v[i];
	}
	return d;
}

template <class T>
inline Deserializer& operator>>(Deserializer& d, std::shared_ptr<T>& ptr)
{
	T* data = nullptr;
	d >> data;
	ptr.reset(data);
	return d;
}

template <class T>
inline Deserializer& operator>>(Deserializer& d, std::unique_ptr<T>& ptr)
{
	T* data = nullptr;
	d >> data;
	ptr.reset(data);
	return d;
}
