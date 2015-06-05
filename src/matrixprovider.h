#pragma once

#include <memory>
#include <boost/numeric/ublas/matrix.hpp>

class MatrixProvider
{
public:
	virtual boost::numeric::ublas::matrix<double> getMatrix() const = 0;
	virtual std::vector<std::vector<double>> getVecVec() const = 0;
	virtual void reset() = 0;
	
private:
};
