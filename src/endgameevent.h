#pragma once

#include "event.h"

struct EndGameEvent : public Event
{
public:
	EndGameEvent();
	void patate() const;
	
private:
	int _status;
};
