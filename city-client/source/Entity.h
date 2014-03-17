#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>

class Entity {
public:
	static const float SIZE;

	Entity(size_t id);
	virtual ~Entity(void);
	size_t getId(void) const;
	sf::Vector2i getPosition(void) const;
	void setPosition(int x, int y);
	void setPosition(const sf::Vector2i& position);

protected:
	size_t id;
	sf::Vector2i position;
};

typedef boost::shared_ptr<Entity> EntitySmartPointer;
#endif
