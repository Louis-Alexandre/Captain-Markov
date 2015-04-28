#include "nodeFinding.h"

std::vector< std::shared_ptr< Tile > > nodeFinding::getConnectedNode() const
{
	return connectedNode;
}

void nodeFinding::initiateNodeFinding()
{
	if (!mapRef.expired()) {
		auto map = mapRef.lock();
		for (auto tile : map->getTiles()) {
			
		}
	}
}

void nodeFinding::markNode(std::shared_ptr< Tile >)
{

}

void nodeFinding::setConnectedNode(std::shared_ptr< Tile >)
{

}

void nodeFinding::setDistanceFromGoal(connectedNode)
{
	
}
