#pragma once

#include <memory>
#include <boost/numeric/ublas/matrix.hpp>

class MatrixLoader;
class Observation;

class MatrixProvider
{
public:
	virtual boost::numeric::ublas::matrix<int> getMatrix() const = 0;
	virtual std::vector<std::vector<int>> getVecVec() const = 0;
	
private:
};
