#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class Tile;
class Node;
class Map;

class nodeFinding
{
public:
	void initiateNodeFinding(sf::Vector2i position);
	void setConnectedNodes(std::shared_ptr<Node>);
	void markNode(std::shared_ptr<Node>);
	void doNodeFinding(std::shared_ptr<Node> node);
	
private:
	std::weak_ptr<Map> mapRef;
	std::map<std::shared_ptr<Tile>, std::shared_ptr<Node>> listeNode;
	
	
};


