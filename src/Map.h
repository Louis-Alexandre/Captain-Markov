#pragma once
#include "Tile.h"
#include "TileType.h"
#include <vector>
#include <memory>
#include <string>

class Map
{
public:
	Map();
	void generateMap();
	void generateTileset();
	
	uint getWidth();
	uint getHeight();
	void setWidth(uint width);
	void setHeight(uint height);
	
	uint getTileHeight();
	uint getTileWidth();
	
	std::vector<std::shared_ptr<Tile>> getTiles();
	std::vector<std::shared_ptr<TileType>> getTileSet();
	std::shared_ptr<Tile> getTileAtPosition(sf::Vector2i position);
	
private:
	std::vector<std::shared_ptr<Tile>> tiles;
	std::vector<std::shared_ptr<TileType>> tileSet;
	uint height;
	uint width;
};
