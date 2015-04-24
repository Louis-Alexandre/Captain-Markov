#pragma once

#include <functional>

#include "event.h"

class CallbackEvent : public Event
{
public:
	CallbackEvent(std::function<void()> callbackFunction);
    void trigger() override;
	
private:
	std::function<void()> callback;
};
