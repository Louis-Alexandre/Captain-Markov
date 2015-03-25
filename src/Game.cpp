#include "Game.h"

void Game::addEntity(std::shared_ptr<Entity> entity)
{
	entities.push_back(entity);
}

void Game::setArrowControlled(std::shared_ptr<Entity> entity)
{
	arrowControlled = entity;
}

void Game::setWasdControlled(std::shared_ptr<Entity> entity)
{
	wasdControlled = entity;
}

void Game::mainLoop()
{

}
