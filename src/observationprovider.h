#pragma once

#include <vector>
#include <boost/numeric/ublas/matrix.hpp>

class ObservationProvider
{
public:
	virtual std::vector<boost::numeric::ublas::matrix<double>> getObservation() const = 0;
};
