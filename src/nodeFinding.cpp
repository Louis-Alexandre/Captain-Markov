#include "nodeFinding.h"
#include "Tile.h"
#include "Node.h"

using namespace std;

void nodeFinding::initiateNodeFinding(sf::Vector2i position)
{
	shared_ptr<Node> goal;
		for (auto node : listeNode) {
			node.second->setDistance(0);
			node.second->setDistanceProbable(0);
			node.second->setMarquer(false);
			node.second->setGoal(false);
			if(node.first->getPosition().x == position.x && node.first->getPosition().y == position.y){
				node.second->setGoal(true);
				goal = node.second;
			}
		}
		doNodeFinding(goal);
}

void nodeFinding::doNodeFinding(shared_ptr<Node> node)
{
	
}


void nodeFinding::markNode(shared_ptr< Node >)
{

}
