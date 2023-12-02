#pragma once

#include "IConvertableToHttp.h"

enum content_type
{
	invalid, text_html, image_png
};

inline std::string toString(content_type t)
{
	switch (t)
	{
	case text_html:
		return "text/html";
	case image_png:
		return "image/png";
	default:
		assert(0);
		break;
	}
	return std::string();
}

class ResponseBuilder
{
public:
	void SetCode(int code);
	void SetContentType(content_type t);
	void SetContent(IConvertableToHttp& data);
	std::string Build();

private:
	std::string setHeader(int code) const;
	std::string setContentData() const;

private:
	int _code = 404;
	content_type _type = invalid;
	std::string _content;
};