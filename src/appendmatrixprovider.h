#pragma once

#include "matrixprovider.h"
#include "observationprovider.h"

#include <memory>
#include <vector>

class MatrixLoader;
class Observation;

class AppendMatrixProvider : public ObservationProvider
{
public:
	AppendMatrixProvider(std::shared_ptr<MatrixLoader> loader, std::shared_ptr<Observation> observation);
	
    std::vector< boost::numeric::ublas::matrix< double > > getObservation() const override;
	
private:
	std::shared_ptr<MatrixLoader> loader;
	std::shared_ptr<Observation> observation;
};
