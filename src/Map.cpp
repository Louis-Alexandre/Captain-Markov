#include "Map.h"

using namespace std;

Map::Map()
{

}

void Map::generateMap()
{
	tiles.clear();
	std::vector<int> map {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
		1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 4, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 4, 1,
		1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 4, 0, 2,
		1, 0, 4, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0,
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
	
	auto texture1 = make_shared<sf::Texture>();
	auto texture2 = make_shared<sf::Texture>();
	auto texture3 = make_shared<sf::Texture>();
	auto texture4 = make_shared<sf::Texture>();
	auto texture5 = make_shared<sf::Texture>();
	texture1->loadFromFile("res/tileset.png", sf::IntRect{0, 0, 16, 16});
	texture2->loadFromFile("res/tileset.png", sf::IntRect{16, 0, 16, 16});
	texture3->loadFromFile("res/tileset.png", sf::IntRect{192, 0, 16, 16});
	texture4->loadFromFile("res/tileset.png", sf::IntRect{208, 0, 16, 16});
	texture5->loadFromFile("res/tileset.png", sf::IntRect{224, 0, 16, 16});
	auto tileMur = make_shared<TileType>();
	auto tileDefault = make_shared<TileType>();
	auto tileGoal = make_shared<TileType>();
	auto tileGoalChecked = make_shared<TileType>();
	auto tileParrot = make_shared<TileType>();
	tileDefault->setTexture(texture1);
	tileDefault->setWalkable(true);
	tileParrot->setTexture(texture5);
	tileParrot->setWalkable(true);
	tileMur->setTexture(texture2);
	tileMur->setWalkable(false);
	tileGoal->setTexture(texture3);
	tileGoal->setWalkable(true);
	tileGoalChecked->setTexture(texture4);
	tileGoalChecked->setWalkable(true);
	tileSet.push_back(tileDefault);
	tileSet.push_back(tileMur);
	tileSet.push_back(tileGoal);
	tileSet.push_back(tileGoalChecked);
	tileSet.push_back(tileParrot);

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
	for (auto i : this->getTiles()) {
		if (i->getPosition() == position) {
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
