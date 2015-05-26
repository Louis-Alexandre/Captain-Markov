#pragma once

#include <memory>

#include <boost/numeric/ublas/matrix.hpp>
#include <SFML/System.hpp>

class Observation;
class MapPositionTile;
class Tile;

class PositionMatrix
{
public:
	PositionMatrix(std::shared_ptr<Observation> observation, std::shared_ptr<MapPositionTile> positionTile);
	
	sf::Vector2i getPosition() const;
	boost::numeric::ublas::matrix<double> getProbability() const;
	double getProbability(std::shared_ptr<Tile> tile) const;
	
	void makeMatrix();
	
	void setPie(std::vector<double> pie);
	void setTransition(boost::numeric::ublas::matrix<double> transition);
	
private:
	std::shared_ptr<MapPositionTile> positionTile;
	boost::numeric::ublas::matrix<double> transition;
	boost::numeric::ublas::matrix<double> position;
	std::vector<double> pie;
	std::shared_ptr<Observation> observation;
};
