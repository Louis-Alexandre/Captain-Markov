#include "ListeNode.h"
#include "Map.h"

using namespace std;

ListeNode::ListeNode(shared_ptr<Map> map)
{
	this->map = map;
}


void ListeNode::setListNode()
{
	for(auto tile: map->getTiles()){
		if (tile->getTileType()->isWalkable()){
			listNode[tile] = make_shared<Node>();
		}
		
	}
}

map<shared_ptr<Tile>, std::shared_ptr<Node>> ListeNode::getListNode()
{
	return listNode;
}

