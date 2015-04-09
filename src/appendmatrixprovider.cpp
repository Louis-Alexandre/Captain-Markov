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

matrix<int> AppendMatrixProvider::getMatrix() const
{
	auto result = getVecVec();
	
	matrix<double> matResult{result.size(), result[0].size()};
	
	for (int n = 0 ; n<result.size() ; n++) {
		for (int m = 0 ; m<result[0].size() ; m++) {
			matResult(n, m) = result[n][m];
		}
	}
	
	return matResult;
}

vector<vector<int>> AppendMatrixProvider::getVecVec() const
{
	vector<vector<int>> result;
	auto mat1 = loader->getAll();
	auto mat2 = observation->getObservations();
	
	result.insert(result.end(), mat1.begin(), mat1.end());
	result.insert(result.end(), mat2.begin(), mat2.end());
	
	return result;
}