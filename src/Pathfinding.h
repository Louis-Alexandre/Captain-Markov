#pragma once
#include <vector>
#include <memory>
class Tile;

class Pathfinding
{
public:
	Pathfinding();
	int calculateSumOfGH(int costG, int costH);

private:
	int costG;
	int sumOfGH;
	std::vector<std::shared_ptr<Tile>> openList;
	std::vector<std::shared_ptr<Tile>> closedList;
};



