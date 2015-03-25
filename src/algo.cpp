#include "algo.h" // contient le "header" ou l'entête de la fonction alpha

#include <vector>
#include <boost/numeric/ublas/matrix.hpp>
#include <numeric>

#include "operationVector.h" // ceci va chercher le fichier qui contient les operations sur les vecteurs

using namespace std;
using namespace boost::numeric::ublas;

matrix<double> Alpha(matrix<double> Obs, matrix<double> M, std::vector<double> pie)
{
// 	Obs est la matrice des observations
// 	M est la matrice de transition
// 	pie est le vecteur de probabilite initiale

	const int m = Obs.size2(); // Nombre detat, de cases
	const int n = Obs.size1(); // Nombre dobservation, duree de la partie
	
//	matrix Alpha = matrix(NbLigne= n, NbCol= m);  Initialisation de la matric Alpha de tailler n*m
	matrix<double> Alpha(n, m);
	auto alph = std::vector<double>(m, 0); // Declaration d'un vecteur de longueur m remplie de 0

	for (int i = 0; i < m; ++i) {
		alph[i] = pie[i] * Obs(0, i);
	}

	double log1surc = log(sum(alph)); // J'ai ajouter la fonction sum, qui fait la somme d'une matrice ou d'un vecteur

// 	alph = alph * (1 / std::accumulate(alph.begin(), alph.end(), 0));
	alph = scalarMultiplication(alph, 1.0 / log1surc);

	for (int i = 0; i < m; ++i) {

		Alpha(0, i) = log(alph[i]) + log1surc;
	}

	auto Alph = matrix<double>(1, m);

	for (int i = 0 ; i < m ; ++i) {
		Alph(0, i) = alph[i];
	}

	for (int i = 1; i < n ; ++i) { // J'ai changer la partie "i < n, ++j" pour "i < n ; ++i"
		Alph = prod(Alph, M); // prod est le produit matriciel

		for (int j = 0; j < m ; ++j) {
			Alph(i, j) = Alph(i, j) * Obs(i, j);
		}

		log1surc += log(sum(alph));
		Alph /= sum(Alph);

		for (int j = 0; j < m ; ++j) {
			Alpha(i, j) = log(Alph(0, j)) + log1surc;
		}

	}

	return Alpha;

}
