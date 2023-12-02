#include <winsock2.h>
#include <WS2tcpip.h>

#include "Socket.h"
#include "../UtilString.h"
#include "ConnResetException.h"

static int sSocketId = 0;

Socket::Socket()
{
	if (++sSocketId == 1)
	{
		WSAData wsaData;
		WSAStartup(MAKEWORD(2, 2), &wsaData); // this is executed once during app startup
	}
}

Socket::~Socket()
{
	close();

	if (--sSocketId == 0)
		WSACleanup(); // this is executed once during app teardown
}

bool Socket::init(uint32_t timeout)
{
	if ((m_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		printf("socket error\n");
		return false;
	}

	if (timeout)
		setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(DWORD));
	m_timeout = timeout;
	return true;
}

bool Socket::isValid()
{
	return m_socket >= 0;
}

int Socket::send(const char* msg, size_t len)
{
	if (len <= 0)
	{
		return 0;
	}
	// TODO: посылать размер пакета в первых восьми байтах
	std::string msg_str(msg, len);
	size_t size = len;
	std::string len_str((char*)(&size), sizeof(size));
	std::string msg_with_len(len_str + msg_str);
	return ::send(m_socket, msg_with_len.data(), msg_with_len.size(), 0);
}

int Socket::sendStr(const std::string& str)
{
	return send(str.c_str(), str.length());
}

int Socket::recv()
{
	size_t pack_len = 0;
	int recv_res = ::recv(m_socket, (char *)&pack_len, sizeof(pack_len), 0); // первые 8Б
	if (recv_res == SOCKET_ERROR)
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
	m_recv.clear();
	m_recv.resize(pack_len);
	recv_res = ::recv(m_socket, m_recv.data(), pack_len, 0);
	if (recv_res == SOCKET_ERROR || recv_res != pack_len)
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
	return recv_res;
}

char* Socket::data()
{
	return m_recv.data();
}

void Socket::close()
{
	if (m_socket != -1)
	{
		shutdown(m_socket, SD_BOTH);
		closesocket(m_socket);
	}
}
