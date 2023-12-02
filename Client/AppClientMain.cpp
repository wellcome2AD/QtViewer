#include <vector>
#include <assert.h>
#include <iostream>

#include "Appclient.h"
#include "../Message/AuthorizedMessage.h"
#include "../Message/TextMessage.h"
#include "../Message/FileMessage.h"
#include "../helpers/UtilFile.h"
#include "../helpers/UtilString.h"

/*int main(int argc, char* argv[])
{
	if (argc < 5 || split(argv[3], ":").size() != 2)
	{
		printf("USAGE: Client.exe <USER_NAME> <PASSWORD> <HOST:PORT> <MESSAGE>\n\n");
		printf("Example: Client.exe user 1234 192.168.1.1:12345 Hello world!\n");
		return 0;
	}

	std::string user_name = argv[1], password = argv[2], address = argv[3];
	std::string msg = argv[4];
	for (int i = 5; i < argc; i++)
	{
		msg += std::string(" ") + argv[i];
	}

	AuthorizedMessage* msg_to_send = nullptr;
	format msg_format = fileExists(msg) ? file : text;
	switch (msg_format) {
	case text:
	{
		msg_to_send = new TextMessage(user_name, password, msg);
		break;
	}
	case file:
	{
		auto dot_befor_ext = msg.find_last_of('.');
		auto extension = msg.substr(dot_befor_ext);
		auto file_data = readFromFile(msg);
		msg_to_send = new FileMessage(user_name, password, extension, file_data);
	}
	default:
		assert(0);
		break;
	}
	Client cl;
	cl.send(address, msg_to_send);
}*/

int main()
{
	// посылка этого сообщения на 127.0.0.1:8080
	std::string user_name = "alice", password = "1234", address = "127.0.0.1:8080", msg = "Hello";	
	AuthorizedMessage* msg_to_send = nullptr;
	format msg_format = fileExists(msg) ? file : text;
	switch (msg_format) {
	case text:
	{
		msg_to_send = new TextMessage(user_name, password, msg);
		break;
	}
	case file:
	{
		auto dot_befor_ext = msg.find_last_of('.');
		auto extension = msg.substr(dot_befor_ext);
		auto file_data = readFromFile(msg);
		msg_to_send = new FileMessage(user_name, password, extension, file_data);
	}
	default:
		assert(0);
		break;
	}	
	Client cl;
	cl.send(address, msg_to_send);
	auto &&msgs = cl.recv();
	if (msgs)
	{
		std::cout << std::string(14, '-') << std::endl;
		for (auto &&m : msgs->GetMsgs())
		{
			auto&& authorized_m = static_cast<AuthorizedMessage*>(m.get());
			std::cout << authorized_m->GetUsername() << ": " << toString(authorized_m->GetFormat()) << " " << authorized_m->GetMsg() << std::endl;
		}
		std::cout << std::string(14, '-') << std::endl;
	}
}
