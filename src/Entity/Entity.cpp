#include "Entity.h"
#include "../CollisionHandler.h"


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

std::shared_ptr< CollisionHandler > Entity::getCollisionHandler() const
{
	return collisionHandler;
}

void Entity::setCollisionHandler(std::shared_ptr< CollisionHandler > collisionHandler)
{
	this->collisionHandler = collisionHandler;
}
