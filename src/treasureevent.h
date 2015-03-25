#pragma once

#include "event.h"

#include <SFML/System.hpp>
#include <memory>

class TileType;
class Map;
class Entity;

class TreasureEvent : public Event
{
public:
	TreasureEvent();
    void trigger() override;
	
	void setSubject(std::shared_ptr<Entity> subject);
	void setMap(std::weak_ptr<Map> map);
	void setTreasureType(std::shared_ptr<TileType> type);
	void setTreasureCheckedType(std::shared_ptr<TileType> type);
	
	std::shared_ptr<Entity> getSubject() const;
	std::shared_ptr<Map> getMap() const;
	std::shared_ptr<TileType> getTreasureType() const;
	std::shared_ptr<TileType> getTreasureCheckedType() const;
	
private:
	std::shared_ptr<Entity> _subject;
	std::shared_ptr<TileType> _treasureType;
	std::shared_ptr<TileType> _treasureCheckedType;
	std::weak_ptr<Map> _mapRef;
	sf::Vector2i _lastPosition;
	int _turnCount;
};
