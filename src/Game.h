#pragma once

#include <vector>
#include "Turn.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Goal;
class Map;
class Entity;
class CollisionHandler;

class Game
{
public:
	Game();
	void addEntity(std::shared_ptr<Entity> entity);
	void setWasdControlled(std::shared_ptr<Entity> entity);
	void setArrowControlled(std::shared_ptr<Entity> entity);
	void setWinGoal(std::shared_ptr<Goal> winGoal);
	void setLostGoal(std::shared_ptr<Goal> lostGoal);
	
	void init();
	void mainLoop();
	void reset();
	void lost();
	void win();
	void end();
	void render();
	void handleEvent();
	
	std::shared_ptr<Goal> getWinGoal() const;
	std::shared_ptr<Goal> getLostGoal() const;
	std::shared_ptr<Map> getMap();
	
private:
	sf::RenderWindow window;
	Turn turn;
	std::vector<std::shared_ptr<Entity>> entities;
	std::shared_ptr<CollisionHandler> collisionHandler;
	std::shared_ptr<Map> map;
	std::shared_ptr<Entity> wasdControlled;
	std::shared_ptr<Entity> arrowControlled;
	std::shared_ptr<Goal> winGoal;
	std::shared_ptr<Goal> lostGoal;
};
