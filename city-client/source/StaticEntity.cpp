#include "StaticEntity.h"
#include "SpriteFactory.h"

StaticEntity::StaticEntity(size_t id, const std::string& sprite_filename) :
	Entity(id)
{
	sprite = SpriteFactory::getInstance().loadSprite(sprite_filename);
	sprite->setSize(SIZE, SIZE);
}

void StaticEntity::render(sf::RenderWindow& render) {
	sprite->setPosition(
		static_cast<float>(SIZE) * position.x,
		static_cast<float>(SIZE) * position.y
	);
	sprite->render(render);
}
