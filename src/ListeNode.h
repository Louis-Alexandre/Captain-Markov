#pragma once

#include <map>
#include <memory>

class TileType;
class Tile;
class Node;

class ListeNode
{
public:
	void setListNode();
	std::map<std::shared_ptr<Tile>, Node> getListNode();
	
private:
	std::map<std::shared_ptr<Tile>, Node> listNode;
};


