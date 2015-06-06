#include "appendmatrixprovider.h"

#include "matrixloader.h"
#include "observation.h"

using namespace std;
using boost::numeric::ublas::matrix;

AppendMatrixProvider::AppendMatrixProvider(shared_ptr<MatrixLoader> loader) : loader{loader} {}

vector<matrix<double>> AppendMatrixProvider::getObservation() const
{
	auto previousGames = loader->getAll();
	vector<matrix<double>> result;
	
	for (auto game : previousGames) {
		matrix<double> mat{game.size(), game[0].size()};
		for (int n = 0 ; n<game.size() ; n++) {
			for (int m = 0 ; m<game[0].size() ; m++) {
				mat(n, m) = game[n][m];
			}
		}
		result.push_back(mat);
	}
	
	return result;
}

vector<matrix<double>> AppendMatrixProvider::getLast(int n) const
{
	auto obs = getObservation();
	if (obs.size() > n) {
		auto it = obs.end();
		advance(it, -n);
		return vector<matrix<double>>(it, obs.end());
	} else {
		return obs;
	}
}
