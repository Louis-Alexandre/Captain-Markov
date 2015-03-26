#include "Position.h"

#include <vector>
#include <boost/numeric/ublas/matrix.hpp>
#include <numeric>

#include "operationVector.h" // ceci va chercher le fichier qui contient les operations sur les vecteurs
#include "alpha.h"

using namespace std;
using namespace boost::numeric::ublas;

matrix<double> Position(matrix<double> Obs, matrix<double> M, std::vector<double> pie) {

    int n = Obs.size1();
    int m = Obs.size2();
    auto alpha = Alpha(Obs, M, pie);
    matrix<double> Probs(n, m);
    double truc=0.0;

    for ( int i=0; i<n; ++i){

        double maxx = getMax(ligne(alpha,i));
        for ( int j=0; j<m; ++j){
            truc = truc+ exp(alpha(i,j)-maxx);
        }
        double corr = maxx+log(truc);
        for ( int j=0; j<m; ++j){
            Probs(i,j) = exp(alpha(i,j)-corr);
        }
    }
    
	for ( int j=0; j<n; ++j) {
		double sumLigne = sum(ligne(Probs,j));
		if ( sumLigne ==0 ) {
			Probs(j,j) = 1;

		} else {
			for ( int i = 0;  i <m; ++i){
				Probs(j,i) = Probs(j,i) / sumLigne;
			}
		}
	}
    return Probs;

}
