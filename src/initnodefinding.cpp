#include "initnodefinding.h"

#include "positionmatrix.h"
#include "NodeFinding.h"
#include "ListeNode.h"

using namespace std;

InitNodeFinding::InitNodeFinding(shared_ptr< PositionMatrix > _positionMatrix, shared_ptr< NodeFinding > _nodeFinding) : positionMatrix{_positionMatrix}, nodeFinding{_nodeFinding}
{
	
}

void InitNodeFinding::trigger()
{
	positionMatrix->makeMatrix();
	
}
