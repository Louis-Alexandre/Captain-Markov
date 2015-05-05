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
		vector<double> turn;
		for (auto tile : map->getTiles()) {
			if (tile->getTileType()->isWalkable()) {
				sf::Vector2i distance = tile->getPosition() - subject->getPosition();
				bool seen = seesPlayer();
				turn.push_back(
					((abs(distance.x) > 1 || abs(distance.y) > 1) && !seen) || (seen && observe->getNextPosition() == tile->getPosition())
				);
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

vector< vector< double > > Observation::getObservations() const
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

matrix< double > Observation::getMatrix() const
{
	auto result = getObservations();
	
	matrix<double> matResult{result.size(), result[0].size()};
	
	for (int n = 0 ; n<result.size() ; n++) {
		for (int m = 0 ; m<result[0].size() ; m++) {
			matResult(n, m) = result[n][m];
		}
	}
	
	return matResult;
}

void Observation::reset()
{
	observations.clear();
}

bool Observation::seesPlayer() const
{
	sf::Vector2i distance = observe->getNextPosition() - subject->getPosition();
	return abs(distance.x) <= 1 && abs(distance.y) <= 1;
}


void Observation::replaceLast(vector<double> observation)
{
	observations[observations.size() - 1] = move(observation);
}

void Observation::setObserve(shared_ptr< Entity > observe)
{
	this->observe = observe;
}
