#pragma once

#include "optionnal.h"

#include <SFML/Window.hpp>
#include <map>
#include <set>
#include <chrono>
#include <memory>

class Event;
class Entity;

class Turn
{
public:
	sf::Vector2i getMouvement(std::shared_ptr<Entity> entity) const;
	void removeMovement(std::shared_ptr<Entity> entity);
	void addMovement(std::shared_ptr<Entity> entity, sf::Vector2i movement);
	bool shouldApply() const;
	void apply();
	
	void addEndTurnEvent(std::shared_ptr<Event> event);
	void removeTurnEvent(std::shared_ptr<Event> event);
	
	void addPreApplyEvent(std::shared_ptr<Event> event);
	void removePreApplyEvent(std::shared_ptr<Event> event);
	
	void addApplyEvent(std::shared_ptr<Event> event);
	void removeApplyEvent(std::shared_ptr<Event> event);
	
	void reset();
	double deltaTime() const;
	
	void addRequiredEntity(std::shared_ptr<Entity> entity);
	void removeRequiredEntity(std::shared_ptr<Entity> entity);

private:
	void preApply();
	std::set<std::shared_ptr<Event>> applyEvents;
	std::vector<std::shared_ptr<Event>> preApplyEvents;
	std::set<std::shared_ptr<Event>> endTurnEvents;
	std::map<std::shared_ptr<Entity>, optionnal<sf::Vector2i>> listMove;
	std::set<std::shared_ptr<Entity>> required;
	std::chrono::high_resolution_clock::time_point lastTime = std::chrono::high_resolution_clock::now();
	double totalTime = 0;
};


