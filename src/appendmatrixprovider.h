#pragma once

#include "matrixprovider.h"

#include <memory>
#include <vector>

class MatrixLoader;
class Observation;

class AppendMatrixProvider : public MatrixProvider
{
public:
	AppendMatrixProvider(std::shared_ptr<MatrixLoader> loader, std::shared_ptr<Observation> observation);
	
	boost::numeric::ublas::matrix<int> getMatrix() const override;
	std::vector<std::vector<int>> getVecVec() const override;
	
private:
	std::shared_ptr<MatrixLoader> loader;
	std::shared_ptr<Observation> observation;
};
