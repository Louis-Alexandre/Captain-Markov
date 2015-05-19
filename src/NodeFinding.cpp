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
			if (node.second) {
				node.second->reset();
				if(node.first->getPosition() == position){
					node.second->setGoal(true);
					goal = node.second;
					goal->setDistance(0);
					goal->setMarquer(true);
				}
			}
		}
		doNodeFinding(goal);
}

void NodeFinding::doNodeFinding(shared_ptr<Node> node)
{
	for (auto connectedNode : node->getConnectedNodes()){
		if (connectedNode) {
			if(connectedNode->getDistance() > node->getDistance()){
				connectedNode->setDistance(node->getDistance()+1);
			}
			
			if (!connectedNode->isMarquer()) {
				connectedNode->setMarquer(true);
				doNodeFinding(connectedNode);
			}
		}
	}
}

sf::Vector2i NodeFinding::findBestMove(sf::Vector2i position)
{
	shared_ptr<Node> currentPosition;
	shared_ptr<Node> nextPosition;
	for (auto node : listeNode->getListNode()) {
		if (node.first) {
			if(node.first->getPosition() == position){
				if (node.second) {
					for (auto connectedNode : node.second->getConnectedNodes()){
						if (!nextPosition || connectedNode->getDistance() < nextPosition->getDistance()){
							nextPosition = connectedNode;
						}
					}
				}
			}
		}

	}
	cout << endl;
	for (auto node : listeNode->getListNode()) {
		if(node.second && node.first && node.second == nextPosition){
			return node.first->getPosition();
		}
	}
	
}






