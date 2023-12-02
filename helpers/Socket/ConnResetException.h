#pragma once

#include "SocketException.h"

class ConnResetException : public SocketException
{
public:
	using SocketException::SocketException;
};
