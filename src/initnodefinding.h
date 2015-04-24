#pragma once
#include <memory>
#include <SFML/System.hpp>
#include "event.h"

class PositionMatrix;
class Observation;
class InitNodeFinding :public Event
{
public:
	InitNodeFinding(std::shared_ptr<PositionMatrix>);
	void trigger() override;

private:
	std::shared_ptr<PositionMatrix> positionMatrix;
};


