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
	sf::Vector2i getNextPosition() const;
	void setNextPosition(sf::Vector2i position);
	void move();
	
	void resetPosition();
	void draw(sf::RenderWindow& window, MapInfo* mapInfo);
	
	void setTexture(std::shared_ptr<sf::Texture> _texture);
	
	void setCollisionHandler(std::shared_ptr<CollisionHandler> collisionHandler);
	std::shared_ptr<CollisionHandler> getCollisionHandler() const;
	
private:
	std::shared_ptr<sf::Texture> texture;
	sf::Vector2i startPosition;
	sf::Vector2i nextPosition;
	sf::Vector2i position;
	std::shared_ptr<CollisionHandler> collisionHandler;
	

};
