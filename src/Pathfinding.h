#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class Tile;
class Map;

class Pathfinding
{
public:
	Pathfinding();
	double calculateSumOfGH(int costG, double costH) const;
	void addToOpenList(std::shared_ptr<Tile> tile);
	void deleteOpenList();
	void deleteCloseList();
	void addToCloseList(std::shared_ptr<Tile> tile);
	std::vector<std::shared_ptr<Tile>> getClosedList();
	int getCostG(std::shared_ptr<Tile> tile1, std::shared_ptr<Tile> tile2) const;
	void setGoal(std::shared_ptr<Tile> goal);
	std::shared_ptr<Tile> getGoal();
	void initiateOpenList(std::shared_ptr<Tile> startingPoint);
	void StartPathfinding(sf::Vector2i position, std::shared_ptr<Tile> goalTile);
	bool AddBestWay();
	bool tileIsGoal(std::shared_ptr<Tile> Tile);
	std::vector<std::shared_ptr<Tile>> getNearbyTiles(sf::Vector2i position) const;
	bool isNearby(std::shared_ptr<Tile> tile, sf::Vector2i position) const;
private:
	std::vector<std::shared_ptr<Tile>> openList;
	std::vector<std::shared_ptr<Tile>> closedList;
	std::vector<std::shared_ptr<Tile>> possibleWay;
	std::shared_ptr<Tile> Goal;
	std::weak_ptr<Map> mapRef;
};



