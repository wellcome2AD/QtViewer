#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Serializer.h"
#include "../Message/IMessage.h"
#include "../Message/TextMessage.h"
#include "../Message/FileMessage.h"
#include "../Message/RequestMessage.h"

typedef size_t MSG_FIELD_SIZE_TYPE;
class my_endl {};

inline Serializer& operator<<(Serializer& s, my_endl endl)
{
	s.Flush();
	return s;
}

inline Serializer& operator<<(Serializer& s, MSG_FIELD_SIZE_TYPE size)
{
	auto size_str = std::string((char*)(&size), sizeof(MSG_FIELD_SIZE_TYPE));
	for(size_t i = 0; i < size_str.size(); ++i)
	{
		s.PutChar(size_str[i]);
	}
	return s;
}

inline Serializer& operator<<(Serializer& s, const std::string& str)
{
	MSG_FIELD_SIZE_TYPE size = str.size();
	s << size;
	for(size_t i = 0; i < size; ++i)
	{
		s.PutChar(str[i]);
	}
	return s;
}

inline Serializer& operator<<(Serializer& s, const IMessage* m)
{
	if (!m)
	{
		return s;
	}
	std::string format = toString(m->GetFormat());
	for(size_t i = 0; i < format.size(); ++i)
	{
		s.PutChar(format[i]);
	}
	m->Serialize(s);
	return s;
}

inline Serializer& operator<<(Serializer& s, const IMessage& m)
{
	s << &m;
	return s;
}

template <class T>
inline Serializer& operator<<(Serializer& s, const std::vector<T>& v)
{
	s << v.size();
	for (auto&& el : v)
	{
		s << el;
	}
	return s;
}

template <class T>
inline Serializer& operator<<(Serializer& s, const std::shared_ptr<T>& ptr)
{
	assert(ptr);
	s << ptr.get();
	return s;
}

template <class T>
inline Serializer& operator<<(Serializer& s, const std::unique_ptr<T>& ptr)
{
	assert(ptr);
	s << ptr.get();
	return s;
}
