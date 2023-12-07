#pragma once

#include <memory>
#include <Event.h>

//#include "Event.h"

class IObserver
{
public:
	virtual ~IObserver() = default;
	virtual void update(const Event& e) = 0;
};
