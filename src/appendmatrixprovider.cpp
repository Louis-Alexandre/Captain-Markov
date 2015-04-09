#include "appendmatrixprovider.h"

#include "matrixloader.h"
#include "observation.h"

using namespace std;
using boost::numeric::ublas::matrix;

AppendMatrixProvider::AppendMatrixProvider(shared_ptr<MatrixLoader> loader, shared_ptr<Observation> observation) :
	loader{loader},
	observation{observation}
{
	
}

vector<matrix<int>> AppendMatrixProvider::getObservation() const
{
	auto previousGames = loader->getAll();
	auto currentGame = observation->getVecVec();
	vector<matrix<int>> result;
	
	for (auto game : previousGames) {
		matrix<int> mat{game.size(), game[0].size()};
		for (int n = 0 ; n<game.size() ; n++) {
			for (int m = 0 ; m<game[0].size() ; m++) {
				mat(n, m) = game[n][m];
			}
		}
		result.push_back(mat);
	}
	
	return result;
	
}
