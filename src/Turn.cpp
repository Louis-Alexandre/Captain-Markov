#include "Turn.h"

#include <iostream>

using namespace std;



sf::Vector2i Turn::getMouvement(shared_ptr<Entity> entity)
{
	return listMove[entity];
}

void Turn::addMovement(shared_ptr< Entity > entity, sf::Vector2i movement)
{
	listMove[entity] = movement;
}

bool Turn::shouldApply() const
{
	return deltaTime() >= 0.7;
}

void Turn::apply()
{
	reset();
	for (auto& i : listMove) {
		i.first->move(i.second);
		i.second = {};
	}
}

double Turn::deltaTime() const
{
	return std::chrono::duration_cast<std::chrono::duration<double, ratio<1, 1>>>(chrono::high_resolution_clock::now() - lastTime).count();
}

void Turn::reset()
{
	lastTime = chrono::high_resolution_clock::now();
	totalTime = 0;
}
