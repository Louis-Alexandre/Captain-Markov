#pragma once
#include <memory>
#include <SFML/System.hpp>
#include "event.h"

class PositionMatrix;
class NodeFinding;

class InitNodeFinding :public Event
{
public:
	InitNodeFinding(std::shared_ptr<PositionMatrix> _positionMatrix, std::shared_ptr<NodeFinding> _nodeFinding);
	void trigger() override;

private:
	std::shared_ptr<PositionMatrix> positionMatrix;
	std::shared_ptr<NodeFinding> nodeFinding;
};


