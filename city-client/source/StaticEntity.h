#ifndef STATICENTITY_H
#define STATICENTITY_H

#include "Entity.h"
#include "Sprite.h"

class StaticEntity : public Entity {
public:
	StaticEntity(size_t id, const std::string& sprite_filename);
	virtual void render(sf::RenderWindow& render);

protected:
	SpriteSmartPointer sprite;
};

typedef boost::shared_ptr<StaticEntity> StaticEntitySmartPointer;
#endif
