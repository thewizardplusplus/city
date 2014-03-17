#include "Sprite.h"
#include <boost/format.hpp>
#include <stdexcept>

using namespace boost;

Sprite::Sprite(const std::string& filename) {
	bool image_loaded = image.LoadFromFile(filename);
	if (!image_loaded) {
		throw std::runtime_error(
			(boost::format("Unable to load image \"%s\".") % filename)
				.str()
		);
	}

	sprite.SetImage(image);
}

sf::Vector2f Sprite::getPosition(void) const {
	return sprite.GetPosition();
}

void Sprite::setPosition(float x, float y) {
	sprite.SetPosition(x, y);
}

void Sprite::setPosition(const sf::Vector2f& position) {
	sprite.SetPosition(position);
}

sf::Vector2f Sprite::getSize(void) const {
	return sprite.GetSize();
}

void Sprite::setSize(float width, float height) {
	sprite.Resize(width, height);
}

void Sprite::setSize(const sf::Vector2f& size) {
	sprite.Resize(size);
}

void Sprite::render(sf::RenderWindow& render) {
	render.Draw(sprite);
}
