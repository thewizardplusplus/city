#include "SpriteFactory.h"
#include <boost/format.hpp>
#include <stdexcept>

SpriteFactory& SpriteFactory::getInstance(void) {
	static SpriteFactory sprite_factory;
	return sprite_factory;
}

SpriteSmartPointer SpriteFactory::loadSprite(const std::string& filename) {
	if (!sprites.count(filename)) {
		sprites[filename] = SpriteSmartPointer(new Sprite(filename));
	}

	return sprites[filename];
}

SpriteFactory::SpriteFactory(void) {}
