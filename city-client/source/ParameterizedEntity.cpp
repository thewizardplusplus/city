#include "ParameterizedEntity.h"

const float ParameterizedEntity::PARAMETER_LABEL_SHIFT = 10;
const LabelStyle ParameterizedEntity::PARAMETER_LABEL_STYLE(
	FontFactory::getInstance().loadFont("font.otf"),
	sf::Color::Red,
	2.5f
);

ParameterizedEntity::ParameterizedEntity(const std::string& sprite_filename) :
	Entity(sprite_filename),
	label(PARAMETER_LABEL_STYLE)
{
	updateParameterPosition();
}

std::string ParameterizedEntity::getParameter(void) const {
	return label.getText();
}

void ParameterizedEntity::setParameter(const std::string& parameter) {
	label.setText(parameter);
}

void ParameterizedEntity::setPosition(const sf::Vector2f& position) {
	Entity::setPosition(position);
	updateParameterPosition();
}

void ParameterizedEntity::render(sf::RenderWindow& render) {
	Entity::render(render);
	label.render(render);
}

void ParameterizedEntity::updateParameterPosition(void) {
	label.setPosition(
		sprite.getPosition() + sf::Vector2f(0.0f, PARAMETER_LABEL_SHIFT)
	);
}
