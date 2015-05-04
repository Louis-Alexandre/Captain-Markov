
#include "Node.h"

int Node::getDistance()
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

double Node::getDistanceProbable()
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

void Node::addConnectedNode(std::shared_ptr<Node> node)
{
	connectedNodes.emplace(node);
}

void Node::removeConnectedNode(std::shared_ptr<Node> node)
{
	connectedNodes.erase(node);
}


bool Node::isGoal()
{
	return goal;
}

bool Node::isMarquer()
{
	return marquer;
}

