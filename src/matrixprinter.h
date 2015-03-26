#pragma once

#include "event.h"

#include <memory>

class Observation;

class MatrixPrinter : public Event
{
public:
	
	void setObservation(std::shared_ptr<Observation> observation);
	std::shared_ptr<Observation> getObservation();
	
    void trigger() override;
	
private:
	std::shared_ptr<Observation> observation;
};
