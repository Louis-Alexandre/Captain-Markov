#pragma once

#include "matrixprovider.h"

#include <functional>
#include <boost/numeric/ublas/matrix.hpp>

class CallbackMatrixProvider : public MatrixProvider
{
public:
	CallbackMatrixProvider(std::function<boost::numeric::ublas::matrix<double>()> callbackFucntion);
    boost::numeric::ublas::matrix< double > getMatrix() const override;
	
private:
	std::function<boost::numeric::ublas::matrix<double>()> callback;
};
