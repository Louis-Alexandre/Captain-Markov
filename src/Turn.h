#pragma once
#include <SFML/Window.hpp>
#include <map>
#include <memory>
#include <chrono>
#include "Entity/Entity.h"

class Turn
{
public:
	sf::Vector2i getMouvement(std::shared_ptr<Entity> entity);
	void addMovement(std::shared_ptr<Entity> entity, sf::Vector2i movement);
	bool shouldApply() const;
	void apply();
	void createVectorTurn();
	
	void reset();
	double deltaTime() const;

private:
	std::vector<sf::Vector2i> mouvement;
	std::map<std::shared_ptr<Entity>, sf::Vector2i> listMove;
	std::chrono::high_resolution_clock::time_point lastTime = std::chrono::high_resolution_clock::now();
	double totalTime = 0;
};


