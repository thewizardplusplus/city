#ifndef LEVEL_H
#define LEVEL_H

#include "Entity.h"
#include <vector>

typedef std::vector<Entity::Pointer> EntityGroup;

class Level {
public:
	static const sf::Color BACKGROUND_COLOR;
	static const float GRID_THICKNESS;
	static const sf::Color GRID_COLOR;

	Level(const std::string& filename);
	sf::Vector2i getPosition(void) const;
	void setPosition(int x, int y);
	void setPosition(const sf::Vector2i& position);
	void render(sf::RenderWindow& render);

private:
	sf::Vector2i position;
	EntityGroup entities;
};
#endif
