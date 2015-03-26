#include "observation.h"

#include "Map.h"
#include "Entity/Entity.h"
#include "Tile.h"
#include "TileType.h"

using namespace std;

void Observation::trigger()
{
	if (mapRef.lock()) {
		auto map = mapRef.lock();
		vector<int> turn;
		for (auto tile : map->getTiles()) {
			if (tile->getTileType()->isWalkable()) {
				auto distance = tile->getPosition() - subject->getPosition();
				if (abs(distance.x) <= 1 && abs(distance.y) <= 1) {
					turn.push_back(0);
				} else {
					turn.push_back(1);
				}
			}
		}
		observations.push_back(turn);
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

