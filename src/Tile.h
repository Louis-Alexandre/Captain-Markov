#pragma once
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
class TileType;
class Tile
{
public:
	Tile();
	Tile(std::shared_ptr<TileType> tileType);
	
	sf::Vector2i getPosition() const;
	void setPosition(sf::Vector2i position);
	std::shared_ptr<TileType> getTileType() const;
	void setTileType(std::shared_ptr<TileType> type);
	void setTileHeight(int tileHeight);
	int getTileHeight() const;
	void setTileWidth(int tileWidth);
	int getTileWidth() const;
 	double getHeuristic();
 	void setHeuristic(double probabiliter);
	
	

private:
	//type goal
	std::shared_ptr<TileType> tileType;
	double heuristic;
	int tileWidth;
	int tileHeight;
	sf::Vector2i position;
	

};
