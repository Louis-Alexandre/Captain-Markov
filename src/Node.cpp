#include "Node.h"

#include <limits>

using namespace std;

int Node::getDistance() const
{
	return distance;
}

void Node::setDistance(int distance)
{
 this->distance = distance;
}

void Node::setDistanceProbable(double distanceProbable)
{
	this->distanceProbable = distanceProbable;
}

double Node::getDistanceProbable() const
{
	return distanceProbable;
}

void Node::setGoal(bool Goal)
{
	this->goal = goal;
}

void Node::setMarquer(bool marquer)
{
	this->marquer = marquer;
}

void Node::addConnectedNode(shared_ptr<Node> node)
{
	connectedNodes.emplace(node);
}

void Node::removeConnectedNode(shared_ptr<Node> node)
{
	connectedNodes.erase(node);
}

set<shared_ptr<Node>> Node::getConnectedNodes() const
{
	set<shared_ptr<Node>> nodes;
	
	for (auto node : connectedNodes) {
		if (!node.expired()) {
			nodes.emplace(node.lock());
		}
	}
	return nodes;
}

bool Node::isGoal() const
{
	return goal;
}

bool Node::isMarquer() const
{
	return marquer;
}

void Node::reset()
{
	marquer = false;
	goal = false;
	distance = numeric_limits<int>::max();
	distanceProbable = 0;
}
