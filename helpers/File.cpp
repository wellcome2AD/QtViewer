#include <File.h>
#include <UtilFile.h>

//#include "File.h"
//#include "UtilFile.h"

File::File(const std::string& path) : _path(path) 
{
	unsigned long long size;
	auto temp = fileRead(path, &size);
	if (temp)
	{
		_data = std::string(temp, size);
		delete[] temp;
	}
	else
	{
		printf("Can't open file %s\n", path.c_str());
	}
}

std::string File::GetPath() const
{
	return _path;
}

std::string File::GetData() const
{
	return _data;
}

std::string File::GetHttp() const
{
	return _data;
}
