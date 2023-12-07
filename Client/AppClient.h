#pragma once

#include <QObject>
#include <vector>
#include <string>
#include <memory>

#include "../Observer/IObservable.h"
#include "helpers/SocketClient.h"
#include "../Message/AuthorizedMessage.h"
#include "../Message/IMessagePack.h"

// command-line Client app that can send messages to Server.
class Client : public QObject
{
    Q_OBJECT
public:
	Client() = default;
	virtual ~Client() = default;
	bool connect(std::string url);
	void disconnect();
	bool send(const std::string& url, const AuthorizedMessage* msg);
	std::shared_ptr<IMessagePack> recv();

signals:
    void notifySignal(QSharedPointer<Event> e);

private:
	friend class Viewer;

private:
	std::unique_ptr<SocketClient> _s;
	std::vector<IObserver*> _observers;
};
