#include <assert.h>

#include "ResponseBuilder.h"

void ResponseBuilder::SetCode(int code) { _code = code; }

void ResponseBuilder::SetContentType(content_type t) { _type = t; }

void ResponseBuilder::SetContent(IConvertableToHttp& data) { _content = data.GetHttp(); }

std::string ResponseBuilder::Build()
{
	std::string response;
	response = setHeader(_code);
	if (_content.size() == 0)
	{
		_code = 404;
	}
	if (_code != 404)
	{
		response += setContentData() + _content;
	}
	return response;
}

static std::string codeStatus(int code) 
{
	switch (code)
	{
	case 200:
		return "OK";
	case 404:
		return "Not Found";
	default:
		assert(0);
		break;
	}
}

std::string ResponseBuilder::setHeader(int code) const
{
	return "HTTP/1.1 " + std::to_string(code) + " " + codeStatus(code) + "\r\n";
}
std::string ResponseBuilder::setContentData()  const
{
    return "Content-Type: " + toString(_type) + "\r\n" \
		   "Content-Length: " + std::to_string(_content.size()) + "\r\n\r\n";
}
