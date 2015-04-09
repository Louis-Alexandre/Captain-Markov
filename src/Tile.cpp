#include "Tile.h"

Tile::Tile()
{
	
}

sf::Vector2i Tile::getPosition() const
{
	return position;
}

void Tile::setPosition(sf::Vector2i position)
{
	this->position = position;
}

std::shared_ptr<TileType> Tile::getTileType() const
{
	return tileType;
}

void Tile::setTileType(std::shared_ptr<TileType> type)
{
	this->tileType = type;

}

int Tile::getTileHeight() const
{
	return tileHeight;
}

void Tile::setTileHeight(int tileHeight)
{
	this->tileHeight = tileHeight;
}

int Tile::getTileWidth() const
{
	return tileWidth;
}

void Tile::setTileWidth(int tileWidth)
{
	this->tileWidth = tileWidth;
}

double Tile::getHeuristic()
{
	return heuristic;
}

void Tile::setHeuristic(double probabiliter)
{

}

int Tile::getNodeDistance() const
{
	return nodeDistance;
}

void Tile::setNodeDistance(int nodeDistance)
{
	this->nodeDistance = nodeDistance;
}


