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

void Node::reset()
{
	distance = numeric_limits<int>::max();
	weight = 0;
}

double Node::getWeight() const
{
	return weight;
}

void Node::setWeight(double weight)
{
	this->weight = weight;
}

double Node::surroundingProbability() const
{
	double totalWeight = weight;
	for (auto node : connectedNodes) {
		totalWeight += node.expired() ? 0 : node.lock()->getWeight();
	}
	return totalWeight;
}
