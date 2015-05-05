#pragma once

#include "Node.h"
#include "Tile.h"

#include <map>
#include <memory>

class TileType;
class Tile;
class Map;

class ListeNode
{
public:
	ListeNode(std::shared_ptr<Map>);
	void makeListNode();
	std::map<std::shared_ptr<Tile>, std::shared_ptr<Node>> getListNode();
	
private:
	std::map<std::shared_ptr<Tile>, std::shared_ptr<Node>> listNode;
	std::shared_ptr<Map> map;
};


