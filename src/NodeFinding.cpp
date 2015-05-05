#include "NodeFinding.h"
#include "Tile.h"
#include "Node.h"
#include "ListeNode.h"

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
			}
		
		}
		doNodeFinding(goal);
}

void NodeFinding::doNodeFinding(shared_ptr<Node> node)
{
	for (auto connectedNode : node->getConnectedNodes()){
		if(connectedNode->getDistance() > node->getDistance()){
			connectedNode->setDistance(node->getDistance()+1);
		}
		
		if (!connectedNode->isMarquer()) {
			connectedNode->isMarquer();
			doNodeFinding(connectedNode);
		}
	}
}
