#include "NodeFinding.h"
#include "Tile.h"
#include "Node.h"
#include "ListeNode.h"

#include "iostream"

using namespace std;

NodeFinding::NodeFinding(shared_ptr<ListeNode> _listeNode) : listeNode{_listeNode}
{
	
}


void NodeFinding::initiateNodeFinding(sf::Vector2i position)
{
	shared_ptr<Node> goal;
		for (auto node : listeNode->getListNode()) {
			node.second->reset();
			if(node.first->getPosition() == position){
				node.second->setGoal(true);
				goal = node.second;
				goal->setDistance(0);
				goal->setMarquer(true);
			}
		}
		doNodeFinding(goal);
}
void NodeFinding::doNodeFinding(shared_ptr<Node> node)
{
	node->setMarquer(true);
	for (auto connectedNode : node->getConnectedNodes()){
		if (connectedNode) {
			if(connectedNode->getDistance() > node->getDistance()+1){
				connectedNode->setDistance(node->getDistance()+1);
				doNodeFinding(connectedNode);
			}
		}
	}
}

int NodeFinding::getDistance(sf::Vector2i position)
{
	for (auto node : listeNode->getListNode()) {
		if (node.first->getPosition() == position) {
			return node.second->getDistance();
		}
	}
}

sf::Vector2i NodeFinding::findBestMove(sf::Vector2i position)
{
	shared_ptr<Node> currentPosition;
	shared_ptr<Node> nextPosition;
	
	for (auto node : listeNode->getListNode()) {
		if(node.first->getPosition() == position){
			for (auto connectedNode : node.second->getConnectedNodes()){
				if (!nextPosition || connectedNode->getDistance() < nextPosition->getDistance()){
					nextPosition = connectedNode;
				}
			}
		}
	}
	
	for (auto node : listeNode->getListNode()) {
		if(node.second == nextPosition){
			return node.first->getPosition();
		}
	}
	
}






