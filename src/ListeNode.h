#pragma once

#include "Node.h"
#include "Tile.h"
#include "positionmatrix.h"

#include <map>
#include <memory>

class TileType;
class Tile;
class Map;
class MapPositionTile;

class ListeNode
{
public:
	ListeNode(std::shared_ptr<Map> map, std::shared_ptr<MapPositionTile> mpt);
	void makeListNode();
	void assignProb(std::shared_ptr<PositionMatrix> positionMatrix);
	std::map<std::shared_ptr<Tile>, std::shared_ptr<Node>> getListNode();
	
private:
	std::map<std::shared_ptr<Tile>, std::shared_ptr<Node>> listNode;
	std::shared_ptr<Map> map;
	std::shared_ptr<MapPositionTile> mpt;
};


