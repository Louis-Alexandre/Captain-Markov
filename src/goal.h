#pragma once

#include "event.h"

#include <memory>
#include <functional>

class Goal : public Event
{
public:
	virtual bool check() = 0;
	void trigger() override final;
	void setCallback(std::function<void()> callback);
	
private:
	std::function<void()> _callback;
	
};
