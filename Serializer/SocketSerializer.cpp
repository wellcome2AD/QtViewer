#include <winsock2.h>

#include "SocketSerializer.h"
#include "../helpers/socket/Socket.h"
#include "SerializerOperators.h"
#include "../helpers/socket/ConnResetException.h"

SocketSerializer::SocketSerializer(Socket* s) : _socket(s) {}

void SocketSerializer::PutChar(char c)
{
	_buffer.push_back(c);
}

void SocketSerializer::Flush()
{
	if (!_buffer.empty())
	{
		auto return_val = _socket->send(_buffer.data(), _buffer.size());
		if (return_val == SOCKET_ERROR)
		{
			auto er_code = WSAGetLastError();
			if (er_code == WSAECONNRESET)
			{
				throw ConnResetException(er_code);
			}
			else
			{
				throw SocketException(er_code);
			}
		}
		_buffer.clear();
	}
}
