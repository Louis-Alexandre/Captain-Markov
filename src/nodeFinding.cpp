#include "nodeFinding.h"
#include "Tile.h"
#include "Node.h"

std::vector< std::shared_ptr< Tile > > nodeFinding::getConnectedNodes() const
{
	return connectedNodes;
}

void nodeFinding::initiateNodeFinding(sf::Vector2i position)
{
		for (auto node : listeNode) {
			node.second->setDistance(0);
			node.second->setDistanceProbable(0);
			node.second->setMarquer(false);
			node.second->setGoal(false);
			totalDistanceFromGoal = 0;
			if(node.first->getPosition().x == position.x && node.first->getPosition().y == position.y){
				node.second->setGoal(true);
				currentNode = node.second;
			}
		}
		startNodeFinding();
}

void nodeFinding::startNodeFinding()
{
	
}


void nodeFinding::markNode(std::shared_ptr< Tile >)
{

}

void nodeFinding::setConnectedNodes(std::shared_ptr< Tile >)
{

}

void nodeFinding::setDistanceFromGoal(connectedNodes)
{
		for(auto node : connectedNodes){
			
		}
}
