#pragma once

#include <memory>

#include "Event.h"

class IObserver
{
public:
	virtual ~IObserver() = default;
	virtual void Update(const Event& e) = 0;
};
