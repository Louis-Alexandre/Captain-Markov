#pragma once

#include "event.h"

#include <memory>

class PositionMatrix;
class Entity;
class Observation;
class AppendMatrixProvider;
class Map;
class MapPositionTile;

class RPrinter : public Event
{
public:
	RPrinter(
		std::shared_ptr<PositionMatrix> _positionMatrix,
		std::shared_ptr<Entity> _player1,
		std::shared_ptr<Entity> _player2,
		std::shared_ptr<Observation> _obs,
		std::shared_ptr<AppendMatrixProvider> _mxp,
		std::shared_ptr<Map> _map,
		std::shared_ptr<MapPositionTile> _mpt
	);
	
	void trigger() override;
	
private:
	std::shared_ptr<PositionMatrix> positionMatrix;
	std::shared_ptr<Entity> player1;
	std::shared_ptr<Entity> player2;
	std::shared_ptr<Observation> obs;
	std::shared_ptr<AppendMatrixProvider> mxp;
	std::shared_ptr<Map> map;
	std::shared_ptr<MapPositionTile> mpt;
};
