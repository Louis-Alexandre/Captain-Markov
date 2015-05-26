#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class ListeNode;
class Node;
class PositionMatrix;

class NodeFinding
{
public:
	NodeFinding(std::shared_ptr<ListeNode> _listeNode);
	void initiateNodeFinding(std::shared_ptr<PositionMatrix> position);
	void doNodeFinding(std::shared_ptr<Node> node);
	sf::Vector2i findBestMove(sf::Vector2i position);
	int getDistance(sf::Vector2i position);
	
private:
	std::shared_ptr<ListeNode> listeNode;
};


