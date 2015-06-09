#include "ListeNode.h"
#include "Map.h"
#include "mappositiontile.h"

using namespace std;
ListeNode::ListeNode(shared_ptr<Map> map, shared_ptr<MapPositionTile> mpt) : map{map}, mpt{mpt} {}


void ListeNode::makeListNode()
{
	int i = 0;
	listNode.clear();
	for(auto tile: map->getTiles()){
		if (tile->getTileType()->isWalkable()){
			i++;
			auto node = make_shared<Node>(i);
			listNode[tile] = node;
			
			for (auto position : {sf::Vector2i{0, 1}, sf::Vector2i{0, -1}, sf::Vector2i{1, 0}, sf::Vector2i{-1, 0}}) {
				auto tileNode = map->getTileAtPosition(tile->getPosition() + position);
				setConnectedNode(node, tileNode);
			}
			
			for (auto position : {sf::Vector2i{1, 1}, sf::Vector2i{1, -1}, sf::Vector2i{-1, 1}, sf::Vector2i{-1, -1}}) {
				auto tileNode = map->getTileAtPosition(tile->getPosition() + position);
				setVisibleNode(node, tileNode);
			}
		}
	}
}

void ListeNode::setConnectedNode(shared_ptr<Node> node, shared_ptr<Tile> tile)
{
	shared_ptr<Node> connectedNode;
	auto itSouth = listNode.find(tile);
	if (tile && itSouth != listNode.end()) {
		connectedNode = listNode[tile];
	}
	
	if (tile && tile->getTileType()->isWalkable() && connectedNode) {
		node->addConnectedNode(connectedNode);
		connectedNode->addConnectedNode(node);
	}
}

void ListeNode::setVisibleNode(shared_ptr< Node > node, shared_ptr< Tile > tile)
{
	shared_ptr<Node> connectedNode;
	auto itSouth = listNode.find(tile);
	if (tile && itSouth != listNode.end()) {
		connectedNode = listNode[tile];
	}
	
	if (tile && tile->getTileType()->isWalkable() && connectedNode) {
		node->addVisibleNode(connectedNode);
		connectedNode->addVisibleNode(node);
	}
}

map<shared_ptr<Tile>, std::shared_ptr<Node>> ListeNode::getListNode()
{
	return listNode;
}

void ListeNode::assignProb(std::shared_ptr< PositionMatrix > positionMatrix)
{
	
}

