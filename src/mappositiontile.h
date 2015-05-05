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
	MapPositionTile(std::shared_ptr<Map> _map);
	
	sf::Vector2i getPosition(int arg);
private:
	void makeMap();
	std::shared_ptr<Map> map;
	std::vector<std::shared_ptr<Tile>> mappedTiles;
};
