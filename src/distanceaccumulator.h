#pragma once

#include "event.h"

#include <vector>
#include <memory>

class NodeFinding;
class Entity;

class DistanceAccumulator : public Event
{
public:
	DistanceAccumulator(std::shared_ptr<Entity> _target, std::shared_ptr<NodeFinding> _nodeFinding);
    void trigger() override;
	
	std::vector<double> getDistances() const;
	void reset();
	
private:
	std::shared_ptr<Entity> target;
	std::shared_ptr<NodeFinding> nodeFinding;
	std::vector<double> distances;
};
