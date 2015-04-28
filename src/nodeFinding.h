#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class Tile;
class Node;
class nodeFinding
{
public:
	void initiateNodeFinding(sf::Vector2i position);
	std::vector<std::shared_ptr<Node>> getConnectedNodes()const;
	void setConnectedNodes(std::shared_ptr<Node>);
	void markNode(std::shared_ptr<Node>);
	void setDistanceFromGoal(std::vector<std::shared_ptr<Node>);
	void startNodeFinding();
	
private:
	std::weak_ptr<Map> mapRef;
	std::map<std::shared_ptr<Tile>, std::shared_ptr<Node>> listeNode;
	std::vector<std::shared_ptr<Node>> connectedNodes;
	std::shared_ptr<Node> currentNode;
	int totalDistanceFromGoal;
	
	
};


