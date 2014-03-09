#include "Level.h"

const sf::Color Level::BACKGROUND_COLOR(0x22, 0x8b, 0x22);
const float Level::GRID_THICKNESS = 2.0f;
const sf::Color Level::GRID_COLOR(128, 128, 128);

Level::Level(const std::string& filename) {
	(void)filename;

	Entity::Pointer entity1(new Entity(0, "red_castle.png"));
	entity1->setPosition(0, 0);
	entities.push_back(entity1);

	Entity::Pointer entity2(new Entity(0, "red_castle.png"));
	entity2->setPosition(0, 1);
	entities.push_back(entity2);

	Entity::Pointer entity3(new Entity(0, "red_castle.png"));
	entity3->setPosition(1, 0);
	entities.push_back(entity3);
}

sf::Vector2i Level::getPosition(void) const {
	return position;
}

void Level::setPosition(int x, int y) {
	setPosition(sf::Vector2i(x, y));
}

void Level::setPosition(const sf::Vector2i& position) {
	this->position = position;
}

void Level::render(sf::RenderWindow& render) {
	sf::Vector2i render_size(render.GetWidth(), render.GetHeight());
	render.Draw(
		sf::Shape::Rectangle(
			0,
			0,
			render_size.x,
			render_size.y,
			BACKGROUND_COLOR
		)
	);

	EntityGroup::const_iterator i = entities.begin();
	for (; i != entities.end(); ++i) {
		Entity::Pointer entity = *i;
		entity->setPosition(entity->getPosition() - position);
		entity->render(render);
		entity->setPosition(entity->getPosition() + position);
	}

	for (int y = 0; y < render_size.y; y += Entity::SIZE) {
		render.Draw(
			sf::Shape::Line(0, y, render_size.x, y, GRID_THICKNESS, GRID_COLOR)
		);
	}
	for (int x = 0; x < render_size.x; x += Entity::SIZE) {
		render.Draw(
			sf::Shape::Line(x, 0, x, render_size.y, GRID_THICKNESS, GRID_COLOR)
		);
	}
}
