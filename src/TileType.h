#pragma once
#include <SFML/Graphics.hpp>

class TileType
{
public:
	void setWalkable(bool walkable); 
	bool isWalkable() const;
	void setColor(sf::Color color);
	sf::Color getColor() const;
	
private:
	sf::Color color;
	bool walkable;
};


