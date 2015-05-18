#pragma once

#include "event.h"

#include <vector>
#include <memory>

class PositionMatrix;
class Entity;

class DistanceAccumulator : public Event
{
public:
	DistanceAccumulator(std::shared_ptr<PositionMatrix> _positionMatrix, std::shared_ptr<Entity> _target);
    void trigger() override;
	
	std::vector<double> getDistances() const;
	void reset();
	
private:
	std::shared_ptr<PositionMatrix> positionMatrix;
	std::shared_ptr<Entity> target;
	std::vector<double> distances;
};
