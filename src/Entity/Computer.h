#pragma once
#include "Entity.h"
#include "../Tile.h"
#include "../Pathfinding.h"
#include <memory>

class Pathfinding;

class Computer : public Entity
{
public:
	Computer();
	void changeTileGoal(std::shared_ptr<Tile> newGoal);
	void generatePositionProbable();
	void moveToNextTile(std::vector<std::shared_ptr<Tile>> closeList);
	void startPathFinding();

private:
	std::shared_ptr<Tile> tileGoal;
	std::vector<int> positionProbable;
	std::shared_ptr<Pathfinding> pathfinding;
};
