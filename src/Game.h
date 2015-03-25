#pragma once
#include <vector>
#include "Entity/Entity.h"

class Game
{
public:
	void addEntity(std::shared_ptr<Entity> entity);
	void setWasdControlled(std::shared_ptr<Entity> entity);
	void setArrowControlled(std::shared_ptr<Entity> entity);
	void mainLoop();
private:
	std::vector<std::shared_ptr<Entity>> entities;
	std::shared_ptr<Entity> wasdControlled;
	std::shared_ptr<Entity> arrowControlled;
};
