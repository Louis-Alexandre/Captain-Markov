#pragma once

#include <vector>
#include <memory>

class Tile;
class Node;
class nodeFinding
{
public:
	void initiateNodeFinding();
	std::vector<std::shared_ptr<Node>> getConnectedNode()const;
	void setConnectedNode(std::shared_ptr<Node>);
	void markNode(std::shared_ptr<Node>);
	void setDistanceFromGoal(std::vector<std::shared_ptr<Node>);
	
private:
	std::weak_ptr<Map> mapRef;
	std::map<std::shared_ptr<Tile>, std::shared_ptr<Node>> listeNode;
	std::vector<std::shared_ptr<Node>> connectedNode;
	std::shared_ptr<Node> currentNode;
	int totalDistanceFromGoal;
	
	
};


