#pragma once // nous voulons include qu'une seule fois.

#include <vector>
#include <boost/numeric/ublas/matrix.hpp>

// entête de la fonction
boost::numeric::ublas::matrix<double> Alpha(boost::numeric::ublas::matrix<double> Obs, boost::numeric::ublas::matrix<double> M, std::vector<double> pie);
