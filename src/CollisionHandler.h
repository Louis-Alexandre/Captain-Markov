#pragma once
#include "Map.h"
#include "Tile.h"
#include <SFML/Window.hpp>
class CollisionHandler
{
public:
	CollisionHandler();
	bool checkCollision(sf::Vector2i position) const;
	
	void setMap(std::shared_ptr<Map> map);
	std::shared_ptr<Map> getMap() const;

private:
	std::shared_ptr<Map> map;
};
