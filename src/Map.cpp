#include "Map.h"

using namespace std;

Map::Map()
{

}

void Map::generateMap()
{
	std::vector<int> map {
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1,
		1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1,
		2, 0, 0, 1, 1, 0, 1, 1, 0, 0, 2,
		1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1
	};

	int width = 11;
	int height = 7;
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
	tileMur->setColor(sf::Color::Green);
	tileDefault->setColor(sf::Color::Black);
	tileGoal->setColor(sf::Color::Yellow);
	tileMur->setWalkable(false);
	tileDefault->setWalkable(true);
	tileGoal->setWalkable(true);
	tileSet.push_back(tileDefault);
	tileSet.push_back(tileMur);
	tileSet.push_back(tileGoal);

}

int Map::getWindowsHeight()
{
	return windowsHeight;
}

void Map::setWindowsHeight(int windowsHeight)
{
	this->windowsHeight = windowsHeight;
}

int Map::getWindowsWidth()
{
	return windowsWidth;
}

void Map::setWindowsWidth(int windowsWidth)
{
	this->windowsWidth = windowsWidth;
}

vector< shared_ptr< Tile > > Map::getTiles()
{
	return tiles;
}

shared_ptr< Tile >  Map::getTileAtPosition(sf::Vector2i position)
{
	for (shared_ptr< Tile > i : this->getTiles()) {
		if (i->getPosition().x == position.x && i->getPosition().y == position.y) {
			return i;
		}
	}
	return nullptr;
}











