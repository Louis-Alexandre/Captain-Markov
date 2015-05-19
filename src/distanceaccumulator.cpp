#include "distanceaccumulator.h"

#include "NodeFinding.h"
#include "Entity/Entity.h"

DistanceAccumulator::DistanceAccumulator(std::shared_ptr<Entity> _target, std::shared_ptr<NodeFinding> _nodeFinding) : nodeFinding{_nodeFinding}, target{_target} {}

void DistanceAccumulator::trigger()
{
	distances.emplace_back(nodeFinding->getDistance(target->getPosition()));
}

std::vector<double> DistanceAccumulator::getDistances() const
{
	return distances;
}

void DistanceAccumulator::reset()
{
	distances.clear();
}
