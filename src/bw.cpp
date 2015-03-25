#include <vector>
#include <boost/numeric/ublas/matrix.hpp>
#include <numeric>

#include "operationVector.h" // ceci va chercher le fichier qui contient les operations sur les vecteurs
#include "alpha.h"
#include "beta.h"

using namespace std;
using namespace boost::numeric::ublas;

matrix<double> MINI(std::vector<matrix<double>> C, matrix<double> Mini, std::vector<double> pie, int iter) {

// 	C est la les des matrices d<observations
// 	Mini est la matrice de transition initiale
// 	pie est le vecteur de probabilite initiale
//  m est le nombre detat
//  iter, le nombre diteration desire
	const int m = C[0].size2();
	const int obs = C.size(); // Nombre de parties joués
	auto nouvMm = std::vector<matrix<double>>(obs, matrix<double>(m,m)); // Ce qui va stocker nos poids de transition pour chaque parties

    for ( int k=0 ; k < iter; ++k) {

        matrix<double> nouvM = Mini;

        for ( int o=0; o < obs; ++o) {

            int n = C[o].size1();
            auto lalpha = Alpha(C[o],nouvM,pie);
            auto lbeta = Beta(C[o],nouvM,pie);
            double p = getMax(ligne(lalpha,n-1));
            double logl = p + log(sum(expMat(ligne(lalpha,n-1)-p)));

            for ( int i=0; i <m; ++i) {
                for ( int j=0; j<m; ++j) {
                    double grostruc = 0;
                    for ( int ind=0; ind <n-1; ++ind ) {
                        grostruc = grostruc+ exp(lalpha(ind,i)+C[o](ind+1,j)+lbeta(ind+1,j)-logl);
                    }
                    nouvMm[o](i,j) = Mini(i,j) * grostruc;
                }
            }

        }

        nouvM = nouvMm[0];

        for ( int o=1; o< obs; ++o) {
            nouvM = nouvM + nouvMm[o];
        }

        for ( int j=0; j<m; ++j) {
			double sumLigne = sum(ligne(nouvM,j));
            if ( sumLigne ==0 ) {
                nouvM(j,j) = 1;

            } else {
                for ( int i = 0;  i <m; ++i){
                    nouvM(j,i) = nouvM(j,i) / sumLigne;
                }

            }

        }


        Mini = nouvM;
    }

	return Mini;

}
