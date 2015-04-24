#include "callbackmatrixprovider.h"

CallbackMatrixProvider::CallbackMatrixProvider(std::function<boost::numeric::ublas::matrix<double>()> callbackFucntion) : callback{callbackFucntion}
{

}

boost::numeric::ublas::matrix< double > CallbackMatrixProvider::getMatrix() const
{
	return callback();
}
