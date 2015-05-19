#include "ListeNode.h"
#include "Map.h"

using namespace std;
ListeNode::ListeNode(shared_ptr<Map> map) : map{map} {}


void ListeNode::makeListNode()
{
	int i = 0;
	for(auto tile: map->getTiles()){
		if (tile->getTileType()->isWalkable()){
			auto node = make_shared<Node>();
			listNode[tile] = node;
			
			auto south = map->getTileAtPosition(tile->getPosition() + sf::Vector2i{0, 1});
			auto north = map->getTileAtPosition(tile->getPosition() + sf::Vector2i{0, -1});
			auto east = map->getTileAtPosition(tile->getPosition() + sf::Vector2i{1, 0});
			auto west = map->getTileAtPosition(tile->getPosition() + sf::Vector2i{-1, 0});
			
			shared_ptr<Node> southNode;
			shared_ptr<Node> northNode;
			shared_ptr<Node> eastNode;
			shared_ptr<Node> westNode;
			
			auto itSouth = listNode.find(south);
			if (south && itSouth != listNode.end()) {
				southNode = listNode[south];
			}
			
			auto itNorth = listNode.find(north);
			if (north && itNorth != listNode.end()) {
				northNode = listNode[north];
			}
			
			auto itEast = listNode.find(east);
			if (east && itEast != listNode.end()) {
				eastNode = listNode[east];
			}
			
			auto itWest = listNode.find(west);
			if (west && itWest != listNode.end()) {
				westNode = listNode[west];
			}
			
			if (south && south->getTileType()->isWalkable() && southNode) {
				node->addConnectedNode(southNode);
				southNode->addConnectedNode(node);
				
			}
			if (north && north->getTileType()->isWalkable() && northNode) {
				node->addConnectedNode(northNode);
				northNode->addConnectedNode(node);
			}
			if (east && east->getTileType()->isWalkable() && eastNode) {
				node->addConnectedNode(eastNode);
				eastNode->addConnectedNode(node);
			}
			if (west && west->getTileType()->isWalkable() && westNode) {
				node->addConnectedNode(westNode);
				westNode->addConnectedNode(node);
			}
		}
	}
}

map<shared_ptr<Tile>, std::shared_ptr<Node>> ListeNode::getListNode()
{
	return listNode;
}

void ListeNode::assignProb(std::shared_ptr< PositionMatrix > positionMatrix)
{
	
}

