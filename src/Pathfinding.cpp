#include "Pathfinding.h"
#include "Map.h"
#include "Tile.h"
#include <iterator>

#include "Map.h"
using namespace std;
Pathfinding::Pathfinding()
{

}

int Pathfinding::getCostG(shared_ptr<Tile> tile1, shared_ptr<Tile> tile2) const
{nst
{
	return costG + costH;>getPosition() - tile1->getPosition();
	return sqrt((relative.x*relative.x)+(relative.y*relative.y));
}


shared_ptr< Tile > Pathfinding::getGoal()
{
	return Goal;
}

void Pathfinding::setGoal(shared_ptr< Tile > goal)
{
	this->Goal = goal;
}


double Pathfinding::calculateSumOfGH(int costG, double costH) co
}

void Pathfinding::addToCloseList(shared_ptr<Tile> tile)
{
	closedList.push_back(tile);
}

void Pathfinding::addToOpenList(shared_ptr<Tile> tile)
{
	openList.push_back(tile);
}

void Pathfinding::deleteCloseList()
{
	closedList.clear();
}

void Pathfinding::deleteOpenList()
{
	openList.clear();
}

vector< shared_ptr< Tile > > Pathfinding::getClosedList()
{
	return closedList;
}

bool Pathfinding::AddBestWay()
{
	double sumOfGH = 0;
	shared_ptr<Tile> tileFinal;
	for (auto i : openList) {
		if (tileIsGoal(i)) {
			tileFinal = i;
			return true;
		} else {
			if (calculateSumOfGH(getCostG(getGoal(), i), i->getHeuristic()) <= sumOfGH) {
				tileFinal = i;
				sumOfGH = calculateSumOfGH(getCostG(getGoal(), i), i->getHeuristic());
			}
		}
	}
	addToCloseList(tileFinal);
	return false;
}

bool Pathfinding::tileIsGoal(shared_ptr<Tile> Tile)
{
	return getGoal() == Tile;
}

void Pathfinding::initiateOpenList(shared_ptr<Tile> startingPoint)
{
	if (!mapRef.expired()) {
		auto map = mapRef.lock();
		for (auto tile : map->getTiles()) {
			if (isNearby(tile , startingPoint->getPosition())) {
				addToOpenList(tile);
			}
		}
	}
}



bool Pathfinding::isNearby(shared_ptr< Tile > tile, sf::Vector2i position) const
{
	return abs(position.x - tile->getPosition().x) <= 1  && abs(position.y - tile->getPosition().y) <= 1;
}

void Pathfinding::StartPathfinding(sf::Vector2i position, shared_ptr< Tile > goalTile)
{
	if(!mapRef.expired()){
		auto map = mapRef.lock();
	deleteCloseList();
	deleteOpenList();
	initiateOpenList(map->getTileAtPosition(position));
	while(AddBestWay()){
		deleteOpenList();
		initiateOpenList(*closedList.rbegin());
	}//faut mettre le tile goal et utiliser la methode tileIsGoal.
	}
}



