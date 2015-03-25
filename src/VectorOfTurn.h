#pragma once

#include <boost/numeric/ublas/matrix.hpp>
#include <vector>

class VectorOfTurn
{
public:
	void addTurn(std::vector<int>);
	boost::numeric::ublas::matrix<int> getTurnSnapshotMatrix();
private:
	std::vector<std::vector<int>> turnSnapshots;
	
};
