#include "TextureFactory.h"
#include <boost/format.hpp>
#include <stdexcept>

TextureFactory& TextureFactory::getInstance(void) {
	static TextureFactory texture_factory;
	return texture_factory;
}

Texture TextureFactory::loadTexture(const std::string& filename) {
	if (!textures.count(filename)) {
		Texture texture(new sf::Image());
		bool texture_loaded = texture->LoadFromFile(filename);
		if (!texture_loaded) {
			throw std::runtime_error(
				(boost::format("Unable to load texture \"%s\".") % filename)
					.str()
			);
		}

		textures[filename] = texture;
	}

	return textures[filename];
}

TextureFactory::TextureFactory(void) {}
