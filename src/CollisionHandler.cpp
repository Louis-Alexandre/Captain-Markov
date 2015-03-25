#include "CollisionHandler.h"
#include <iostream>
using namespace std;

CollisionHandler::CollisionHandler()
{

}
bool CollisionHandler::checkCollision(sf::Vector2i position) const
{
	auto tile = map->getTileAtPosition(position);
	if (tile) {
		return tile->getTileType()->isWalkable();
	}
	
	return false;
}

shared_ptr<Map> CollisionHandler::getMap() const
{
	return map;
}

void CollisionHandler::setMap(shared_ptr<Map> map)
{
	this->map = map;
}
