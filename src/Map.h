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
	Map(std::string level);
	void generateMap();
	void generateTileset();
	int getWindowsWidth();
	void setWindowsWidth(int windowsWidth);
	int getWindowsHeight();
	void setWindowsHeight(int windowsHeight);

	std::vector<std::shared_ptr<Tile>> getTiles();
	std::shared_ptr<Tile> getTileAtPosition(sf::Vector2i position);
	
private:
	std::vector<std::shared_ptr<Tile>> tiles;
	std::vector<std::shared_ptr<TileType>> tileSet;
	int windowsWidth;
	int windowsHeight;
	
};
