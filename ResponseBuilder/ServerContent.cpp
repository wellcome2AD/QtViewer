#include "ServerContent.h"
#include "../../helpers/UtilFile.h"

std::string ServerContent::GetHttp() const
{
	std::string payload = _body_begin;
	auto endsWith = [](const std::string& fileName, const std::string& ext) {
		return fileName.substr(fileName.size() - ext.size()) == ext;
	};
	for (auto&& [user, msg] : m_data)
	{
		if (fileExists("resources/" + msg) && (endsWith(msg, ".png") || endsWith(msg, ".jpg")))
		{
			payload += "<p>" + user + ":<br><img src=\"/" + msg + "\"></p>\n";
		}
		else
		{
			payload += (user + ": " + msg + "<br>"); // collect all the feed and send it back to browser
		}
	}
    return payload + _end;
}

void ServerContent::push_back(std::pair<std::string, std::string> v)
{
	m_data.push_back(v);
}

std::pair<std::string, std::string> ServerContent::back() const
{
	return m_data.back();
}

std::vector<std::pair<std::string, std::string>>::iterator ServerContent::begin() { return m_data.begin(); }

std::vector<std::pair<std::string, std::string>>::iterator ServerContent::end() { return m_data.end(); }

bool ServerContent::empty() const
{
	return m_data.empty();
}
