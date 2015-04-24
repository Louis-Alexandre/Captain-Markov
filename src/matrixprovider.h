#pragma once

#include <memory>
#include <boost/numeric/ublas/matrix.hpp>

class MatrixProvider
{
public:
	virtual boost::numeric::ublas::matrix<double> getMatrix() const = 0;
	
private:
};
