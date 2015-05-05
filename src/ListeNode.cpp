#include "ListeNode.h"
#include "Map.h"

using namespace std;
ListeNode::ListeNode(shared_ptr<Map> map)
{
	this->map = map;
}


void ListeNode::makeListNode()
{
	for(auto tile: map->getTiles()){
		if (tile->getTileType()->isWalkable()){
			auto node = make_shared<Node>();
			listNode[tile] = node;
			
			auto south = map->getTileAtPosition(tile->getPosition() + sf::Vector2i{0, 1});
			auto north = map->getTileAtPosition(tile->getPosition() + sf::Vector2i{0, -1});
			auto east = map->getTileAtPosition(tile->getPosition() + sf::Vector2i{1, 0});
			auto west = map->getTileAtPosition(tile->getPosition() + sf::Vector2i{-1, 0});
			
			auto southNode = listNode[south];
			auto northNode = listNode[north];
			auto eastNode = listNode[east];
			auto westNode = listNode[west];
			
			if (south->getTileType()->isWalkable() && southNode) {
				node->addConnectedNode(southNode);
			}
			if (north->getTileType()->isWalkable() && northNode) {
				node->addConnectedNode(northNode);
			}
			if (east->getTileType()->isWalkable() && eastNode) {
				node->addConnectedNode(eastNode);
			}
			if (west->getTileType()->isWalkable() && westNode) {
				node->addConnectedNode(westNode);
			}
		}
	}
}

map<shared_ptr<Tile>, std::shared_ptr<Node>> ListeNode::getListNode()
{
	return listNode;
}

