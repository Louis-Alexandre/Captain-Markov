#include "TileType.h"

void TileType::setColor(sf::Color color)
{
	this->color = color;
}
sf::Color TileType::getColor() const
{
	return color;
}
bool TileType::isWalkable() const
{
	return walkable;
}
void TileType::setWalkable(bool walkable)
{
	this-> walkable = walkable;
}

