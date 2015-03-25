#include <vector>
#include <boost/numeric/ublas/matrix.hpp>
#include <numeric>

#include "operationVector.h" // ceci va chercher le fichier qui contient les operations sur les vecteurs

using namespace std;
using namespace boost::numeric::ublas;

matrix<double> Beta(matrix<double> Obs, matrix<double> M, std::vector<double> pie) {

// 	Obs est la matrice des observations
// 	M est la matrice de transition
// 	pie est le vecteur de probabilite initiale

	const int m = Obs.size2(); // Nombre detat, de cases
	const int n = Obs.size1(); // Nombre dobservation, duree de la partie

//	matrix Alpha = matrix(NbLigne= n, NbCol= m);  Initialisation de la matric Alpha de tailler n*m
	matrix<double> Beta(n, m);
	auto bet = std::vector<double>(m, 1.0/m); // Declaration d'un vecteur de longueur m remplie de 0

	for (int i = 0; i < m; ++i) {

		Beta(n-1, i) = 0; // Si je comprend bien, la derniere ligne est la n-1 ?
	}

	double log1surc = log(sum(bet));
	auto Bet = matrix<double>(1, m);


	Bet = prod(M,ligne(Obs,n-1));

	for (int i = 0; i < m; ++i) {

		Beta(n-2, i) = log(Bet(0,i))+log1surc;
	}

	log1surc = log1surc + log(sum(Bet));
	Bet /= sum(Bet);
    auto Inter = matrix<double>(1, m);



	for (int i = 3; i < n+1 ; ++i) { // J'ai changer la partie "i < n, ++j" pour "i < n ; ++i"
		Inter = prod(M, ligne(Obs,n-i+1)); // prod est le produit matriciel

		for (int j = 0; j < m ; ++j) {
			Bet(0, j) = Inter(0, j) * Bet(0, j);
		}

		for (int j = 0; j < m ; ++j) {
			Beta(n-i, j) = log(Bet(0, j)) + log1surc;
		}

		log1surc += log(sum(Bet));
		Bet /= sum(Bet);



	}

	return Beta;

}
