#include <winsock2.h>
#include <clocale>

#include "SocketException.h"

SocketException::SocketException(int er_code)
{
	char* s_ptr = NULL;
	FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, er_code,
		0,
		(LPSTR)&s_ptr, 0, NULL);
	s = std::string(s_ptr);
	LocalFree(s_ptr);
}

const char* SocketException::what() const
{
	return s.c_str();
}

void printExc(const std::exception& ex)
{
	auto&& currentLocale = setlocale(LC_ALL, "");
	printf("ERROR: %s", ex.what());
	setlocale(LC_ALL, currentLocale);
}
