#ifndef LABEL_H
#define LABEL_H

#include "LabelStyle.h"

class Label {
public:
	explicit Label(const LabelStyle& style);
	std::string getText(void) const;
	void setText(const std::string& text);
	sf::Vector2f getPosition(void) const;
	void setPosition(float x, float y);
	void setPosition(const sf::Vector2f& position);
	void render(sf::RenderWindow& render);

private:
	LabelStyle style;
	sf::String text;
};
#endif
