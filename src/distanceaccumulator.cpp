#include "distanceaccumulator.h"

#include "positionmatrix.h"
#include "Entity/Entity.h"

DistanceAccumulator::DistanceAccumulator(std::shared_ptr<PositionMatrix> _positionMatrix, std::shared_ptr<Entity> _target) : positionMatrix{_positionMatrix}, target{_target} {}

void DistanceAccumulator::trigger()
{
	auto relative = positionMatrix->getPosition() - target->getPosition();
	distances.emplace_back(sqrt(relative.x*relative.x + relative.y*relative.y));
}

std::vector<double> DistanceAccumulator::getDistances() const
{
	return distances;
}

void DistanceAccumulator::reset()
{
	distances.clear();
}
