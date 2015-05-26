#include "mappositiontile.h"

#include "Tile.h"
#include "Map.h"

#include <algorithm>

using namespace std;

MapPositionTile::MapPositionTile(shared_ptr<Map> _map) : map{_map} {}

sf::Vector2i MapPositionTile::getPosition(int arg) const
{
	if (arg < mappedTiles.size()) {
		return mappedTiles[arg]->getPosition();
	} else {
		return {};
	}
}

void MapPositionTile::makeMap()
{
	mappedTiles.clear();
	for (auto tile : map->getTiles()) {
		if (tile->getTileType()->isWalkable()) {
			mappedTiles.push_back(tile);
		}
	}
}

int MapPositionTile::getArg(shared_ptr<Tile> tile) const
{
	auto it = find(mappedTiles.begin(), mappedTiles.end(), tile);
	
	if (it != mappedTiles.end()) {
		return distance(mappedTiles.begin(), it);
	}
	
	return 0;
}
