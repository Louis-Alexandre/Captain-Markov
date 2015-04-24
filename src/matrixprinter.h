#pragma once

#include "event.h"

#include <memory>

class MatrixProvider;

class MatrixPrinter : public Event
{
public:
	MatrixPrinter(std::shared_ptr<MatrixProvider> matrixProvider);
    void trigger() override;
	
private:
	std::shared_ptr<MatrixProvider> matrixProvider;
};
