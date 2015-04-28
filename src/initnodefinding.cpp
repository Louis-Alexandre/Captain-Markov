#include "initnodefinding.h"
#include "positionmatrix.h"

InitNodeFinding::InitNodeFinding(std::shared_ptr< PositionMatrix > positionMatrix) : positionMatrix{positionMatrix}
{
	
}

void InitNodeFinding::trigger()
{
	positionMatrix->makeMatrix();
	
}
