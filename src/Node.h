#pragma once

#include <set>
#include <memory>

class TileType;
class Tile;

class Node
{
public:
	void setDistance(int distance);
	int getDistance() const;
	void setDistanceProbable(double distanceProbable);
	void addConnectedNode( std::shared_ptr< Node > node );
	void removeConnectedNode( std::shared_ptr< Node > node );
	std::set<std::shared_ptr<Node>> getConnectedNodes() const;
	double getDistanceProbable() const;
	
	void reset();
	
private:
	int distance = 0;
	double distanceProbable = 0;
	std::set<std::weak_ptr<Node>, std::owner_less<std::weak_ptr<Node>>> connectedNodes;
};


