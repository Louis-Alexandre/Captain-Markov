#pragma once
#include <memory>
#include <SFML/System.hpp>
#include "event.h"

class PositionMatrix;
class NodeFinding;
class Entity;

class InitNodeFinding :public Event
{
public:
	InitNodeFinding(std::shared_ptr<PositionMatrix> _positionMatrix, std::shared_ptr<NodeFinding> _nodeFinding);
	void trigger() override;
	void setControlledEntity(std::shared_ptr<Entity> _controlledPlayer);

private:
	std::shared_ptr<PositionMatrix> positionMatrix;
	std::shared_ptr<NodeFinding> nodeFinding;
	std::shared_ptr<Entity> controlledPlayer;
};


