#include "VariableEntity.h"
#include "SpriteFactory.h"
#include <boost/foreach.hpp>
#include <stdexcept>

VariableEntity::VariableEntity(
	size_t id,
	const StringGroup& sprites_filenames
) :
	Entity(id),
	state(0)
{
	if (sprites_filenames.empty()) {
		throw std::runtime_error(
			"Must not create VariableEntity with empty sprites filenames "
			"vector."
		);
	}

	sprites.reserve(sprites_filenames.size());
	BOOST_FOREACH(std::string sprite_filename, sprites_filenames) {
		SpriteSmartPointer sprite = SpriteFactory::getInstance().loadSprite(
			sprite_filename
		);
		sprite->setSize(SIZE, SIZE);

		sprites.push_back(sprite);
	}
}

size_t VariableEntity::getState(void) const {
	return state;
}

void VariableEntity::setState(size_t state) {
	this->state = state;
}

void VariableEntity::render(sf::RenderWindow& render) try {
	SpriteSmartPointer sprite = sprites.at(state - 1);
	sprite->setPosition(
		static_cast<float>(SIZE) * position.x,
		static_cast<float>(SIZE) * position.y
	);
	sprite->render(render);
} catch (const std::out_of_range& exception) {
	(void)exception;
	throw std::runtime_error("Invalid state of VariableEntity.");
}
