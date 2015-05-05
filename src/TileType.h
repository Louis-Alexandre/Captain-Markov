#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class TileType
{
public:
	void setWalkable(bool walkable); 
	bool isWalkable() const;
	
	void setTexture(std::shared_ptr<sf::Texture> _texture);
	std::shared_ptr<const sf::Texture> getTexture() const;
	
private:
	std::shared_ptr<sf::Texture> texture;
	bool walkable;
};


