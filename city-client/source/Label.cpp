#include "Label.h"

Label::Label(const LabelStyle& style) :
	style(style)
{
	if (style.font) {
		text.SetFont(*style.font);
	} else {
		text.SetFont(sf::Font::GetDefaultFont());
	}
	text.SetColor(style.color);
	text.SetSize(style.size);
}

std::string Label::getText(void) const {
	return text.GetText();
}

void Label::setText(const std::string& text) {
	this->text.SetText(text);
}

sf::Vector2f Label::getPosition(void) const {
	return text.GetPosition();
}

void Label::setPosition(float x, float y) {
	text.SetPosition(x, y);
}

void Label::setPosition(const sf::Vector2f& position) {
	text.SetPosition(position);
}

void Label::render(sf::RenderWindow& render) {
	render.Draw(text);
}
