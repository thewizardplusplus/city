#include "FontFactory.h"
#include <boost/format.hpp>
#include <stdexcept>

FontFactory& FontFactory::getInstance(void) {
	static FontFactory font_factory;
	return font_factory;
}

Font FontFactory::loadFont(const std::string& filename) {
	if (!fonts.count(filename)) {
		Font font(new sf::Font());
		bool font_loaded = font->LoadFromFile(filename);
		if (!font_loaded) {
			throw std::runtime_error(
				(boost::format("Unable to load font \"%s\".") % filename).str()
			);
		}

		fonts[filename] = font;
	}

	return fonts[filename];
}

FontFactory::FontFactory(void) {}
