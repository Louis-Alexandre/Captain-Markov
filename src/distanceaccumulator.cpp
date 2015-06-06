#include "distanceaccumulator.h"

#include "NodeFinding.h"
#include "Entity/Entity.h"
#include "observation.h"

DistanceAccumulator::DistanceAccumulator(std::shared_ptr<Entity> _target, std::shared_ptr<NodeFinding> _nodeFinding, std::shared_ptr<Observation> _observation) :
	nodeFinding{_nodeFinding},
	target{_target},
	observation{_observation} {}

void DistanceAccumulator::trigger()
{
	if (!observation->seesPlayer()) {
		distances.emplace_back(nodeFinding->getDistance(target->getPosition()));
	}
}

std::vector<double> DistanceAccumulator::getDistances() const
{
	return distances;
}

void DistanceAccumulator::reset()
{
	distances.clear();
}
