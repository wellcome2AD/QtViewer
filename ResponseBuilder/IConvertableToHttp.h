#pragma once

#include <string>

class IConvertableToHttp 
{
public:
	virtual std::string GetHttp() const = 0;
};