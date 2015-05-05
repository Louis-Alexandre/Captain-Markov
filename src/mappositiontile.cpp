#include "mappositiontile.h"

#include "Tile.h"
#include "Map.h"

using namespace std;

MapPositionTile::MapPositionTile(shared_ptr<Map> _map) : map{_map} {}

sf::Vector2i MapPositionTile::getPosition(int arg)
{
	if (mappedTiles.size() == 0) {
		makeMap();
	}

	if (arg < mappedTiles.size()) {
		return mappedTiles[arg]->getPosition();
	} else {
		return {};
	}
}

void MapPositionTile::makeMap()
{
	for (auto tile : map->getTiles()) {
		if (tile->getTileType()->isWalkable()) {
			mappedTiles.push_back(tile);
		}
	}
}
