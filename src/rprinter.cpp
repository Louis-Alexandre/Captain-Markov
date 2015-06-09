#include "rprinter.h"
#include "appendmatrixprovider.h"
#include "observation.h"
#include "positionmatrix.h"
#include "mappositiontile.h"
#include "Entity/Entity.h"

#include "operationVector.h"
#include "Map.h"

#include <fstream>

using namespace std;

RPrinter::RPrinter(
	shared_ptr<PositionMatrix> _positionMatrix,
	shared_ptr<Entity> _player1,
	shared_ptr<Entity> _player2,
	shared_ptr<Observation> _obs,
	shared_ptr<AppendMatrixProvider> _mxp,
	shared_ptr<Map> _map,
	shared_ptr<MapPositionTile> _mpt
) : 
	positionMatrix{_positionMatrix},
	player1{_player1},
	player2{_player2},
	obs{_obs},
	mxp{_mxp},
	map{_map} {}

void RPrinter::trigger()
{
	sf::Vector2i graphPlayer1Pos{player1->getPosition().x, 7-player1->getPosition().y};
	sf::Vector2i graphPlayer2Pos{player2->getPosition().x, 7-player2->getPosition().y};
	
	string name{string{"heat"} + to_string(mxp->getObservation().size()) + "-" + to_string(obs->getObservations().size())};
	
	ifstream printr{"print.r"};
	string printProgram{istreambuf_iterator<char>{printr}, istreambuf_iterator<char>{}};
	ofstream inSave{string{"r/"} + name + ".r", ifstream::binary};
	
	inSave << "Data <- c(";
	
	int j = 0;
	auto probs = positionMatrix->getProbability();
	probs = ligne(probs, probs.size1()-1);
	auto last = *map->getTiles().rbegin();
	for (auto tile : map->getTiles()) {
		if (tile->getTileType()->isWalkable()) {
			inSave << probs(0, j++);
		} else {
			inSave << 2;
		}
		if (tile != last) {
			inSave << ", ";
		}
	}
	inSave << ")\n";
	inSave << "pos1 <- c(" << graphPlayer1Pos.x << ", " << graphPlayer1Pos.y << ")\n";
	inSave << "pos2 <- c(" << graphPlayer2Pos.x << ", " << graphPlayer2Pos.y << ")\n";
	inSave << "pdf(file=paste (\"" << name << "\", \".pdf\", sep=\"\"),16,8)";
	inSave << printProgram;
}
