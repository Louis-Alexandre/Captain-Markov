#pragma once

#include "event.h"
#include <memory>

class DistanceAccumulator;

class DistancePersistor : public Event
{
public:
	DistancePersistor(std::shared_ptr<DistanceAccumulator> _distanceAccumulator);
    void trigger() override;
	
private:
	std::shared_ptr<DistanceAccumulator> distanceAccumulator;
};
