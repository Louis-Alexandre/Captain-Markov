#pragma once

#include "matrixprovider.h"

#include <memory>

#include <boost/numeric/ublas/matrix.hpp>
#include <SFML/System.hpp>

class Observation;
class MapPositionTile;
class Tile;

class PositionMatrix : public MatrixProvider
{
public:
	PositionMatrix(std::shared_ptr<Observation> observation, std::shared_ptr<MapPositionTile> positionTile);
	
	sf::Vector2i getPosition() const;
	boost::numeric::ublas::matrix<double> getProbability() const;
	double getProbability(std::shared_ptr<Tile> tile) const;
	
	void makeMatrix();
	
	void setPie(std::vector<double> pie);
	void setTransition(boost::numeric::ublas::matrix<double> transition);
	
    virtual boost::numeric::ublas::matrix<double> getMatrix() const;
    virtual std::vector<std::vector<double>> getVecVec() const;
    virtual void reset();
	
private:
	std::shared_ptr<MapPositionTile> positionTile;
	boost::numeric::ublas::matrix<double> transition;
	boost::numeric::ublas::matrix<double> position;
	std::vector<double> pie;
	std::shared_ptr<Observation> observation;
};
