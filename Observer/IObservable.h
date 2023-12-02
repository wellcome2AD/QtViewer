#pragma once

#include <memory>

class IObserver;
class Event;

class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void AddObserver(IObserver* o) = 0;
	virtual void Notify(const Event& e) = 0;
};
