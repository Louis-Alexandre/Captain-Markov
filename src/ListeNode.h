#pragma once

#include "Node.h"

#include <map>
#include <memory>

class TileType;
class Tile;
class Map;

class ListeNode
{
public:
	ListeNode(std::shared_ptr<Map>);
	void setListNode();
	std::map<std::shared_ptr<Tile>, Node> getListNode();
	
private:
	std::map<std::shared_ptr<Tile>, Node> listNode;
	std::shared_ptr<Map> map;
};


