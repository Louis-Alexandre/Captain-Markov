#pragma once

#include <vector>
#include <boost/numeric/ublas/matrix.hpp>

extern boost::numeric::ublas::matrix<double> Alpha(boost::numeric::ublas::matrix<double> Obs, boost::numeric::ublas::matrix<double> M, std::vector<double> pie);