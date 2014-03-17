#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>

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
	sf::Image image;
	sf::Sprite sprite;
};

typedef boost::shared_ptr<Sprite> SpriteSmartPointer;
#endif
