#include <time.h>
#include <algorithm>
#include <QDebug>
#include <AppClient.h>
#include <SocketSerializer.h>
#include <SerializerOperators.h>
#include <SocketDeserializer.h>
#include <DeserializerOperators.h>
#include <UtilString.h>
#include <UtilFile.h>
#include <Socket/SocketException.h>
#include <Event.h>
#include <IObserver.h>
#include <MessagesUpdateEvent.h>
#include <MessagePack.h>
#include <Socket/ConnResetException.h>
#include <ConnResetEvent.h>

//#include "AppClient.h"
//#include "../Serializer/SocketSerializer.h"
//#include "../Serializer/SerializerOperators.h"
//#include "../Deserializer/SocketDeserializer.h"
//#include "../Deserializer/DeserializerOperators.h"
//#include "../helpers/UtilString.h"
//#include "../helpers/UtilFile.h"
//#include "../helpers/socket/SocketException.h"
//#include "../Observer/Event.h"
//#include "../Observer/IObserver.h"
//#include "../Observer/MessagesUpdateEvent.h"
//#include "../Message/MessagePack.h"
//#include "../helpers/Socket/ConnResetException.h"
//#include "../Observer/ConnResetEvent.h"

bool Client::connect(std::string url)
{
	if (_s)
	{
		return true;
	}
	_s = std::make_unique<SocketClient>();
	static constexpr int timeout = 60;
	auto start = clock();
	auto lasted = 0;
	bool succes_connect = false;
	_s->init();
	while (!(succes_connect = _s->connect(url)) && lasted < timeout)
	{
		lasted = (clock() - start) / CLOCKS_PER_SEC;
		printf("%d sec : ", lasted);
		_s->close();
		_s->init();
	}
	if (!succes_connect)
	{
		printf("connection error to %s due to timeout (%d sec)\n", url.c_str(), timeout);
	}
	return succes_connect;
}

void Client::disconnect()
{
	if (_s)
	{
		_s.reset();
	}
}

bool Client::send(const std::string& url, const AuthorizedMessage* msg)
{
	if (!connect(url))
	{
		return false;
	}

	if (msg)
	{
		SocketSerializer s(_s.get());
		s << msg << my_endl();
		/*
		printf("------SEND-----\n%s %s\n", msg->GetUsername().c_str(), msg->GetMsg().c_str());
		printf("data format %s, ", toString(msg->GetFormat()).c_str());
		printf("data size %zd\n", msg->GetMsg().size());
		printf("--------------\n\n");
		*/
		return true;
	}
	return false;
}

std::shared_ptr<IMessagePack> Client::recv()
{
	if (!_s)
	{
		printf("Socket disconnected\n");
		return nullptr;
	}

	SocketDeserializer d(_s.get());	
	IMessage* recv_msgs = nullptr;
	try
	{
		d >> recv_msgs;
	}
	catch (const ConnResetException& ex)
	{
		printExc(ex);
		disconnect();
		Notify(ConnResetEvent(0));
		return nullptr;
	}
	catch (const std::exception&)
	{
		return nullptr;
	}
	assert(recv_msgs);		
	printf("-----RECV-----\n");
    qDebug() <<
	printf("--------------\n\n");
	Notify(MessagesUpdateEvent(0, *recv_msgs));
	return std::shared_ptr<IMessagePack>(static_cast<IMessagePack*>(recv_msgs));
}

void Client::AddObserver(IObserver* o)
{
	_observers.push_back(o);
}

void Client::Notify(const Event& e)
{
	for (auto&& o : _observers)
	{
		o->Update(e);
	}
}
