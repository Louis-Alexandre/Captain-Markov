#include "treasurefound.h"

#include "Map.h"

using namespace std;

TreasureFound::TreasureFound() : _countToWin(1)
{

}

bool TreasureFound::check()
{
	int treasureCount = 0;
	if (!_mapRef.expired()) {
		auto map = _mapRef.lock();
		for (auto tile : map->getTiles()) {
			if (tile->getTileType() == _treasureType) {
				treasureCount++;
				if (treasureCount == _countToWin) {
					return true;
				}
			}
		}
	}
	
	return false;
}

int TreasureFound::getCountToWin() const
{
	return _countToWin;
}

shared_ptr<Map> TreasureFound::getMap() const
{
	return _mapRef.expired() ? nullptr:_mapRef.lock();
}

shared_ptr<TileType> TreasureFound::getTreasureType() const
{
	return _treasureType;
}

void TreasureFound::setCountToWin(int countToWin)
{
	_countToWin = countToWin;
}

void TreasureFound::setMap(weak_ptr<Map> map)
{
	_mapRef = map;
}

void TreasureFound::setTreasureType(shared_ptr<TileType> treasureType)
{
	_treasureType = treasureType;
}
