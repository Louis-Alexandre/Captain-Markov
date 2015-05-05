#include "TileType.h"

bool TileType::isWalkable() const
{
	return walkable;
}
void TileType::setWalkable(bool walkable)
{
	this-> walkable = walkable;
}

std::shared_ptr<const sf::Texture> TileType::getTexture() const
{
	return texture;
}

void TileType::setTexture(std::shared_ptr<sf::Texture> _testure)
{
	texture = _testure;
}
