#ifndef ENTITY_H
#define ENTITY_H

#include "Sprite.h"
#include <boost/shared_ptr.hpp>

class Entity {
public:
	typedef boost::shared_ptr<Entity> Pointer;

	static const float SIZE;

	Entity(size_t id, const std::string& sprite_filename);
	virtual ~Entity(void);
	size_t getId(void) const;
	sf::Vector2i getPosition(void) const;
	void setPosition(int x, int y);
	virtual void setPosition(const sf::Vector2i& position);
	virtual void render(sf::RenderWindow& render);

protected:
	size_t id;
	sf::Vector2i position;
	Sprite sprite;

	void updateSpritePosition(void);
};
#endif
