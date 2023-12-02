#pragma once

#include <exception>
#include <string>

void printExc(const std::exception& ex);

class SocketException : public std::exception
{
public:
	SocketException(int er_code);
	virtual ~SocketException() = default;
	virtual const char* what() const override;

private:
	std::string s;
};
