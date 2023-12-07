#include <SocketDeserializer.h>
#include <Socket/Socket.h>

//#include "SocketDeserializer.h"
//#include "../helpers/socket/Socket.h"

SocketDeserializer::SocketDeserializer(Socket* s) : _socket(s), _offset(0), _count(0) {}

void SocketDeserializer::Recv()
{
	_count = _socket->recv();
	_offset = 0;
}

char SocketDeserializer::GetChar()
{
	if (_offset == _count)
	{
		Recv();
	}
	char res = _socket->data()[_offset];
	++_offset;	
	return res;
}
