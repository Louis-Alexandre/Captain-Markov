#pragma once

#include <set>
#include <memory>

class TileType;
class Tile;

class Node
{
public:
	Node(int position);
	void setDistance(int distance);
	int getDistance() const;
	
	void addConnectedNode( std::shared_ptr< Node > node );
	void removeConnectedNode( std::shared_ptr< Node > node );
	std::set<std::shared_ptr<Node>> getConnectedNodes() const;
	
	void addVisibleNode( std::shared_ptr< Node > node );
	void removeVisibleNode( std::shared_ptr< Node > node );
	std::set<std::shared_ptr<Node>> getVisibleNodes() const;
	
	double getWeight() const;
	void setWeight(double weight);
	
	double surroundingProbability() const;
	
	void reset();
	int getPosition() const;
	void setPosition(int n);
private:
	int position = 0;
	int distance = 0;
	double weight = 0;
	std::set<std::weak_ptr<Node>, std::owner_less<std::weak_ptr<Node>>> connectedNodes;
	std::set<std::weak_ptr<Node>, std::owner_less<std::weak_ptr<Node>>> visibleNodes;
};


