#pragma once

#include <map>
#include <memory>

class TileType;
class Tile;

class Node
{
public:
	void setDistance(int distance);
	int getDistance();
	void setDistanceProbable(double distanceProbable);
	double getDistanceProbable();
	bool isMarquer();
	bool isGoal();
private:
	int distance = 0;
	double distanceProbable = 0;
	bool marquer = false;
	bool goal = false;
};


