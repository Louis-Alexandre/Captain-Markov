#pragma once
#include <SFML/System.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>

class CollisionHandler;

class Entity
{
public:
	Entity();
	sf::Vector2i getPosition() const;
	void setPosition(sf::Vector2i position);
	void move(sf::Vector2i movement);
	
	void setCollisionHandler(std::shared_ptr<CollisionHandler> collisionHandler);
	std::shared_ptr<CollisionHandler> getCollisionHandler() const;
	
private:
	sf::Vector2i position;
	std::shared_ptr<CollisionHandler> collisionHandler;
	

};
