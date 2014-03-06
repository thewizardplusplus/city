#ifndef SPRITE_H
#define SPRITE_H

#include "TextureFactory.h"

class Sprite {
public:
	Sprite(const std::string& filename);
	sf::Vector2f getPosition(void) const;
	void setPosition(float x, float y);
	void setPosition(const sf::Vector2f& position);
	sf::Vector2f getSize(void) const;
	void setSize(float width, float height);
	void setSize(const sf::Vector2f& size);
	void render(sf::RenderWindow& render);

private:
	Texture texture;
	sf::Sprite sprite;
};
#endif
