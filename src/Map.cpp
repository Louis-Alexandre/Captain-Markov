#include "Map.h"

using namespace std;

Map::Map()
{

}

void Map::generateMap()
{
	std::vector<int> map {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
		1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1,
		1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0,
		2, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,
		0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1
	};

	int width = 16;
	int height = 8;
	sf::Vector2i position;

	for (int t : map) {
		auto tile = make_shared<Tile>();
		tile->setTileType(tileSet[t]);
		tile->setPosition(position);
		tiles.push_back(tile);
		position.x ++;
		if (position.x >= width) {
			position.x = 0;
			position.y ++;
		}


	}


}

void Map::generateTileset()
{
	auto tileMur = make_shared<TileType>();
	auto tileDefault = make_shared<TileType>();
	auto tileGoal = make_shared<TileType>();
	auto tileGoalChecked = make_shared<TileType>();
	tileDefault->setColor(sf::Color::Black);
	tileDefault->setWalkable(true);
	tileMur->setColor(sf::Color::Green);
	tileMur->setWalkable(false);
	tileGoal->setColor(sf::Color::Yellow);
	tileGoal->setWalkable(true);
	tileGoalChecked->setColor(sf::Color::Magenta);
	tileGoalChecked->setWalkable(true);
	tileSet.push_back(tileDefault);
	tileSet.push_back(tileMur);
	tileSet.push_back(tileGoal);
	tileSet.push_back(tileGoalChecked);

}

vector<shared_ptr<Tile>> Map::getTiles()
{
	return tiles;
}

vector<shared_ptr<TileType>> Map::getTileSet()
{
	return tileSet;
}

shared_ptr<Tile> Map::getTileAtPosition(sf::Vector2i position)
{
	for (shared_ptr< Tile > i : this->getTiles()) {
		if (i->getPosition().x == position.x && i->getPosition().y == position.y) {
			return i;
		}
	}
	return nullptr;
}

uint Map::getHeight()
{
	return height;
}

uint Map::getTileHeight()
{
	return width / 16;
}

uint Map::getTileWidth()
{
	return height / 8;
}

uint Map::getWidth()
{
	return width;
}

void Map::setHeight(uint height)
{
	this->height = height;
}

void Map::setWidth(uint width)
{
	this->width = width;
}
