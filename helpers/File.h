#pragma once

#include <string>
#include <IConvertableToHttp.h>

//#include "../ResponseBuilder/IConvertableToHttp.h"

class File : public IConvertableToHttp
{
public:
	File(const std::string& path);
	std::string GetPath() const;
	std::string GetData() const;
	virtual std::string GetHttp() const override;

private:
	std::string _path, _data;

	
};
