#include "Entity.h"

const float Entity::SIZE = 75.0f;

Entity::Entity(size_t id) :
	id(id)
{}

Entity::~Entity(void) {}

size_t Entity::getId(void) const {
	return id;
}

sf::Vector2i Entity::getPosition(void) const {
	return position;
}

void Entity::setPosition(int x, int y) {
	setPosition(sf::Vector2i(x, y));
}

void Entity::setPosition(const sf::Vector2i& position) {
	this->position = position;
}
