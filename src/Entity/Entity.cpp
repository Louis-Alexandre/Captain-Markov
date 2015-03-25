#include "Entity.h"
#include "../CollisionHandler.h"

#include "../mapinfo.h"

using namespace std;

Entity::Entity()
{
}

sf::Vector2i Entity::getPosition() const
{
	return position;
}

void Entity::setPosition(sf::Vector2i position)
{
	this->position = position;
}

void Entity::move(sf::Vector2i movement)
{
	if (collisionHandler->checkCollision(position + movement)) {
		position += movement;
	}
}

shared_ptr<CollisionHandler> Entity::getCollisionHandler() const
{
	return collisionHandler;
}

void Entity::setCollisionHandler(shared_ptr<CollisionHandler> collisionHandler)
{
	this->collisionHandler = collisionHandler;
}

sf::Vector2i Entity::getStartPosition() const
{
	return startPosition;
}

void Entity::setStartPosition(sf::Vector2i position)
{
	startPosition = position;
}

void Entity::resetPosition()
{
	position = startPosition;
}

void Entity::draw(sf::RenderWindow& window, MapInfo* mapInfo)
{
	sf::RectangleShape playerRect(sf::Vector2f{static_cast<float>(mapInfo->getTileWidth()), static_cast<float>(mapInfo->getTileHeight())});
	playerRect.setFillColor(sf::Color::White);
	playerRect.setPosition(position.x * mapInfo->getTileWidth(), position.y * mapInfo->getTileHeight());
	window.draw(playerRect);
}
