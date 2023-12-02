#pragma once

#include "Deserializer.h"

class Socket;

typedef size_t MSG_FIELD_SIZE_TYPE;

class SocketDeserializer : public Deserializer
{
private:
	Socket* _socket;
	size_t _offset;
	size_t _count;

public:
	SocketDeserializer(Socket* s);
	virtual ~SocketDeserializer() override = default;
	virtual void Recv() override;
	virtual char GetChar() override;
};
