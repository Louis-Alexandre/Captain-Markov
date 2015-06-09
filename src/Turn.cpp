#include "Turn.h"

#include "Entity/Entity.h"
#include "event.h"

#include <memory>
#include <iostream>

using namespace std;

sf::Vector2i Turn::getMouvement(shared_ptr<Entity> entity) const
{
	auto it = listMove.find(entity);
	
	if (it != listMove.end() && it->second) {
		return *it->second;
	} else {
		return sf::Vector2i{0, 0};
	}
}

void Turn::addMovement(shared_ptr<Entity> entity, sf::Vector2i movement)
{
	listMove[entity] = movement;
}

void Turn::removeMovement(shared_ptr<Entity> entity)
{
	listMove[entity] = nullopt;
}

bool Turn::shouldApply() const
{
	for (auto entity : required) {
		auto it = listMove.find(entity);
		if (it == listMove.end() || !it->second) {
			return false;
		}
	}
	
	return true && deltaTime() >= 0.25;
}

void Turn::preApply()
{
	for (auto& n : listMove) {
		if (n.second) {
			n.first->setNextPosition(n.first->getPosition() + *n.second);
			n.second = nullopt;
		}
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
	
	for (auto& n : listMove) {
		n.first->move();
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
	preApplyEvents.emplace_back(event);
}

void Turn::removePreApplyEvent(shared_ptr< Event > event)
{
	auto it = find(preApplyEvents.begin(), preApplyEvents.end(), event);
	
	if (it != preApplyEvents.end()) {
		preApplyEvents.erase(it);
	}
}

void Turn::addApplyEvent(shared_ptr<Event> event)
{
	applyEvents.insert(event);
}

void Turn::removeApplyEvent(shared_ptr<Event> event)
{
	applyEvents.erase(event);
}

void Turn::addRequiredEntity(shared_ptr<Entity> entity)
{
	required.emplace(entity);
}

void Turn::removeRequiredEntity(shared_ptr<Entity> entity)
{
	required.erase(entity);
}
