#pragma once

#include <memory>
#include <vector>
#include <SFML/System.hpp>
// Nom de merde, donne la position de la tuile par rapport a l'arg

class Map;
class Tile;

class MapPositionTile
{
public:
	MapPositionTile(std::shared_ptr<Map> map);
	
	sf::Vector2i getPosition(int arg);
	
private:
	std::vector<std::shared_ptr<Tile>> mappedTiles;
};
