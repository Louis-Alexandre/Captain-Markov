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
	AppendMatrixProvider(std::shared_ptr<MatrixLoader> loader);
	
    std::vector< boost::numeric::ublas::matrix< double > > getObservation() const override;
	std::vector< boost::numeric::ublas::matrix< double > > getLast10() const;
	
private:
	std::shared_ptr<MatrixLoader> loader;
};
