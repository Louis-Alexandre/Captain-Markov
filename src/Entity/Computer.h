#pragma once
#include "Entity.h"
#include "../Tile.h"
#include <memory>
class Computer : public Entity
{
public:
	Computer();
	void changeTileGoal(std::shared_ptr<Tile> newGoal);
	void generatePositionProbable();
	

private:
	std::shared_ptr<Tile> tileGoal;
	std::vector<int> positionProbable;
};
