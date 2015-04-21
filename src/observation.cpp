#include "observation.h"

#include "Map.h"
#include "Entity/Entity.h"
#include "Tile.h"
#include "TileType.h"

using namespace std;
using boost::numeric::ublas::matrix;

void Observation::trigger()
{
	if (mapRef.lock()) {
		auto map = mapRef.lock();
		vector<int> turn;
		for (auto tile : map->getTiles()) {
			if (tile->getTileType()->isWalkable()) {
				auto distance = tile->getPosition() - subject->getNextPosition();
				turn.emplace_back(abs(distance.x) > 1 || abs(distance.y) > 1);
			}
		}
		observations.emplace_back(turn);
	}
}

shared_ptr<Map> Observation::getMap() const
{
	return mapRef.lock();
}

void Observation::setMap(weak_ptr<Map> map)
{
	mapRef = map;
}

vector<vector<int>> Observation::getObservations() const
{
	return observations;
}

shared_ptr<Entity> Observation::getSubject() const
{
	return subject;
}

void Observation::setSubject(shared_ptr<Entity> subject)
{
	this->subject = subject;
}

boost::numeric::ublas::matrix<int> Observation::getMatrix() const
{
	auto result = getVecVec();
	
	matrix<double> matResult{result.size(), result[0].size()};
	
	for (int n = 0 ; n<result.size() ; n++) {
		for (int m = 0 ; m<result[0].size() ; m++) {
			matResult(n, m) = result[n][m];
		}
	}
	
	return matResult;
}

vector<vector<int>> Observation::getVecVec() const
{
	return getObservations();
}
