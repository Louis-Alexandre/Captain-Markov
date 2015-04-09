#pragma once

#include <vector>
#include <boost/numeric/ublas/matrix.hpp>

extern boost::numeric::ublas::matrix<double> BW(std::vector<boost::numeric::ublas::matrix<double>> C, boost::numeric::ublas::matrix<double> Mini, std::vector<double> pie, int iter);
