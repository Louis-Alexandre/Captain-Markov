#pragma once

#include "goal.h"

class Map;
class TileType;

class TreasureFound : public Goal
{
public:
	TreasureFound();
    bool check() override;
	void setTreasureType(std::shared_ptr<TileType> treasureType);
	std::shared_ptr<TileType> getTreasureType() const;
	
	void setCountToWin(int countToWin);
	int getCountToWin() const;
	
	void setMap(std::weak_ptr<Map> map);
	std::shared_ptr<Map> getMap() const;
	
private:
	std::weak_ptr<Map> _mapRef;
	std::shared_ptr<TileType> _treasureType;
	int _countToWin;
};
