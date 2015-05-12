#include "initnodefinding.h"

#include "positionmatrix.h"
#include "NodeFinding.h"
#include "ListeNode.h"
#include "Entity/Entity.h"

#include "iostream"
using namespace std;

InitNodeFinding::InitNodeFinding(shared_ptr< PositionMatrix > _positionMatrix, shared_ptr< NodeFinding > _nodeFinding) : positionMatrix{_positionMatrix}, nodeFinding{_nodeFinding}
{
	
}

void InitNodeFinding::trigger()
{
	positionMatrix->makeMatrix();
	nodeFinding->initiateNodeFinding(positionMatrix->getPosition());
	controlledPlayer->setNextPosition(nodeFinding->findBestMove(controlledPlayer->getPosition()));
	cout << "nextPositionX: " << nodeFinding->findBestMove(controlledPlayer->getPosition()).x;
	cout << " ,nextPositionY: " << nodeFinding->findBestMove(controlledPlayer->getPosition()).y << endl;
}

void InitNodeFinding::setControlledEntity(shared_ptr<Entity> _controlledPlayer)
{
	controlledPlayer = _controlledPlayer;
}

