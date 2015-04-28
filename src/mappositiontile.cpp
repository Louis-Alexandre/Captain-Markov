#include "mappositiontile.h"

#include "Tile.h"
#include "Map.h"

using namespace std;

MapPositionTile::MapPositionTile(shared_ptr<Map> map)
{
	for (auto tile : map->getTiles()) {
		if (tile->getTileType()->isWalkable()) {
			mappedTiles.push_back(tile);
		}
	}
}

sf::Vector2i MapPositionTile::getPosition(int arg)
{
	if (arg < mappedTiles.size()) {
		return mappedTiles[arg]->getPosition();
	} else {
		return {};
	}
}
