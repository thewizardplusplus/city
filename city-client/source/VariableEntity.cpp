#include "VariableEntity.h"
#include <stdexcept>

VariableEntity::VariableEntity(
	size_t id,
	const StringGroup& sprites_filenames
) try :
	Entity(id, sprites_filenames.at(0)),
	state(0)
{
	sprites.reserve(sprites_filenames.size());
	StringGroup::const_iterator i = sprites_filenames.begin();
	for (++i; i != sprites_filenames.end(); ++i) {
		Sprite sprite(*i);
		sprite.setSize(SIZE, SIZE);

		sprites.push_back(sprite);
	}
} catch (const std::out_of_range& exception) {
	(void)exception;
	throw std::runtime_error(
		"Must not create VariableEntity with empty sprites filenames vector."
	);
}

size_t VariableEntity::getState(void) const {
	return state;
}

void VariableEntity::setState(size_t state) {
	this->state = state;
}

void VariableEntity::setPosition(const sf::Vector2i& position) {
	Entity::setPosition(position);
	updateSpritesPosition();
}

void VariableEntity::render(sf::RenderWindow& render) try {
	if (state == 0) {
		Entity::render(render);
	} else {
		sprites.at(state - 1).render(render);
	}
} catch (const std::out_of_range& exception) {
	(void)exception;
	throw std::runtime_error("Invalid state of VariableEntity.");
}

void VariableEntity::updateSpritesPosition(void) {
	SpriteGroup::iterator i = sprites.begin();
	for (; i != sprites.end(); ++i) {
		i->setPosition(sprite.getPosition());
	}
}
