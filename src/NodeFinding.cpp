#include "NodeFinding.h"
#include "Tile.h"
#include "Node.h"
#include "ListeNode.h"

#include "iostream"

using namespace std;

NodeFinding::NodeFinding(shared_ptr<ListeNode> _listeNode) : listeNode{_listeNode}
{
	
}


void NodeFinding::initiateNodeFinding(shared_ptr<PositionMatrix> position)
{
	shared_ptr<Node> goal;
	for (auto node : listeNode->getListNode()) {
		node.second->reset();
		position->getProbability(node.first);
		if(node.first->getPosition() == position->getPosition()){
			goal = node.second;
			goal->setDistance(0);
		}
	}
	if (goal) {
		doNodeFinding(goal);
	}
}
void NodeFinding::doNodeFinding(shared_ptr<Node> node)
{
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
		if(node.first->getPosition() == position) {
			for (auto connectedNode : node.second->getConnectedNodes()) {
				if (
					(!nextPosition || connectedNode->getDistance() < nextPosition->getDistance()) ||
					(connectedNode->getDistance() == nextPosition->getDistance() &&  nextPosition->surroundingProbability() < connectedNode->surroundingProbability())
				) {
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







