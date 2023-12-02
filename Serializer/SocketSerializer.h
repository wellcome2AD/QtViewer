#pragma once

#include <vector>

#include "Serializer.h"

class Socket;

class SocketSerializer : public Serializer
{
private:
	Socket* _socket;
	std::vector<char> _buffer;

public:
	SocketSerializer(Socket* s);
	virtual ~SocketSerializer() override = default;
	virtual void PutChar(char c) override;
	virtual void Flush() override;
};
