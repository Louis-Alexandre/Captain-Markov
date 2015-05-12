#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class ListeNode;
class Node;

class NodeFinding
{
public:
	NodeFinding(std::shared_ptr<ListeNode> _listeNode);
	void initiateNodeFinding(sf::Vector2i position);
	void doNodeFinding(std::shared_ptr<Node> node);
	sf::Vector2i findBestMove(sf::Vector2i position);
	
private:
	std::shared_ptr<ListeNode> listeNode;
};


