#ifndef LABELSTYLE_H
#define LABELSTYLE_H

#include "FontFactory.h"

class LabelStyle {
public:
	Font font;
	sf::Color color;
	float size;

	LabelStyle(const Font& font, const sf::Color& color, float size);
};
#endif
