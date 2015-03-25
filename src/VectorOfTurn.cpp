#include "VectorOfTurn.h"

using namespace std;
using namespace boost::numeric::ublas;

void VectorOfTurn::addTurn(std::vector<int> currentTurn)
{
	turnSnapshots.push_back(currentTurn);
}

matrix<int> VectorOfTurn::getTurnSnapshotMatrix()
{
	int i = 0;
	int j = 0;
	int hauteur = turnSnapshots.size();
	int largeur = turnSnapshots[0].size();
	matrix<int> gameSnapshot (hauteur, largeur);
	for(auto turn: turnSnapshots){
		for(int prob: turn){
			gameSnapshot(i, j) = prob;
			j++;
		}
		i++;
	}
	return gameSnapshot;
}
