#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <memory>

class CollisionHandler;
class MapInfo;

class Entity
{
public:
	Entity();
	sf::Vector2i getPosition() const;
	void setPosition(sf::Vector2i position);
	sf::Vector2i getStartPosition() const;
	void setStartPosition(sf::Vector2i position);
	void move(sf::Vector2i movement);
	
	void resetPosition();
	virtual void draw(sf::RenderWindow& window, MapInfo* mapInfo);
	
	void setCollisionHandler(std::shared_ptr<CollisionHandler> collisionHandler);
	std::shared_ptr<CollisionHandler> getCollisionHandler() const;
	
private:
	sf::Vector2i startPosition;
	sf::Vector2i position;
	std::shared_ptr<CollisionHandler> collisionHandler;
	

};
