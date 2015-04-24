#include "positionmatrix.h"

#include "math.h"
#include "operationVector.h"

#include "Position.h"
#include "observation.h"
#include "mappositiontile.h"

using namespace std;

PositionMatrix::PositionMatrix(std::shared_ptr< Observation > observation, std::shared_ptr<MapPositionTile> positionTile) : observation{observation}, positionTile{positionTile}
{

}

sf::Vector2i PositionMatrix::getPosition() const
{
	int argMax = 0;
	double probMax = 0;
	auto mat = ligne(position, position.size1()-1);
	for (int i=0 ; i< mat.size2() ; i++) {
		argMax = probMax < mat(0, i) ? i:argMax;
		probMax = probMax < mat(0, i) ? mat(0, i):probMax;
	}
	
	return positionTile->getPosition(argMax);
}

boost::numeric::ublas::matrix< double > PositionMatrix::getProbability() const
{
	return position;
}

void PositionMatrix::setPie(std::vector< double > pie)
{
	this->pie = pie;
}

void PositionMatrix::setTransition(boost::numeric::ublas::matrix< double > transition)
{
	this->transition = transition;
}

void PositionMatrix::makeMatrix()
{
	position = Position(observation->getMatrix(), transition, pie);
}
