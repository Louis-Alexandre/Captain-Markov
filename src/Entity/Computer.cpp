#include "Computer.h"

Computer::Computer()
{
	
}

void Computer::changeTileGoal(std::shared_ptr< Tile > newGoal)
{

}


void Computer::generatePositionProbable()
{

}

void Computer::moveToNextTile(std::vector<std::shared_ptr<Tile>> closeList)
{
}

void Computer::startPathFinding()
{
	pathfinding->StartPathfinding(this->getPosition(),this->tileGoal);
	
}

