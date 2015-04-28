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
	void setMarquer(bool marquer);
	void setGoal(bool Goal);
	void setDepth(int depth);
	int getDepth();
	double getDistanceProbable();
	bool isMarquer();
	bool isGoal();
private:
	int distance = 0;
	int depth = 0;
	double distanceProbable = 0;
	bool marquer = false;
	bool goal = false;
};


