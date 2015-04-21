#include "Turn.h"

#include "Entity/Entity.h"
#include "event.h"

#include <memory>
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

void Turn::preApply()
{
	for (auto& i : listMove) {
		i.first->setNextPosition(i.first->getPosition() + i.second);
		i.second = {};
	}
	
	for (auto event : preApplyEvents) {
		event->trigger();
	}
}

void Turn::apply()
{
	reset();
	preApply();
	
	for (auto event : applyEvents) {
		event->trigger();
	}
	
	for (auto& i : listMove) {
		i.first->move();
		i.second = {};
	}
	
	for (auto event : endTurnEvents) {
		event->trigger();
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

void Turn::addEndTurnEvent(shared_ptr<Event> event)
{
	endTurnEvents.insert(event);
}

void Turn::removeTurnEvent(shared_ptr<Event> event)
{
	endTurnEvents.erase(event);
}

void Turn::addPreApplyEvent(shared_ptr< Event > event)
{
	preApplyEvents.insert(event);
}

void Turn::removePreApplyEvent(shared_ptr< Event > event)
{
	preApplyEvents.erase(event);
}

void Turn::addApplyEvent(shared_ptr<Event> event)
{
	applyEvents.insert(event);
}

void Turn::removeApplyEvent(shared_ptr<Event> event)
{
	applyEvents.erase(event);
}
