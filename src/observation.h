#pragma once

#include "event.h"
#include "matrixprovider.h"

#include <memory>
#include <vector>
#include <set>

class Map;
class Entity;
class TileType;
class Tile;

class Observation : public Event, public MatrixProvider
{
public:
	std::shared_ptr<Map> getMap() const;
	void setMap(std::weak_ptr<Map> map);
	
    void trigger() override;
	
	void setSubject(std::shared_ptr<Entity> subject);
	std::shared_ptr<Entity> getSubject() const;
	
	std::vector<std::vector<double>> getObservations() const;
	
    boost::numeric::ublas::matrix<double> getMatrix() const override;
	
	void replaceLast(std::vector<double> observation);
	void reset();
	
	void setObserve(std::shared_ptr<Entity> observe);
	void addEyeType(std::shared_ptr<TileType> type);
	
private:
	bool seesPlayer() const;
	bool isEyeTile(std::shared_ptr<Tile> tile) const;
	std::set<std::shared_ptr<TileType>> eyeTypes;
	std::vector<std::vector<double>> observations;
	std::shared_ptr<Entity> observe;
	std::shared_ptr<Entity> subject;
	std::weak_ptr<Map> mapRef;
};
