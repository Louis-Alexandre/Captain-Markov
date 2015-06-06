#include "treasureevent.h"

#include "Entity/Entity.h"
#include "Map.h"
#include "Tile.h"

TreasureEvent::TreasureEvent() : _turnCount{0}, _lastPosition{0, 0}
{
	
}

void TreasureEvent::trigger()
{
	if (!_mapRef.expired()) {
		auto map = _mapRef.lock();
		auto tile = map->getTileAtPosition(_subject->getPosition());
		if (tile->getTileType() == _treasureType && _lastPosition == _subject->getPosition()) {
			_turnCount++;
			if (_turnCount == 5) {
				tile->setTileType(_treasureCheckedType);
				_turnCount = 0;
				_lastPosition = {0, 0};
			}
		} else {
			_turnCount = 0;
		}
		_lastPosition = _subject->getPosition();
	}
}

std::shared_ptr<Map> TreasureEvent::getMap() const
{
	return !_mapRef.expired() ? _mapRef.lock() : nullptr;
}

std::shared_ptr< TileType > TreasureEvent::getTreasureCheckedType() const
{
	return _treasureCheckedType;
}

void TreasureEvent::setTreasureCheckedType(std::shared_ptr< TileType > type)
{
	_treasureCheckedType = type;
}

std::shared_ptr<Entity> TreasureEvent::getSubject() const
{
	return _subject;
}

std::shared_ptr<TileType> TreasureEvent::getTreasureType() const
{
	return _treasureType;
}

void TreasureEvent::setMap(std::weak_ptr<Map> map)
{
	_mapRef = map;
}

void TreasureEvent::setSubject(std::shared_ptr<Entity> subject)
{
	_subject = subject;
}

void TreasureEvent::setTreasureType(std::shared_ptr<TileType> type)
{
	_treasureType = type;
}
