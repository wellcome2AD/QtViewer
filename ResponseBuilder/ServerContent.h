#pragma once

#include <vector>

#include "IConvertableToHttp.h"

class ServerContent : public IConvertableToHttp
{
public:
	virtual std::string GetHttp() const override;
	void push_back(std::pair<std::string, std::string> v);
	std::pair<std::string, std::string> back() const;
	std::vector<std::pair<std::string, std::string>>::iterator begin();
	std::vector<std::pair<std::string, std::string>>::iterator end();
	bool empty() const;

private:
	std::vector<std::pair<std::string, std::string>> m_data; // representation of uploaded data
	const char* _body_begin = "<!DOCTYPE html>"\
							  "<html>" \
							  "<head>" \
								"<meta charset = \"UTF-8\">" \
								"<title>Server Content</title>" \
							  "</head>" \
							  "<body>\n";
	const char* _end = "</body>\n</html>";
};