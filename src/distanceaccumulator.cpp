#include "distanceaccumulator.h"

#include "NodeFinding.h"
#include "Entity/Entity.h"
#include "observation.h"

using namespace std;

DistanceAccumulator::DistanceAccumulator(shared_ptr<Entity> _target, shared_ptr<NodeFinding> _nodeFinding, shared_ptr<Observation> _observation) :
	nodeFinding{_nodeFinding},
	target{_target},
	observation{_observation} {}

void DistanceAccumulator::trigger()
{
	if (!observation->seesPlayer()) {
		distances.emplace_back(nodeFinding->getDistance(target->getPosition()));
	}
}

vector<double> DistanceAccumulator::getDistances() const
{
	return distances;
}

void DistanceAccumulator::reset()
{
	distances.clear();
}
