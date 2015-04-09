#pragma once

#include "event.h"

#include <memory>

class MatrixProvider;

class MatrixPrinter : public Event
{
public:
	void setObservation(std::shared_ptr<MatrixProvider> observation);
	std::shared_ptr<MatrixProvider> getObservation();
	
    void trigger() override;
	
private:
	std::shared_ptr<MatrixProvider> observation;
};
