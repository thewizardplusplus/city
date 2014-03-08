#include "Entity.h"

const float Entity::SIZE = 10.0;

Entity::Entity(const std::string& sprite_filename) :
	sprite(sprite_filename)
{}

Entity::~Entity(void) {}

sf::Vector2f Entity::getPosition(void) const {
	return sprite.getPosition();
}

void Entity::setPosition(float x, float y) {
	setPosition(sf::Vector2f(x, y));
}

void Entity::setPosition(const sf::Vector2f& position) {
	sprite.setPosition(position);
}

void Entity::render(sf::RenderWindow& render) {
	sprite.render(render);
}
