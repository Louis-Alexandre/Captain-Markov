#include "Tile.h"

#include "mapinfo.h"
#include "TileType.h"

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

void Tile::draw(sf::RenderWindow& window, MapInfo* mapInfo)
{
	
	sf::RectangleShape tileRectangle(sf::Vector2f {static_cast<float>(mapInfo->getTileWidth()), static_cast<float>(mapInfo->getTileHeight())});
	if (!tileType->getTexture()) {
		tileRectangle.setFillColor(sf::Color::White);
	} else {
		tileRectangle.setTexture(tileType->getTexture().get());
	}
	tileRectangle.setPosition(position.x * mapInfo->getTileWidth(), position.y * mapInfo->getTileHeight());
	window.draw(tileRectangle);
}

int Tile::getNodeDistance() const
{
	return nodeDistance;
}

void Tile::setNodeDistance(int nodeDistance)
{
	this->nodeDistance = nodeDistance;
}


