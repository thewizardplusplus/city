#ifndef ENTITY_H
#define ENTITY_H

#include "Sprite.h"

class Entity {
public:
	static const float SIZE;

	Entity(const std::string& sprite_filename);
	virtual ~Entity(void);
	sf::Vector2f getPosition(void) const;
	void setPosition(float x, float y);
	virtual void setPosition(const sf::Vector2f& position);
	virtual void render(sf::RenderWindow& render);

protected:
	Sprite sprite;
};
#endif
