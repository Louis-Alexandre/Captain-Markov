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
		listNode[tile] = {};
	}
}

map<shared_ptr<Tile>, Node> ListeNode::getListNode()
{
	return listNode;
}

